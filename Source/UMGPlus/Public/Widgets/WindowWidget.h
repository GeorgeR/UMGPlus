// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/ViewWidget.h"
#include "Border.h"
#include "CanvasPanelSlot.h"
#include "Button.h"

#include "WindowWidget.generated.h"

USTRUCT(BlueprintType)
struct UMGPLUS_API FWindowParameters
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCenterOfScreen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint Position;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint Size;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText TitleText;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bClampToViewport;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bMoveable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bResizeable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsCloseable;

	FWindowParameters();
};

UCLASS(BlueprintType)
class UMGPLUS_API UWindowWidget
	: public UViewWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UBorder* TitleBorder;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UBorder* ResizeBorder;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* WindowContent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText TitleText;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bHasFocus;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bClampToViewport;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bMoveable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bResizeable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsCloseable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector2D MinSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector2D MaxSize;

	UWindowWidget();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void SetParameters(FWindowParameters& InParameters);

protected:
	void NativeConstruct() override;

private:
	UPROPERTY()
	UCanvasPanelSlot* RootSlot;

	FVector2D LastMousePosition;
	FVector2D DesiredSize;
	bool bIsMouseButtonDown;
	bool bIsForResize;

	UFUNCTION()
	FEventReply OnTitleMouseDown(FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	FEventReply OnTitleMouseMove(FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	FEventReply OnTitleMouseUp(FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	void DragPosition(const FVector2D& InMouseDelta);
	void DragSize(const FVector2D& InMouseDelta);
	inline bool IsMouseInViewport(const FPointerEvent& InPointerEvent);
	inline FVector2D GetViewportSize();
	inline float GetViewportScale();
	inline void GetMouseInViewportSpace(const FPointerEvent& InPointerEvent, FVector2D& OutPixelPosition,
	                                    FVector2D& OutViewportPosition);

protected:
	FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath,
	                           const FFocusEvent& InFocusEvent) override;
};