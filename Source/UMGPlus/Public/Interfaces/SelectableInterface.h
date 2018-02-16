#pragma once

#include "CoreMinimal.h"

#include "SelectableInterface.generated.h"

UINTERFACE(MinimalAPI)
class USelectableInterface
	: public UInterface
{
	GENERATED_BODY()
};

class UMGPLUS_API ISelectableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	void SetSelected(bool bSelected);
};