#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "ITypedTableView.h"

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
	void SetIndex(int32 InIndex);
	virtual void SetIndex_Implementation(int32 InIndex) { }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	int32 GetIndentLevel();
	virtual int32 GetIndentLevel_Implementation() { return -1; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	bool HasChildren();
	virtual bool HasChildren_Implementation() { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	ESelectionMode::Type GetSelectionMode();
	virtual ESelectionMode::Type GetSelectionMode_Implementation() { return ESelectionMode::Single; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ListItem")
	void RegisterOnClicked();
	virtual void RegisterOnClicked_Implementation() { }
};