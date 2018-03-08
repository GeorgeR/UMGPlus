#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "ViewWidget.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UMGPLUS_API UViewWidget
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ShowSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float IdleSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CloseSpeed = 1.0f;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShow);
	UPROPERTY(BlueprintAssignable)
	FOnShow OnShow;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClose);
	UPROPERTY(BlueprintAssignable)
	FOnClose OnClose;

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void PlayShow();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void PlayIdle();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void PlayClose();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void Close();

	bool Initialize() override;

protected:
	UPROPERTY(Transient)
	UWidgetAnimation* ShowAnimation;
	
	UPROPERTY(Transient)
	UWidgetAnimation* IdleAnimation;
	
	UPROPERTY(Transient)
	UWidgetAnimation* CloseAnimation;

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void Play(UWidgetAnimation* InAnimation, bool bLoop = false, float InSpeed = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	UWidgetAnimation* GetNamedAnimation(const FName InAnimationName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMGPlus")
	bool GetShowDuration(float& OutDuration);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMGPlus")
	bool GetIdleDuration(float& OutDuration);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMGPlus")
	bool GetCloseDuration(float& OutDuration);

	bool GetAnimationDuration(TFunction<UWidgetAnimation*(UViewWidget*)> InSelector, float& OutDuration);

	void ForEachSubWidget(TFunction<void(UViewWidget*)> InFunc, bool bIncludeThis = true);

	FTimerManager& GetTimerManager() const { return GetWorld()->GetTimerManager(); }

private:
	FTimerHandle ShowHandle;
	FTimerHandle IdleHandle;
	FTimerHandle CloseHandle;

	UPROPERTY(Transient)
	TMap<FName, UWidgetAnimation*> CachedAnimations;

	void CacheAnimations();

	UPROPERTY(Transient)
	TArray<UViewWidget*> SubWidgets;

	void GetSubWidgets(TArray<UViewWidget*>& OutWidgets);
};