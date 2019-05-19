#include "ViewManager/ViewManager.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "Interfaces/HasContextInterface.h"
#include "Widgets/ViewWidget.h"
#include "Widgets/WindowWidget.h"

UViewManager::UViewManager()
{
	//WindowContainerWidgetClass = LoadClass<UWindowContainerWidget>(this, TEXT("WidgetBlueprint'/UMGPlus/WBP_WindowContainer.WBP_WindowContainer_C'"));
}

UUserWidget* UViewManager::Show_BP(TSubclassOf<UUserWidget> WidgetClass, const FViewParameters& Parameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	return Super::Show(WidgetClass, Parameters, Name, Context);
}

UUserWidget* UViewManager::Show_BP_FromReference(TSoftClassPtr<UUserWidget> WidgetClass, const FViewParameters& Parameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	return Super::Show(WidgetClass, Parameters, Name, Context);
}

/*
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
*/
