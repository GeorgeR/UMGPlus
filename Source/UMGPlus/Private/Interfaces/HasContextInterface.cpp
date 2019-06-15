#include "Interfaces/HasContextInterface.h"

#include "Kismet/KismetSystemLibrary.h"

//DEFINE_FUNCTION(IHasContextInterface::execGetContext_Struct)
//{
//	auto Self = P_THIS_OBJECT;
//	UStructProperty* SrcContextProperty = FindField<UStructProperty>(Self->GetClass(), TEXT("Context"));
//	
//	Stack.MostRecentPropertyAddress = nullptr;
//	Stack.MostRecentProperty = nullptr;
//
//	Stack.StepCompiledIn<UStructProperty>(nullptr);
//	void* DstContextAddr = Stack.MostRecentPropertyAddress;
//	auto DstContextProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
//
//	bool bResult = false;
//	UScriptStruct* SrcContext = SrcContextProperty->Struct;
//	uint8* SrcContextData = (uint8*)FMemory::Malloc(SrcContext->GetStructureSize());
//	SrcContext->InitializeStruct(SrcContextData);
//	if (DstContextAddr && DstContextProperty && SrcContext != nullptr)
//	{
//		if(SrcContext == DstContextProperty->Struct)
//		{
//			SrcContext->CopyScriptStruct(DstContextAddr, SrcContextData);
//			bResult = true;
//		}
//	}
//	
//	P_FINISH;
//
//	// #todo Native implementation
//	//P_NATIVE_BEGIN;
//	//bResult = P_THIS->GetContext_Struct_Implementation(Z_Param_Context);
//	//P_NATIVE_END;
//
//	*(bool*)RESULT_PARAM = bResult;
//}
//
//DEFINE_FUNCTION(IHasContextInterface::execSetContext_Struct)
//{
//	Stack.MostRecentPropertyAddress = nullptr;
//	Stack.MostRecentProperty = nullptr;
//
//	Stack.StepCompiledIn<UStructProperty>(nullptr);
//	void* SrcContextAddr = Stack.MostRecentPropertyAddress;
//	auto SrcContextProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
//
//	UScriptStruct* DstContext = nullptr;
//	uint8* DstContextData = nullptr;
//
//	// #todo Get existing Context (if it exists and is a struct) and destroy it
//	if (DstContext != nullptr)
//		DstContext->DestroyStruct(DstContextData);
//
//	if (SrcContextAddr && SrcContextProperty)
//	{
//		DstContext = SrcContextProperty->Struct;
//		DstContext->CopyScriptStruct(DstContextData, SrcContextAddr);
//	}
//
//	P_FINISH;
//
//	// #todo Native implementation
//	//P_NATIVE_BEGIN;
//	//P_THIS->SetContext_Struct_Implementation(Z_Param_Context);
//	//P_NATIVE_END;
//}
