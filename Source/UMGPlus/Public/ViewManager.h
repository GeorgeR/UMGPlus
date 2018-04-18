#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Widgets/WindowWidget.h"
#include "WindowContainerWidget.h"

#include "ViewManager.generated.h"

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	IM_UIOnly			UMETA(DisplayName = "UI only"),
	IM_GameAndUI		UMETA(DisplayName = "Game and UI"),
	IM_GameOnly			UMETA(DisplayName = "Game only")
};

USTRUCT(BlueprintType)
struct UMGPLUS_API FViewParameters
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInputMode InputMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bShowMouse;

	FViewParameters();
};

/* It's recommended you attach this to GameInstance and call it via Get() */
UCLASS(BlueprintType)
class UMGPLUS_API UViewManager
	: public UObject
{
	GENERATED_BODY()
	
public:
	UViewManager();

	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	static UViewManager* Get();

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
	static UViewManager* Instance;

	UPROPERTY(Transient)
	TMap<UClass*, UUserWidget*> WidgetCache;

	UPROPERTY()
	TSubclassOf<UWindowContainerWidget> WindowContainerWidgetClass;
	
	UFUNCTION(BlueprintCallable, Category = "ViewManager")
	UUserWidget* GetOrCreateWidget(APlayerController* InController, TSubclassOf<UUserWidget> InWidgetClass);

	static void SetInputMode(APlayerController* InController, EInputMode InInputMode);

	static void TrySetContext(UUserWidget* InWidget, UObject* InContext);

	TArray<FTimerHandle> TimerHandleCache;
	FTimerHandle& GetFadeTimerHandle();
};