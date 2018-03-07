#pragma once

#include "CoreMinimal.h"
#include "HasContextInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHasContextInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* A UUserWidget can implement this as a convenience to set and get a context. */
/* C++ users can use the templated overloads, however Blueprint users must use the BP functions and cast. */
class UMGPLUS_API IHasContextInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	UObject* GetContext() const;
	virtual UObject* GetContext_Implementation() const { return nullptr; }
	
	template <typename T>
	virtual T* GetContext() const { return Cast<T>(GetContext()); }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	void SetContext(UObject* InContext);
	virtual void SetContext_Implementation(UObject* InContext) { }
	
	template <typename T>
	virtual void SetContext(T* InContext) { SetContext(Cast<UObject>(InContexT)); }
};