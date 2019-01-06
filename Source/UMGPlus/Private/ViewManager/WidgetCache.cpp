#include "WidgetCache.h"

#include "UserWidget.h"

FWidgetCacheKey::FWidgetCacheKey()
	: Class(nullptr),
	Name(NAME_None) { }

FWidgetCacheKey::FWidgetCacheKey(UClass* Class, const FName& Name /*= NAME_None*/)
	: Class(Class),
	Name(Name)
{
	if (!Class->IsChildOf(UUserWidget::StaticClass()))
		CastLogError(*Class->GetFullName(), *UUserWidget::StaticClass()->GetFullName());
}

bool FWidgetCacheKey::operator==(const FWidgetCacheKey& Other) const { return Class == Other.Class; }
bool FWidgetCacheKey::operator!=(const FWidgetCacheKey& Other) const { return !(*this == Other); }

UUserWidget* FWidgetCache::GetOrCreate(APlayerController* PlayerController, TSubclassOf<UUserWidget> WidgetClass, const FName& Name /*= NAME_None*/)
{
	check(PlayerController);
	check(PlayerController->IsLocalController());
	check(PlayerController->GetWorld());
	check(WidgetClass);

	auto CacheKey = FWidgetCacheKey(WidgetClass, Name);
	UUserWidget* Widget = nullptr;
	if (!TryGet(CacheKey, Widget))
	{
		Widget = CreateWidget<UUserWidget>(PlayerController->GetWorld(), WidgetClass);
		Items.Add(CacheKey, Widget);
		check(Widget);
	}
	
	return Widget;
}

bool FWidgetCache::TryGet(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, const FName& Name /*= NAME_None*/)
{
	auto CacheKey = FWidgetCacheKey(WidgetClass, Name);
	return TryGet(CacheKey, Widget);
}

bool FWidgetCache::TryGet(const FWidgetCacheKey& CacheKey, UUserWidget* Widget)
{
	if (Items.Contains(CacheKey))
	{
		if (Items[CacheKey] == nullptr)
		{
			Items.Remove(CacheKey);
			return false;
		}

		Widget = Items[CacheKey];
		return true;
	}

	return false;
}
