#include "ViewManager.h"
#include "HasContextInterface.h"
#include "ViewWidget.h"
#include "WindowWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"

UViewManager* UViewManager::Instance = nullptr;

FViewParameters::FViewParameters()
{
	InputMode = EInputMode::IM_GameAndUI;
	bShowMouse = false;
}

UViewManager::UViewManager()
{
	Instance = this;

	WindowContainerWidgetClass = LoadClass<UWindowContainerWidget>(this, TEXT("WidgetBlueprint'/UMGPlus/WBP_WindowContainer.WBP_WindowContainer_C'"));
}

UViewManager* UViewManager::Get()
{
	if(Instance == nullptr)
		NewObject<UViewManager>();
	
	return Instance;
}

void UViewManager::FadeTo(APlayerController* InController, float InDuration, FLinearColor InColor, bool bFadeAudio, bool bHoldWhenFinished)
{
	check(InController);
	const auto CameraManager = InController->PlayerCameraManager;
	
	CameraManager->StartCameraFade(0.0f, 1.0f, InDuration, InColor, bFadeAudio, bHoldWhenFinished);
}

void UViewManager::FadeTo(APlayerController* InController, TFunction<void()> OnComplete, float InDuration, FLinearColor InColor, bool bFadeAudio, bool bHoldWhenFinished)
{
	FadeTo(InController, InDuration, InColor, bFadeAudio, bHoldWhenFinished);

	auto FadeTimer = GetFadeTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(FadeTimer, [&]()
	{
		OnComplete();
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
		TimerHandleCache.Remove(FadeTimer);
	}, InDuration, false);
}

void UViewManager::FadeFrom(APlayerController* InController, float InDuration, FLinearColor InColor, bool bFadeAudio, bool bHoldWhenFinished)
{
	check(InController);
	const auto CameraManager = InController->PlayerCameraManager;

	CameraManager->StartCameraFade(1.0f, 0.0f, InDuration, InColor, bFadeAudio, bHoldWhenFinished);
}

void UViewManager::FadeFrom(APlayerController* InController, TFunction<void()> OnComplete, float InDuration, FLinearColor InColor, bool bFadeAudio, bool bHoldWhenFinished)
{
	FadeFrom(InController, InDuration, InColor, bFadeAudio, bHoldWhenFinished);

	auto FadeTimer = GetFadeTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(FadeTimer, [&]()
	{
		OnComplete();
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
		TimerHandleCache.Remove(FadeTimer);
	}, InDuration, false);
}

UUserWidget* UViewManager::Show(APlayerController* InController, TSubclassOf<UUserWidget> InWidgetClass, FViewParameters InParameters, UObject* InContext)
{
	check(InController);
	check(InWidgetClass);

	const auto Widget = GetOrCreateWidget(InController, InWidgetClass);

	TrySetContext(Widget, InContext);

	Widget->AddToViewport();

	SetInputMode(InController, InParameters.InputMode);
	InController->bShowMouseCursor = InParameters.bShowMouse;

	const auto ViewWidget = Cast<UViewWidget>(Widget);
	if(ViewWidget != nullptr)
		ViewWidget->PlayShow();

	return Widget;
}

UUserWidget* UViewManager::ShowInSlot(APlayerController* InController, UUserWidget* InParentWidget,	TSubclassOf<UUserWidget> InWidgetClass, FName InSlotName, FViewParameters InParameters, UObject* InContext)
{
	check(InController);
	check(InParentWidget);
	check(InWidgetClass);

	const auto Widget = GetOrCreateWidget(InController, InWidgetClass);

	TrySetContext(Widget, InContext);
	
	InParentWidget->SetContentForSlot(InSlotName, Widget);

	SetInputMode(InController, InParameters.InputMode);
	InController->bShowMouseCursor = InParameters.bShowMouse;

	const auto ViewWidget = Cast<UViewWidget>(Widget);
	if (ViewWidget != nullptr)
		ViewWidget->PlayShow();

	return Widget;
}

UUserWidget* UViewManager::ShowWindow(APlayerController* InController, TSubclassOf<UWindowWidget> InWindowClass, TSubclassOf<UUserWidget> InContentWidgetClass, FViewParameters InParameters, FWindowParameters InWindowParameters, UObject* InContext)
{
	check(InController);
	check(InWindowClass);
	check(InContentWidgetClass);

	const auto WindowContainerWidget = Cast<UWindowContainerWidget>(GetOrCreateWidget(InController, WindowContainerWidgetClass));

	const TSubclassOf<UUserWidget> WindowClass = InWindowClass;
	const auto WindowWidget = Cast<UWindowWidget>(GetOrCreateWidget(InController, WindowClass));
	
	const auto ContentWidget = ShowInSlot(InController, Cast<UUserWidget>(WindowWidget), InContentWidgetClass, TEXT("WindowContent"), InParameters, InContext);

	TrySetContext(ContentWidget, InContext);
	
	WindowContainerWidget->AddToViewport();
	auto Slot = Cast<UCanvasPanelSlot>(WindowContainerWidget->WindowContainerPanel->AddChildToCanvas(WindowWidget));
	
	if (!InWindowParameters.bCenterOfScreen)
		Slot->SetPosition(InWindowParameters.Position);
	else
	{
		Slot->SetAnchors(FAnchors(0.5f));
		Slot->SetAlignment(FVector2D(0.5f, 0.5f));
		Slot->SetPosition(FVector2D(0.0f, 0.5f));
	}
	
	Slot->SetSize(InWindowParameters.Size);
	
	SetInputMode(InController, InParameters.InputMode);
	InController->bShowMouseCursor = InParameters.bShowMouse;

	auto ViewWidget = Cast<UViewWidget>(WindowWidget);
	if (ViewWidget != nullptr)
		ViewWidget->PlayShow();

	ViewWidget = Cast<UViewWidget>(ContentWidget);
	if (ViewWidget != nullptr)
		ViewWidget->PlayShow();

	return ContentWidget;
}

UUserWidget* UViewManager::GetOrCreateWidget(APlayerController* InController, TSubclassOf<UUserWidget> InWidgetClass)
{
	check(InController->IsLocalController());
	check(InWidgetClass);

	// Check that class isnt a blueprint class

	if (WidgetCache.Contains(InWidgetClass))
		return WidgetCache[InWidgetClass];

	const auto Widget = CreateWidget<UUserWidget>(InController->GetWorld(), InWidgetClass);
	WidgetCache.Add(InWidgetClass, Widget);

	check(Widget);

	return Widget;
}

void UViewManager::SetInputMode(APlayerController* InController, EInputMode InInputMode)
{
	switch (InInputMode)
	{
	case EInputMode::IM_UIOnly:
		InController->SetInputMode(FInputModeUIOnly());
		break;

	case EInputMode::IM_GameAndUI:
		InController->SetInputMode(FInputModeGameAndUI());
		break;

	case EInputMode::IM_GameOnly:
		InController->SetInputMode(FInputModeGameOnly());
		break;
	}
}

void UViewManager::TrySetContext(UUserWidget* InWidget, UObject* InContext)
{
	if (InContext == nullptr)
		return;

	if (InWidget->GetClass()->ImplementsInterface(UHasContextInterface::StaticClass()))
		IHasContextInterface::Execute_SetContext(InWidget, InContext);
}

FTimerHandle& UViewManager::GetFadeTimerHandle()
{
	TimerHandleCache.Add(FTimerHandle());
	return TimerHandleCache.Last();
}