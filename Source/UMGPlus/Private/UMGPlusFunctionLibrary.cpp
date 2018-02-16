#include "UMGPlusFunctionLibrary.h"
#include "EngineMinimal.h"

UUMGPStyleCollection* UUMGPlusFunctionLibrary::GetStyleCollection()
{
	for (TObjectIterator<UUMGPStyleCollection> Iterator; Iterator; ++Iterator)
		return *Iterator;

	return nullptr;
}

TSubclassOf<UWidget> UUMGPlusFunctionLibrary::GetWidgetFromString(FString& InStr)
{
	UClass* Result = FindObject<UClass>(ANY_PACKAGE, *InStr);
	return Result;
}