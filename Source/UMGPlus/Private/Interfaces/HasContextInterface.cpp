//#include "Interfaces/HasContextInterface.h"
//
//#include "Kismet/KismetSystemLibrary.h"
//
//DEFINE_FUNCTION(IHasContextInterface::execGetContext_Struct)
//{
//    const auto Self = P_THIS_OBJECT;
//    const auto SrcContextProperty = FindField<UStructProperty>(Self->GetClass(), TEXT("Context"));
//	
//	Stack.MostRecentPropertyAddress = nullptr;
//	Stack.MostRecentProperty = nullptr;
//
//	Stack.StepCompiledIn<UStructProperty>(nullptr);
//	void* DstContextAddress = Stack.MostRecentPropertyAddress;
//    const auto DstContextProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
//
//    auto bResult = false;
//    const auto SrcContext = SrcContextProperty->Struct;
//    const auto SrcContextData = StaticCast<uint8*>(FMemory::Malloc(SrcContext->GetStructureSize()));
//	SrcContext->InitializeStruct(SrcContextData);
//	if (DstContextAddress && DstContextProperty && SrcContext != nullptr)
//	{
//		if(SrcContext == DstContextProperty->Struct)
//		{
//			SrcContext->CopyScriptStruct(DstContextAddress, SrcContextData);
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
//	*StaticCast<bool*>(RESULT_PARAM) = bResult;
//}
//
//DEFINE_FUNCTION(IHasContextInterface::execSetContext_Struct)
//{
//	Stack.MostRecentPropertyAddress = nullptr;
//	Stack.MostRecentProperty = nullptr;
//
//	Stack.StepCompiledIn<UStructProperty>(nullptr);
//	void* SrcContextAddress = Stack.MostRecentPropertyAddress;
//    const auto SrcContextProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
//
//	UScriptStruct* DstContext = nullptr;
//	uint8* DstContextData = nullptr;
//
//	// #todo Get existing Context (if it exists and is a struct) and destroy it
//	if (DstContext != nullptr)
//		DstContext->DestroyStruct(DstContextData);
//
//	if (SrcContextAddress && SrcContextProperty)
//	{
//		DstContext = SrcContextProperty->Struct;
//		DstContext->CopyScriptStruct(DstContextData, SrcContextAddress);
//	}
//
//	P_FINISH;
//
//	// #todo Native implementation
//	//P_NATIVE_BEGIN;
//	//P_THIS->SetContext_Struct_Implementation(Z_Param_Context);
//	//P_NATIVE_END;
//}
