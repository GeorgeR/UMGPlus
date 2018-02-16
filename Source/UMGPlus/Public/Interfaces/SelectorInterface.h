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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UObject* GetSelectedItem();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetSelectedItems(TArray<UObject*>& Items);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsSelected(UObject* Item);
};