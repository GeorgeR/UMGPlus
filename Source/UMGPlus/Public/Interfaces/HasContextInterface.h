#pragma once

#include "CoreMinimal.h"

#include "HasContextInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHasContextInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class UMGPLUS_API IHasContextInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	void SetContext(UObject* InContext);
};