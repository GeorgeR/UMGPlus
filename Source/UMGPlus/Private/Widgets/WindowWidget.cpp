#include "Widgets/WindowWidget.h"

#include "WidgetLayoutLibrary.h"
#include "SlateBlueprintLibrary.h"
#include "WidgetBlueprintLibrary.h"

FWindowParameters::FWindowParameters()
{
	bCenterOfScreen = true;
	Position = FIntPoint(100, 100);
	Size = FIntPoint(400, 200);

	bClampToViewport = true;
	bMoveable = true;
	bResizeable = true;
	bIsCloseable = true;
}

UWindowWidget::UWindowWidget()
{
	bClampToViewport = true;
	bMoveable = true;
	bResizeable = true;
}

void UWindowWidget::SetParameters(FWindowParameters& InParameters)
{
	TitleText = InParameters.TitleText;
	bClampToViewport = InParameters.bClampToViewport;
	bMoveable = InParameters.bMoveable;
	bResizeable = InParameters.bResizeable;
	bIsCloseable = InParameters.bIsCloseable;
}

void UWindowWidget::Close()
{
	Super::Close();
}

void UWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RootSlot = Cast<UCanvasPanelSlot>(Slot);

	TitleBorder->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnTitleMouseDown"));
	TitleBorder->OnMouseMoveEvent.BindUFunction(this, TEXT("OnTitleMouseMove"));
	TitleBorder->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnTitleMouseUp"));

	ResizeBorder->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnTitleMouseDown"));
	ResizeBorder->OnMouseButtonUpEvent.BindUFunction(this, TEXT("OnTitleMouseUp"));
}

void UWindowWidget::DragPosition(const FVector2D& InMouseDelta)
{
	auto Offset = RootSlot->GetPosition() + InMouseDelta;
	const auto Viewport = GetViewportSize() / GetViewportScale();

	Offset = bClampToViewport ? FMath::Clamp(Offset, FVector2D::ZeroVector, (Viewport - RootSlot->GetSize())) : Offset;

	RootSlot->SetPosition(Offset);
}

FEventReply UWindowWidget::OnTitleMouseDown(FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	GetMouseInViewportSpace(InMouseEvent, PixelPosition, ViewportPosition);

	LastMousePosition = ViewportPosition;
	bIsMouseButtonDown = true;

	return UWidgetBlueprintLibrary::Handled();
}

FEventReply UWindowWidget::OnTitleMouseMove(FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bIsMouseButtonDown)
		return UWidgetBlueprintLibrary::Handled();
		
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	GetMouseInViewportSpace(InMouseEvent, PixelPosition, ViewportPosition);

	const auto CurrentMouseDelta = ViewportPosition - LastMousePosition;

	if (!bIsForResize && bMoveable && IsMouseInViewport(InMouseEvent))
		DragPosition(CurrentMouseDelta);
	else
		DragSize(CurrentMouseDelta);

	auto DetectedDrag = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::CaptureMouse(DetectedDrag, this);
}

FEventReply UWindowWidget::OnTitleMouseUp(FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsMouseButtonDown = false;
	bIsForResize = false;

	auto DetectedDrag = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return UWidgetBlueprintLibrary::ReleaseMouseCapture(DetectedDrag);
}

void UWindowWidget::DragSize(const FVector2D& InMouseDelta)
{
	const auto Viewport = GetViewportSize() / GetViewportScale();

	const FVector2D AdjustedMaxSize(
		MaxSize.X <= Viewport.X ? MaxSize.X : Viewport.X, 
		MaxSize.Y <= Viewport.Y ? MaxSize.Y : Viewport.Y);

	DesiredSize = DesiredSize + InMouseDelta;
	DesiredSize = FMath::Clamp(DesiredSize, MinSize, AdjustedMaxSize);

	RootSlot->SetSize(DesiredSize);

	DragPosition(InMouseDelta);
}

bool UWindowWidget::IsMouseInViewport(const FPointerEvent& InPointerEvent)
{
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	GetMouseInViewportSpace(InPointerEvent, PixelPosition, ViewportPosition);

	const auto ViewportSize = GetViewportSize();

	return (PixelPosition.X >= 0.0f && PixelPosition.X <= ViewportSize.X
		&& PixelPosition.Y >= 0.0f && PixelPosition.Y <= ViewportSize.Y);
}

FVector2D UWindowWidget::GetViewportSize()
{
	return UWidgetLayoutLibrary::GetViewportSize(this);
}

float UWindowWidget::GetViewportScale()
{
	return UWidgetLayoutLibrary::GetViewportScale(this);
}

void UWindowWidget::GetMouseInViewportSpace(
	const FPointerEvent& InPointerEvent, 
	FVector2D& OutPixelPosition,
	FVector2D& OutViewportPosition)
{
	USlateBlueprintLibrary::AbsoluteToViewport(this, InPointerEvent.GetScreenSpacePosition(), OutPixelPosition, OutViewportPosition);
}

FReply UWindowWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	bHasFocus = true;
	return FReply::Handled();
}

void UWindowWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	bHasFocus = false;
}

void UWindowWidget::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	// if the new focused widget is a child of this window, the window maintains focus
}
