#include "UMGPStyleCollectionFactory.h"
#include "UMGPStyleCollection.h"

UUMGPStyleCollectionFactory::UUMGPStyleCollectionFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UUMGPStyleCollection::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UUMGPStyleCollectionFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UUMGPStyleCollection* Result = NewObject<UUMGPStyleCollection>(InParent, InClass, InName, Flags);

	return Result;
}