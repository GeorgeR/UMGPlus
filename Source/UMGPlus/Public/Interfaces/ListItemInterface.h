#pragma once

#include "CoreMinimal.h"

#include "ExpandableInterface.h"

#include "ListItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UListItemInterface
	: public UInterface
{
	GENERATED_BODY()
};

class UMGPLUS_API IListItemInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	void SetIndex(int32 Index);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	int32 GetIndentLevel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	bool HasChildren();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	ESelectionMode::Type GetSelectionMode();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	void RegisterOnClicked();
};