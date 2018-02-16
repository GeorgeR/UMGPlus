#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMGPStyleCollection.h"

#include "UMGPlusFunctionLibrary.generated.h"

UCLASS()
class UMGPLUS_API UUMGPlusFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	static UUMGPStyleCollection* GetStyleCollection();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	static TSubclassOf<UWidget> GetWidgetFromString(FString& InStr);
};