#pragma once

#include "CoreMinimal.h"

#include "WidgetCache.generated.h"

class UUserWidget;

USTRUCT()
struct FWidgetCacheKey
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UClass* Class;

	UPROPERTY()
	FName Name;

	FWidgetCacheKey();

	FWidgetCacheKey(UClass* Class, const FName& Name = NAME_None);

	bool operator==(const FWidgetCacheKey& Other) const;
	bool operator!=(const FWidgetCacheKey& Other) const;

	friend inline uint32 GetTypeHash(const FWidgetCacheKey& Value)
	{
		return HashCombine(GetTypeHash(Value.Class), GetTypeHash(Value.Name));
	}

	FORCEINLINE bool IsValid() const
	{
		return Class != nullptr;
	}
};

USTRUCT()
struct FWidgetCache
{
	GENERATED_BODY()

public:
	UUserWidget* GetOrCreate(APlayerController* PlayerController, TSubclassOf<UUserWidget> WidgetClass, const FName& Name = NAME_None);
	bool TryGet(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, const FName& Name = NAME_None);

private:
	UPROPERTY()
	TMap<FWidgetCacheKey, UUserWidget*> Items;

	bool TryGet(const FWidgetCacheKey& CacheKey, UUserWidget* Widget);
};
