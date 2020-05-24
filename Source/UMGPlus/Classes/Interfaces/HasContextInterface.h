#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "StructBox.h"

#include "HasContextInterface.generated.h"

namespace UMGPlus
{
	namespace detail
	{
		/** From https://forums.unrealengine.com/community/community-content-tools-and-tutorials/27351-tutorial-how-to-accept-wildcard-structs-in-your-ufunctions */
		class FStructHelpers
		{
		public:
			static void ParseProperty(UProperty* Property, void* ValuePtr)
			{
                if (const auto NumericProperty = Cast<UNumericProperty>(Property))
				{
					if (NumericProperty->IsFloatingPoint())
						float FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
					else if (NumericProperty->IsInteger())
						int32 IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
				}
				else if (const auto BoolProperty = Cast<UBoolProperty>(Property))
                    auto BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
				else if (auto NameProperty = Cast<UNameProperty>(Property))
                    auto NameValue = NameProperty->GetPropertyValue(ValuePtr);
				else if (auto StringProperty = Cast<UStrProperty>(Property))
                    auto StringValue = StringProperty->GetPropertyValue(ValuePtr);
				else if (auto TextProperty = Cast<UTextProperty>(Property))
					FText TextValue = TextProperty->GetPropertyValue(ValuePtr);
				else if (const auto ArrayProperty = Cast<UArrayProperty>(Property))
				{
					FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
					for (auto i = 0, n = Helper.Num(); i < n; ++i)
						ParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i));
				}
				else if (const auto StructProperty = Cast<UStructProperty>(Property))
					IterateThroughStructProperty(StructProperty, ValuePtr);
			}

			static void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr)
			{
                const auto Struct = StructProperty->Struct;
				for (TFieldIterator<UProperty> Iterator(Struct); Iterator; ++Iterator)
				{
                    const auto Property = *Iterator;
					auto VariableName = Property->GetName();
					for (auto i = 0; i < Property->ArrayDim; i++)
					{
                        const auto ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, i);
						ParseProperty(Property, ValuePtr);
					}
				}
			}
		};

	}
}

UINTERFACE(Blueprintable, BlueprintType)
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
	/** Return true if context is valid */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	bool GetContext(UObject*& Context) const;
	virtual bool GetContext_Implementation(UObject*& Context) const { return nullptr; }

	template <typename T>
	T* GetContext() const { return Cast<T>(GetContext()); }

	///** Return true if context is valid */
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus", CustomThunk, meta = (CustomStructureParam = "Context", DisplayName = "Get Context (Struct)"))
	//bool GetContext_Struct(UPARAM(Ref) UStructProperty*& Context) const;
	//virtual bool GetContext_Struct_Implementation(UPARAM(Ref) UStructProperty*& Context) const { return false; }

	/*bool GetContext_Struct(FStructBox& Context) const;
	virtual bool GetContext_Struct_Implementation(FStructBox& Context) const { return false; }*/

	//DECLARE_FUNCTION(execGetContext_Struct);

	//const FStructBox GetContext() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	void SetContext(UObject* Context);
	virtual void SetContext_Implementation(UObject* Context) { }

	template <typename T>
	void SetContext(T* Context) { SetContext(Cast<UObject>(Context)); }

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus", CustomThunk, meta = (CustomStructureParam = "Context", DisplayName = "Set Context (Struct)"))
	//void SetContext_Struct(const UStructProperty* Context);
	//virtual void SetContext_Struct_Implementation(const UStructProperty* Context) { }

	/*void SetContext_Struct(const FStructBox& Context);
	virtual void SetContext_Struct_Implementation(const FStructBox& Context) { }*/

	//void SetContext(const FStructBox& Context) { SetContext_Struct(Context); }

	//DECLARE_FUNCTION(execSetContext_Struct);
};
