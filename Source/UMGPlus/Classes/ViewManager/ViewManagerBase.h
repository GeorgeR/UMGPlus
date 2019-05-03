#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "WidgetCache.h"

#include "ViewManagerBase.generated.h"

class UWorld;

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

USTRUCT(BlueprintType)
struct UMGPLUS_API FFadeParameters
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fade")
	float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fade")
	FLinearColor Color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fade")
	bool bFadeAudio;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fade")
	bool bHoldWhenFinished;

	FFadeParameters();
};

#define DECLARE_FUNC(ReturnType, Name, ...)																						\
	template <typename TWidgetClass> ReturnType Name(TWidgetClass WidgetClass, __VA_ARGS__);			

#define DECLARE_FUNC_NO_PARAMS(ReturnType, Name)																				\
	template <typename TWidgetClass> ReturnType Name(TWidgetClass WidgetClass);		

/* Seperate because a specialization can't have default args */
#define DECLARE_SPECIALIZATIONS(ReturnType, Name, ...)																			\
	template <> UMGPLUS_API ReturnType Name<UClass*>(UClass* WidgetClass, __VA_ARGS__);										\
	template <> UMGPLUS_API ReturnType Name<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, __VA_ARGS__);		\
	template <> UMGPLUS_API ReturnType Name<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, __VA_ARGS__);

#define DECLARE_SPECIALIZATIONS_NO_PARAMS(ReturnType, Name)																		\
	template <> UMGPLUS_API ReturnType Name<UClass*>(UClass* WidgetClass);													\
	template <> UMGPLUS_API ReturnType Name<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass);					\
	template <> UMGPLUS_API ReturnType Name<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass);

UCLASS(Abstract, MinimalAPI)
class UViewManagerBase
	: public UObject
{
	GENERATED_BODY()

public:
	virtual void FadeTo(const FFadeParameters& Parameters);
	virtual void FadeTo(const FFadeParameters& Parameters, TFunction<void()> OnComplete);

	virtual void FadeFrom(const FFadeParameters& Parameters);
	virtual void FadeFrom(const FFadeParameters& Parameters, TFunction<void()> OnComplete);

	DECLARE_FUNC(UUserWidget*, Show, const FName& Name = NAME_None, UObject* Context = nullptr)
	DECLARE_SPECIALIZATIONS(UUserWidget*, Show, const FName& Name, UObject* Context)

	DECLARE_FUNC(UUserWidget*, Show, const FViewParameters& ViewParameters, const FName& Name = NAME_None, UObject* Context = nullptr)
	DECLARE_SPECIALIZATIONS(UUserWidget*, Show, const FViewParameters& ViewParameters, const FName& Name, UObject* Context)

	DECLARE_FUNC(void, Close, const FName& Name = NAME_None)
	DECLARE_SPECIALIZATIONS(void, Close, const FName& Name)

	DECLARE_FUNC(UUserWidget*, Toggle, const FName& Name = NAME_None, UObject* Context = nullptr)
	DECLARE_SPECIALIZATIONS(UUserWidget*, Toggle, const FName& Name, UObject* Context)

	DECLARE_FUNC(UUserWidget*, Toggle, const FViewParameters& ViewParameters, const FName& Name = NAME_None, UObject* Context = nullptr)
	DECLARE_SPECIALIZATIONS(UUserWidget*, Toggle, const FViewParameters& ViewParameters, const FName& Name, UObject* Context)

	//template <typename TWidget>
	//FORCEINLINE TWidget* Show(FViewParameters Parameters);

	//template <typename TWidget, typename TContext>
	//FORCEINLINE TWidget* Show(FViewParameters Parameters, TContext* Context);

public:
	UWorld* GetWorld() const override;

protected:
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerController;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMGPlus|ViewManager")
	APlayerController* GetPlayerController();

	UPROPERTY()
	FWidgetCache WidgetCache;

protected:
	TArray<FTimerHandle> TimerHandleCache;
	FTimerHandle& GetFadeTimerHandle();

	void SetInputMode(EInputMode InputMode);
	void TrySetContext(UUserWidget* Widget, UObject* Context);

private:
	bool ClassIsWidget(UClass* Class) const;
};

//template <typename TWidget>
//TWidget* UViewManagerBase::Show(FViewParameters Parameters)
//{
//	return Cast<TWidget>(Show(TWidget::StaticClass(), Parameters));
//}
//
//template <typename TWidget, typename TContext>
//TWidget* UViewManagerBase::Show(FViewParameters Parameters, TContext* Context)
//{
//	return Cast<TWidget>(Show(TWidget::StaticClass(), Parameters, Context));
//}

#undef DECLARE_FUNC
#undef DECLARE_FUNC_NO_PARAMS
#undef DECLARE_SPECIALIZATIONS
#undef DECLARE_SPECIALIZATIONS_NO_PARAMS
