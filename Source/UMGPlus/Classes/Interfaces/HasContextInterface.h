#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

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
				float FloatValue;
				int32 IntValue;
				bool BoolValue;
				FString StringValue;
				FName NameValue;
				FText TextValue;

				if (auto NumericProperty = Cast<UNumericProperty>(Property))
				{
					if (NumericProperty->IsFloatingPoint())
						FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
					else if (NumericProperty->IsInteger())
						IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
				}
				else if (auto BoolProperty = Cast<UBoolProperty>(Property))
					BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
				else if (auto NameProperty = Cast<UNameProperty>(Property))
					NameValue = NameProperty->GetPropertyValue(ValuePtr);
				else if (auto StringProperty = Cast<UStrProperty>(Property))
					StringValue = StringProperty->GetPropertyValue(ValuePtr);
				else if (auto TextProperty = Cast<UTextProperty>(Property))
					TextValue = TextProperty->GetPropertyValue(ValuePtr);
				else if (auto ArrayProperty = Cast<UArrayProperty>(Property))
				{
					FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
					for (auto i = 0, n = Helper.Num(); i < n; ++i)
						ParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i));
				}
				else if (auto StructProperty = Cast<UStructProperty>(Property))
					IterateThroughStructProperty(StructProperty, ValuePtr);
			}

			static void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr)
			{
				auto Struct = StructProperty->Struct;
				for (TFieldIterator<UProperty> Iterator(Struct); Iterator; ++Iterator)
				{
					auto Property = *Iterator;
					auto VariableName = Property->GetName();
					for (auto i = 0; i < Property->ArrayDim; i++)
					{
						void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, i);
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

	/** Return true if context is valid */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus", meta = (DisplayName = "Get Context (Struct)"))
	bool GetContext_Struct(FStructBox& Context) const;
	virtual bool GetContext_Struct_Implementation(FStructBox& Context) const { return false; }

	////DECLARE_FUNCTION(execGetContext_Struct);

	//const FStructBox GetContext() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus")
	void SetContext(UObject* Context);
	virtual void SetContext_Implementation(UObject* Context) { }

	template <typename T>
	void SetContext(T* Context) { SetContext(Cast<UObject>(Context)); }

	// CustomThunk
	// CustomStructureParam = "Context"
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UMGPlus", meta = (DisplayName = "Set Context (Struct)"))
	void SetContext_Struct(const FStructBox& Context);
	virtual void SetContext_Struct_Implementation(const FStructBox& Context) { }

	void SetContext(const FStructBox& Context) { SetContext_Struct(Context); }

	//DECLARE_FUNCTION(execSetContext_Struct);
};
