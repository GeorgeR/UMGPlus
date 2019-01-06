#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "ViewManagerBase.h"
#include "Widgets/WindowWidget.h"
#include "WindowContainerWidget.h"

#include "ViewManager.generated.h"

/* This should be a descendent of your PlayerController */
UCLASS(BlueprintType, Blueprintable)
class UMGPLUS_API UViewManager
	: public UViewManagerBase
{
	GENERATED_BODY()

public:
	UViewManager();

public:
	UFUNCTION(BlueprintCallable, Category = "UMGPlus|ViewManager")
	virtual void FadeTo(const FFadeParameters& Parameters) override { Super::FadeTo(Parameters); }

	UFUNCTION(BlueprintCallable, Category = "UMGPlus|ViewManager")
	virtual void FadeFrom(const FFadeParameters& Parameters) override { Super::FadeTo(Parameters); }

	UFUNCTION(BlueprintCallable, Category = "UMGPlus|ViewManager", meta = (DisplayName = "Show"))
	virtual UUserWidget* Show_BP(TSubclassOf<UUserWidget> WidgetClass, const FViewParameters& Parameters, const FName& Name = NAME_None, UObject* Context = nullptr);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus|ViewManager", meta = (DisplayName = "Show"))
	UUserWidget* Show_BP_FromReference(TSoftClassPtr<UUserWidget> WidgetClass, const FViewParameters& Parameters, const FName& Name = NAME_None, UObject* Context = nullptr);
};

/*
UCLASS(BlueprintType)
class UMGPLUS_API UViewManager
	: public UObject
{
	GENERATED_BODY()
	
public:
	UViewManager();



	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	void FadeTo(APlayerController* InController, float InDuration = 3.0f, FLinearColor InColor = FLinearColor::Black, bool bFadeAudio = false, bool bHoldWhenFinished = true);
	void FadeTo(APlayerController* InController, TFunction<void()> OnComplete, float InDuration = 3.0f, FLinearColor InColor = FLinearColor::Black, bool bFadeAudio = false, bool bHoldWhenFinished = true);

	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	void FadeFrom(APlayerController* InController, float InDuration = 3.0f, FLinearColor InColor = FLinearColor::Black, bool bFadeAudio = false, bool bHoldWhenFinished = true);
	void FadeFrom(APlayerController* InController, TFunction<void()> OnComplete, float InDuration = 3.0f, FLinearColor InColor = FLinearColor::Black, bool bFadeAudio = false, bool bHoldWhenFinished = true);
	
	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	UUserWidget* Show(APlayerController* InController, TSubclassOf<UUserWidget> InWidgetClass, FViewParameters InParameters, UObject* InContext = nullptr);

	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	UUserWidget* ShowInSlot(APlayerController* InController, UUserWidget* InParentWidget, TSubclassOf<UUserWidget> InWidgetClass, FName InSlotName, FViewParameters InParameters, UObject* InContext = nullptr);

	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	UUserWidget* ShowWindow(APlayerController* InController, TSubclassOf<UWindowWidget> InWindowClass, TSubclassOf<UUserWidget> InContentWidgetClass, FViewParameters InParameters, FWindowParameters InWindowParameters, UObject* InContext = nullptr);

private:
	



	UPROPERTY()
	TSubclassOf<UWindowContainerWidget> WindowContainerWidgetClass;
	
	

	static void SetInputMode(APlayerController* InController, EInputMode InInputMode);

	static void TrySetContext(UUserWidget* InWidget, UObject* InContext);

	TArray<FTimerHandle> TimerHandleCache;
	FTimerHandle& GetFadeTimerHandle();
};
*/
