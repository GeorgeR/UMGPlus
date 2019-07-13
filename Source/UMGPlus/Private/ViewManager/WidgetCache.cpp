#include "WidgetCache.h"

#include "UserWidget.h"

FWidgetCacheKey::FWidgetCacheKey()
	: Class(nullptr),
	Name(NAME_None) { }

FWidgetCacheKey::FWidgetCacheKey(const TSubclassOf<UUserWidget> InWidgetClass, const FName& InInstanceName /*= NAME_None*/)
	: Class(InWidgetClass),
	Name(InInstanceName)
{
	if (!InWidgetClass->IsChildOf(UUserWidget::StaticClass()))
		CastLogError(*InWidgetClass->GetFullName(), *UUserWidget::StaticClass()->GetFullName());
}

bool FWidgetCacheKey::operator==(const FWidgetCacheKey& Other) const { return Class == Other.Class; }
bool FWidgetCacheKey::operator!=(const FWidgetCacheKey& Other) const { return !(*this == Other); }

UUserWidget* FWidgetCache::GetOrCreate(APlayerController* InPlayerController, const TSubclassOf<UUserWidget> InWidgetClass, const FName& InInstanceName /*= NAME_None*/)
{
	check(InPlayerController);
	check(InPlayerController != InPlayerController->GetClass()->ClassDefaultObject);
	check(InPlayerController->GetWorld());
	check(InPlayerController->IsLocalController());
	
	check(InWidgetClass);

    const auto CacheKey = FWidgetCacheKey(InWidgetClass, InInstanceName);
	UUserWidget* Widget = nullptr;
	if (!TryGet(CacheKey, Widget))
	{
		Widget = CreateWidget<UUserWidget>(InPlayerController->GetWorld(), InWidgetClass);
		Items.Add(CacheKey, Widget);
		check(Widget);
	}
	
	return Widget;
}

bool FWidgetCache::TryGet(const TSubclassOf<UUserWidget> InWidgetClass, UUserWidget*& OutWidget, const FName& InInstanceName /*= NAME_None*/)
{
    const auto CacheKey = FWidgetCacheKey(InWidgetClass, InInstanceName);
	return TryGet(CacheKey, OutWidget);
}

bool FWidgetCache::TryGet(const FWidgetCacheKey& InCacheKey, UUserWidget*& OutWidget)
{
	if (Items.Contains(InCacheKey))
	{
		if (Items[InCacheKey] == nullptr)
		{
			Items.Remove(InCacheKey);
			return false;
		}

		OutWidget = Items[InCacheKey];
		return true;
	}

	return false;
}
