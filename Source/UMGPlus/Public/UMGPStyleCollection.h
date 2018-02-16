#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMGPStyle.h"

#include "UMGPStyleCollection.generated.h"

UCLASS()
class UMGPLUS_API UUMGPStyleCollection 
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TArray<UUMGPStyle*> Styles;

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	static UUMGPStyleCollection* GetDefault();

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void ApplyTo(UWidget* InWidget);

private:
	static UUMGPStyleCollection* Default;

	TArray<UUMGPStyle*> GetStylesForWidget(UWidget* InWidget);
};