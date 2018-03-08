#pragma once

#include "CoreMinimal.h"

#include "ExpandableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UExpandableInterface
	: public UInterface
{
	GENERATED_BODY()
};

class UMGPLUS_API IExpandableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	bool IsExpanded() const;
	virtual bool IsExpanded_Implementation() const { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	void Expand();
	virtual void Expand_Implementation() { }
};