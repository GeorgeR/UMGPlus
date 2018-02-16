#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"

#include "UMGPStyleCollectionFactory.generated.h"

UCLASS()
class UUMGPStyleCollectionFactory 
	: public UFactory
{
	GENERATED_BODY()

public:
	UUMGPStyleCollectionFactory(const FObjectInitializer& ObjectInitializer);
	
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};