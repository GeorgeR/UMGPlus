#include "ViewManager.h"
#include "HasContextInterface.h"
#include "ViewWidget.h"
#include "WindowWidget.h"

UViewManager* UViewManager::Instance = nullptr;

UViewManager::UViewManager()
{
	Instance = this;
}

UViewManager* UViewManager::Get()
{
	if(Instance == nullptr)
		NewObject<UViewManager>();
	
	return Instance;
}

UUserWidget* UViewManager::Show(APlayerController* InController, TSubclassOf<UUserWidget> InWidgetClass, FViewParameters InParameters, UObject* InContext)
{
	check(InController);
	check(InWidgetClass);

	const auto Widget = GetOrCreateWidget(InController, InWidgetClass);

	if(InContext != nullptr)
	{
		const auto HasContext = Cast<IHasContextInterface>(Widget);
		if (HasContext != nullptr)
			IHasContextInterface::Execute_SetContext(Widget, InContext);
	}

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

	if (InContext != nullptr)
	{
		const auto HasContext = Cast<IHasContextInterface>(Widget);
		if (HasContext != nullptr)
			IHasContextInterface::Execute_SetContext(Widget, InContext);
	}

	InParentWidget->SetContentForSlot(InSlotName, Widget);

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

	const TSubclassOf<UUserWidget> WindowClass = InWindowClass;
	const auto WindowWidget = Cast<UWindowWidget>(GetOrCreateWidget(InController, WindowClass));

	const auto ContentWidget = ShowInSlot(InController, Cast<UUserWidget>(WindowWidget), InContentWidgetClass, TEXT("WindowContent"), InParameters, InContext);

	if (InContext != nullptr)
	{
		const auto HasContext = Cast<IHasContextInterface>(ContentWidget);
		if (HasContext != nullptr)
			IHasContextInterface::Execute_SetContext(ContentWidget, InContext);
	}

	WindowWidget->AddToViewport();

	if (!InWindowParameters.bCenterOfScreen)
		WindowWidget->SetPositionInViewport(InWindowParameters.Position);
	else
	{
		WindowWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		WindowWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		WindowWidget->SetPositionInViewport(FVector2D(0.0f, 0.0f));
	}
	
	WindowWidget->SetDesiredSizeInViewport(InWindowParameters.Size);

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

	const auto Widget = CreateWidget<UUserWidget>(InController, InWidgetClass);
	WidgetCache.Add(InWidgetClass, Widget);

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