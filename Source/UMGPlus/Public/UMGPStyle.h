#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Widget.h"

#include "UMGPStyle.generated.h"

UCLASS()
class UMGPLUS_API UUMGPStyle 
	: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Selector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FName, FString> Properties;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TArray<UUMGPStyle*> Children;

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	FString GetPropertyAsString(FName InKey);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	float GetPropertyAsFloat(FName InKey);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	int32 GetPropertyAsInteger(FName InKey);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	FVector GetPropertyAsVector(FName InKey);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	bool HasProperty(FName InKey);

	UFUNCTION(BlueprintCallable, Category = "UMGPlus")
	void ApplyTo(UWidget* InWidget);

	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void Update();

private:
	UPROPERTY()
	TArray<TSubclassOf<UWidget>> Widgets;

	UPROPERTY()
	TArray<FName> Ids;

	UPROPERTY()
	TArray<FName> Classes;

	bool ParseSelector();
};