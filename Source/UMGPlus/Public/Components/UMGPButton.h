#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"

#include "UMGPButton.generated.h"

UCLASS()
class UMGPLUS_API UUMGPButton
	: public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Style")
	UUMGPStyle* Style;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bWaitForActionOnClick;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};