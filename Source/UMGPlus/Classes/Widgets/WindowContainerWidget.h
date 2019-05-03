#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CanvasPanel.h"
#include "BackgroundBlur.h"
#include "Border.h"

#include "ViewWidget.h"

#include "WindowContainerWidget.generated.h"

UCLASS(BlueprintType)
class UMGPLUS_API UWindowContainerWidget 
	: public UViewWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* WindowContainerPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBackgroundBlur* Blur;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bUseBlur;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float BlurAmount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* WashBorder;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bUseWash;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor WashColor;

	UWindowContainerWidget();
};