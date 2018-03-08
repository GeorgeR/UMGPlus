#pragma once

#include "CoreMinimal.h"

#include "SelectorInterface.generated.h"

UINTERFACE(MinimalAPI)
class USelectorInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class UMGPLUS_API ISelectorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetSelectedIndex();
	virtual int32 GetSelectedIndex_Implementation() { return -1; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UObject* GetSelectedItem();
	virtual UObject* GetSelectedItem_Implementation() { return nullptr; }

	/* Returns false if there is no selection. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetSelectedItems(TArray<UObject*>& OutItems);
	virtual bool GetSelectedItems_Implementation(TArray<UObject*>& OutItems) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsSelected(const UObject* InItem) const;
	virtual bool IsSelected_Implementation(const UObject* InItem) const { return false; }
};