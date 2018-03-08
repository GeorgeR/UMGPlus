#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

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
	virtual void SetSelected_Implementation(bool bSelected) { }
};