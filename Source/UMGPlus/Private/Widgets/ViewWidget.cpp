#include "Widgets/ViewWidget.h"

//#include "WidgetAnimation.h"
#include "MovieScene.h"
#include "Blueprint/WidgetTree.h"
#include "TimerManager.h"

void UViewWidget::PlayShow()
{
	GetTimerManager().ClearTimer(CloseHandle);
	GetTimerManager().ClearTimer(IdleHandle);

	auto AnimationDuration = 0.0f;
	const auto bHasIdleAnimation = GetIdleDuration(AnimationDuration);
	GetShowDuration(AnimationDuration);
	if(bHasIdleAnimation)
		GetTimerManager().SetTimer(ShowHandle, [&]() -> void { PlayIdle(); }, AnimationDuration, false);

	Play(ShowAnimation, false, ShowSpeed);

	ForEachSubWidget([&](UViewWidget* InWidget) -> void { InWidget->PlayShow(); }, false);
}

void UViewWidget::PlayIdle()
{
	Play(IdleAnimation, true, IdleSpeed);

	ForEachSubWidget([&](UViewWidget* InWidget) -> void { InWidget->PlayIdle(); }, false);
}

void UViewWidget::PlayClose()
{
	Play(CloseAnimation, false, CloseSpeed);

	ForEachSubWidget([&](UViewWidget* InWidget) -> void { InWidget->PlayClose(); }, false);
}

void UViewWidget::Close()
{
	GetTimerManager().ClearTimer(ShowHandle);
	GetTimerManager().ClearTimer(IdleHandle);
	GetTimerManager().ClearTimer(CloseHandle);

	auto PlayerController = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}

	auto AnimationDuration = 0.0f;
	if (GetCloseDuration(AnimationDuration))
	{
		this->PlayClose();
		GetTimerManager().SetTimer(CloseHandle, [&]() -> void {
			GetTimerManager().ClearTimer(CloseHandle);
			RemoveFromParent();
			if (OnClose.IsBound())
				OnClose.Broadcast();
		}, AnimationDuration, false);
	}
	else
		RemoveFromParent();
}

bool UViewWidget::Initialize()
{
	const auto bResult = Super::Initialize();

	GetSubWidgets(SubWidgets);
	CacheAnimations();
	if(CachedAnimations.Num() > 0)
	{
		ShowAnimation = GetNamedAnimation(TEXT("Show"));
		IdleAnimation = GetNamedAnimation(TEXT("Idle"));
		CloseAnimation = GetNamedAnimation(TEXT("Close"));
	}

	return bResult;
}

void UViewWidget::Play(UWidgetAnimation* InAnimation, bool bLoop, float InSpeed)
{
	if (InAnimation != nullptr)
		PlayAnimation(InAnimation, 0.0f, bLoop ? 0 : 1, EUMGSequencePlayMode::Forward, InSpeed);
}

UWidgetAnimation* UViewWidget::GetNamedAnimation(const FName InAnimationName)
{
	if (CachedAnimations.Contains(InAnimationName))
		return CachedAnimations[InAnimationName];

	return nullptr;
}

bool UViewWidget::GetShowDuration(float& OutDuration)
{
	return GetAnimationDuration([&](UViewWidget* InWidget) -> UWidgetAnimation*{ return InWidget->ShowAnimation; }, OutDuration);
}

bool UViewWidget::GetIdleDuration(float& OutDuration)
{
	return GetAnimationDuration([&](UViewWidget* InWidget) -> UWidgetAnimation* { return InWidget->IdleAnimation; }, OutDuration);
}

bool UViewWidget::GetCloseDuration(float& OutDuration)
{
	return GetAnimationDuration([&](UViewWidget* InWidget) -> UWidgetAnimation* { return InWidget->CloseAnimation; }, OutDuration);
}

bool UViewWidget::GetAnimationDuration(TFunction<UWidgetAnimation*(UViewWidget*)> InSelector, float& OutDuration)
{
	auto bHasAnimation = false;
	if(InSelector(this) != nullptr)
	{
		OutDuration = FMath::Max(OutDuration, InSelector(this)->GetEndTime());
		bHasAnimation = true;
	}

	ForEachSubWidget([&](UViewWidget* InWidget) -> void {
		if(InSelector(InWidget) != nullptr)
		{
			OutDuration = FMath::Max(OutDuration, InSelector(InWidget)->GetEndTime());
			bHasAnimation = true;
		}
	}, false);

	return bHasAnimation;
}

void UViewWidget::ForEachSubWidget(TFunction<void(UViewWidget*)> InFunc, bool bIncludeThis)
{
	if (bIncludeThis)
		InFunc(this);

	for (auto i = 0; i < SubWidgets.Num(); i++)
		InFunc(SubWidgets[i]);
}

void UViewWidget::CacheAnimations()
{
	if(CachedAnimations.Num() == 0)
	{
		auto Property = GetClass()->PropertyLink;
		while (Property != nullptr)
		{
			if (Property->GetClass() == UObjectProperty::StaticClass())
			{
				const auto ObjectProperty = Cast<UObjectProperty>(Property);
				if (ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					const auto Object = ObjectProperty->GetObjectPropertyValue_InContainer(this);
					auto WidgetAnimation = Cast<UWidgetAnimation>(Object);

					if (WidgetAnimation != nullptr)
					{
						const auto Name = WidgetAnimation->GetMovieScene()->GetFName();
						CachedAnimations.Add(Name, WidgetAnimation);
					}
				}
			}
			Property = Property->PropertyLinkNext;
		}
	}
}

void UViewWidget::GetSubWidgets(TArray<UViewWidget*>& OutWidgets)
{
	if(SubWidgets.Num() == 0)
	{
		TArray<UWidget*> AllWidgets;
		WidgetTree->GetAllWidgets(AllWidgets);
		for (auto Widget : AllWidgets)
		{
			auto SubWidget = Cast<UViewWidget>(Widget);
			if (SubWidget != nullptr)
			{
				OutWidgets.AddUnique(SubWidget);
				SubWidgets.AddUnique(SubWidget);

				SubWidget->GetSubWidgets(OutWidgets);
			}
		}
	}
	else
		OutWidgets.Append(SubWidgets);
}
