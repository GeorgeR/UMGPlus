#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"

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
	template <> ReturnType Name<UClass*>(UClass* WidgetClass, __VA_ARGS__);										\
	template <> ReturnType Name<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, __VA_ARGS__);		\
	template <> ReturnType Name<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, __VA_ARGS__);

#define DECLARE_SPECIALIZATIONS_NO_PARAMS(ReturnType, Name)																		\
	template <> ReturnType Name<UClass*>(UClass* WidgetClass);													\
	template <> ReturnType Name<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass);					\
	template <> ReturnType Name<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass);

UCLASS(Abstract)
class UMGPLUS_API UViewManagerBase
	: public UActorComponent
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

private:
    UUserWidget* ShowInternal(UClass* WidgetClass, const FViewParameters& ViewParameters, const FName& Name = NAME_None, UObject* Context = nullptr);
	void CloseInternal(UClass* WidgetClass, const FName& Name);

public:
	//UWorld* GetWorld() const override;

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
	void TrySetContext(UUserWidget* Widget, UObject* Context) const;

private:
    static bool CheckClassIsWidget(UClass* Class);
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
//

#pragma region Show
template <>
inline UUserWidget* UViewManagerBase::Show<UClass*>(UClass* WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
    const FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
inline UUserWidget* UViewManagerBase::Show<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
    static const FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
inline UUserWidget* UViewManagerBase::Show<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FName& Name, UObject* Context /*= nullptr*/)
{
    static const FViewParameters ViewParameters;
	return Show(WidgetClass, ViewParameters, Name, Context);
}

template <>
inline UUserWidget* UViewManagerBase::Show<UClass*>(UClass* WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	return ShowInternal(WidgetClass, ViewParameters, Name, Context);
}

template <>
inline UUserWidget* UViewManagerBase::Show<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
	return Show(WidgetClass.Get(), ViewParameters, Name, Context);
}

template <>
inline UUserWidget* UViewManagerBase::Show<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FViewParameters& ViewParameters, const FName& Name, UObject* Context /*= nullptr*/)
{
    const auto ResolvedClass = WidgetClass.LoadSynchronous();
	return Show(ResolvedClass, ViewParameters, Name, Context);
}
#pragma endregion Show

#pragma region Close
template <>
inline void UViewManagerBase::Close<UClass*>(UClass* WidgetClass, const FName& Name)
{
	CloseInternal(WidgetClass, Name);
}

template <>
inline void UViewManagerBase::Close<TSubclassOf<UUserWidget>>(TSubclassOf<UUserWidget> WidgetClass, const FName& Name)
{
	return Close(WidgetClass.Get(), Name);
}

template <>
inline void UViewManagerBase::Close<TSoftClassPtr<UUserWidget>>(TSoftClassPtr<UUserWidget> WidgetClass, const FName& Name)
{
    const auto ResolvedClass = WidgetClass.LoadSynchronous();
	return Close(ResolvedClass, Name);
}
#pragma endregion Close

#undef DECLARE_FUNC
#undef DECLARE_FUNC_NO_PARAMS
#undef DECLARE_SPECIALIZATIONS
#undef DECLARE_SPECIALIZATIONS_NO_PARAMS
