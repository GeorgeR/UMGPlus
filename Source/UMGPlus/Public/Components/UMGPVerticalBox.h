#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "UMGPStyle.h"

#include "UMGPVerticalBox.generated.h"

UCLASS()
class UMGPLUS_API UUMGPVerticalBox 
	: public UVerticalBox
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Style")
	UUMGPStyle* Style;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void OnSlotAdded(UPanelSlot* Slot) override;
};