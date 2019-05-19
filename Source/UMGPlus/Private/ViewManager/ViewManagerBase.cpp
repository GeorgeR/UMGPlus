#include "ViewManager/ViewManagerBase.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "Interfaces/HasContextInterface.h"
#include "Widgets/ViewWidget.h"

FViewParameters::FViewParameters()
{
	InputMode = EInputMode::IM_GameAndUI;
	bShowMouse = false;
}

FFadeParameters::FFadeParameters()
{
	Duration = 3.0f;
	Color = FLinearColor::Black;
	bFadeAudio = false;
	bHoldWhenFinished = true;
}

void UViewManagerBase::FadeTo(const FFadeParameters& Parameters)
{
	const auto CameraManager = GetPlayerController()->PlayerCameraManager;
	CameraManager->StartCameraFade(0.0f, 1.0f, Parameters.Duration, Parameters.Color, Parameters.bFadeAudio, Parameters.bHoldWhenFinished);
}

void UViewManagerBase::FadeTo(const FFadeParameters& Parameters, TFunction<void()> OnComplete)
{
	checkf(GetWorld(), TEXT("Couldn't get world, UViewManager should be attached to a PlayerController"));

	FadeTo(Parameters);

	auto FadeTimer = GetFadeTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(FadeTimer, [&]()
	{
		OnComplete();
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
		TimerHandleCache.Remove(FadeTimer);
	}, Parameters.Duration, false);
}

void UViewManagerBase::FadeFrom(const FFadeParameters& Parameters)
{
	const auto CameraManager = GetPlayerController()->PlayerCameraManager;
	CameraManager->StartCameraFade(1.0f, 0.0f, Parameters.Duration, Parameters.Color, Parameters.bFadeAudio, Parameters.bHoldWhenFinished);
}

void UViewManagerBase::FadeFrom(const FFadeParameters& Parameters, TFunction<void()> OnComplete)
{
	checkf(GetWorld(), TEXT("Couldn't get world, UViewManager should be attached to a PlayerController"));

	FadeFrom(Parameters);

	auto FadeTimer = GetFadeTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(FadeTimer, [&]()
	{
		// BUG: OnComplete is Unset inside this timer
		OnComplete();
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
		TimerHandleCache.Remove(FadeTimer);
	}, Parameters.Duration, false);
}

#pragma region Show
template <>
UUserWidget* UViewManagerBase::Show<UClass*>(UClass* WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
	FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
UUserWidget* UViewManagerBase::Show<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
	FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
UUserWidget* UViewManagerBase::Show<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
	FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
UUserWidget* UViewManagerBase::Show<UClass*>(UClass* WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	check(WidgetClass);

	ClassIsWidget(WidgetClass);

	const auto Widget = WidgetCache.GetOrCreate(GetPlayerController(), WidgetClass, Name);
	if (Context != nullptr)
		TrySetContext(Widget, Context);

	Widget->AddToViewport();

	SetInputMode(ViewParameters.InputMode);
	GetPlayerController()->bShowMouseCursor = ViewParameters.bShowMouse;

	const auto ViewWidget = Cast<UViewWidget>(Widget);
	if (ViewWidget != nullptr)
		ViewWidget->PlayShow();

	return Widget;
}

template <>
UUserWidget* UViewManagerBase::Show<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	return Show(WidgetClass.Get(), ViewParameters, Name, Context);
}

template <>
UUserWidget* UViewManagerBase::Show<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	auto ResolvedClass = WidgetClass.LoadSynchronous();
	return Show(ResolvedClass, ViewParameters, Name, Context);
}
#pragma endregion Show

#pragma region Close
template <>
void UViewManagerBase::Close<UClass*>(UClass* WidgetClass, const FName& Name)
{
	check(WidgetClass);

	ClassIsWidget(WidgetClass);

	UUserWidget* Widget = nullptr;
	if (WidgetCache.TryGet(WidgetClass, Widget, Name))
		Widget->RemoveFromParent();
}

template <>
void UViewManagerBase::Close<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FName& Name)
{
	return Close(WidgetClass.Get(), Name);
}

template <>
void UViewManagerBase::Close<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FName& Name)
{
	auto ResolvedClass = WidgetClass.LoadSynchronous();
	return Close(ResolvedClass, Name);
}
#pragma endregion Close

UWorld* UViewManagerBase::GetWorld() const
{
	return PlayerController->GetWorld();
}

APlayerController* UViewManagerBase::GetPlayerController()
{
	if (this->PlayerController != nullptr)
		return this->PlayerController;

	/* Walk up the tree to find player controller */
	auto Outer = GetOuter();
	while (Outer != nullptr)
	{
		auto PlayerController = Cast<APlayerController>(Outer);
		if (PlayerController != nullptr)
		{
			this->PlayerController = PlayerController;
			return this->PlayerController;
		}
		else
			Outer = Outer->GetOuter();
	}

	// TODO: Error
	return nullptr;
}

FTimerHandle& UViewManagerBase::GetFadeTimerHandle()
{
	TimerHandleCache.Add(FTimerHandle());
	return TimerHandleCache.Last();
}

void UViewManagerBase::SetInputMode(EInputMode InputMode)
{
	auto PlayerController = GetPlayerController();
	switch (InputMode)
	{
	case EInputMode::IM_UIOnly:
		PlayerController->SetInputMode(FInputModeUIOnly());
		break;

	case EInputMode::IM_GameAndUI:
		PlayerController->SetInputMode(FInputModeGameAndUI());
		break;

	case EInputMode::IM_GameOnly:
		PlayerController->SetInputMode(FInputModeGameOnly());
		break;
	}
}

void UViewManagerBase::TrySetContext(UUserWidget* Widget, UObject* Context)
{
	check(Context);

	if (Widget->Implements<UHasContextInterface>())
	{
		auto HasContext = Cast<IHasContextInterface>(Widget);
		HasContext->SetContext(Context);
	}
}

bool UViewManagerBase::ClassIsWidget(UClass* Class) const
{
	auto Result = false;

	Result = Class->IsChildOf(UUserWidget::StaticClass());

	if (!Result)
		CastLogError(*Class->GetFullName(), *UUserWidget::StaticClass()->GetFullName());
	
	return Result;
}
