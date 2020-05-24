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

//UWorld* UViewManagerBase::GetWorld() const
//{
//	return PlayerController->GetWorld();
//}

UUserWidget* UViewManagerBase::ShowInternal(UClass* WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context)
{
	ensure(WidgetClass);
	CheckClassIsWidget(WidgetClass);

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

void UViewManagerBase::CloseInternal(UClass* WidgetClass, const FName& Name)
{
	check(WidgetClass);

	CheckClassIsWidget(WidgetClass);

	UUserWidget* Widget = nullptr;
	if (WidgetCache.TryGet(WidgetClass, Widget, Name))
	{
		const auto ViewWidget = Cast<UViewWidget>(Widget);
		if (ViewWidget != nullptr)
			ViewWidget->Close();
		else
		    Widget->RemoveFromParent();
	}
}

APlayerController* UViewManagerBase::GetPlayerController()
{
	if (this->PlayerController != nullptr)
		return this->PlayerController;

	/* Walk up the tree to find player controller */
	auto Outer = GetOuter();
	while (Outer != nullptr)
	{
		auto OuterPlayerController = Cast<APlayerController>(Outer);
		if (OuterPlayerController != nullptr)
		{
			this->PlayerController = OuterPlayerController;
			return this->PlayerController;
		}
		else
			Outer = Outer->GetOuter();
	}

	// #todo Error
	return nullptr;
}

FTimerHandle& UViewManagerBase::GetFadeTimerHandle()
{
	TimerHandleCache.Add(FTimerHandle());
	return TimerHandleCache.Last();
}

void UViewManagerBase::SetInputMode(EInputMode InputMode)
{
	auto OwningPlayerController = GetPlayerController();
	switch (InputMode)
	{
	case EInputMode::IM_UIOnly:
		OwningPlayerController->SetInputMode(FInputModeUIOnly());
		break;

	case EInputMode::IM_GameAndUI:
		OwningPlayerController->SetInputMode(FInputModeGameAndUI());
		break;

	case EInputMode::IM_GameOnly:
		OwningPlayerController->SetInputMode(FInputModeGameOnly());
		break;
	}
}

void UViewManagerBase::TrySetContext(UUserWidget* Widget, UObject* Context) const
{
	check(Context);

	if (Widget->Implements<UHasContextInterface>())
	{
		auto HasContext = Cast<IHasContextInterface>(Widget);
		HasContext->SetContext(Context);
	}
}

bool UViewManagerBase::CheckClassIsWidget(UClass* Class)
{
	auto Result = false;

	Result = Class->IsChildOf(UUserWidget::StaticClass());

	if (!Result)
		CastLogError(*Class->GetFullName(), *UUserWidget::StaticClass()->GetFullName());
	
	return Result;
}
