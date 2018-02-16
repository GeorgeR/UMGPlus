#include "UMGPStyle.h"
#include "UMGPlusFunctionLibrary.h"

FString UUMGPStyle::GetPropertyAsString(FName InKey)
{
	if (HasProperty(InKey))
		return Properties[InKey];
	
	return "";
}

float UUMGPStyle::GetPropertyAsFloat(FName InKey)
{
	if (HasProperty(InKey))
		return FCString::Atof(*Properties[InKey]);

	return -1.0f;
}

int32 UUMGPStyle::GetPropertyAsInteger(FName InKey)
{
	if (HasProperty(InKey))
		return FCString::Atoi(*Properties[InKey]);

	return - 1;
}

FVector UUMGPStyle::GetPropertyAsVector(FName InKey)
{
	if (HasProperty(InKey))
	{
		FVector Result;
		TArray<FString> Array;
		Properties[InKey].ParseIntoArray(Array, TEXT(","), 1);
		for (auto i = 0; i < Array.Num(); i++)
			Result[i] = FCString::Atof(*Array[i]);

		return Result;
	}

	return FVector::ZeroVector;
}

bool UUMGPStyle::HasProperty(FName InKey)
{
	return Properties.Contains(InKey);
}

void UUMGPStyle::ApplyTo(UWidget* InWidget)
{
	// Assumes InWidget is valid for this style
	for (auto& KVP : Properties)
	{
		
	}
}

void UUMGPStyle::PostInitProperties()
{
	Super::PostInitProperties();

	Update();
}

#if WITH_EDITOR
void UUMGPStyle::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	Update();
}
#endif

void UUMGPStyle::Update()
{
	ParseSelector();
}

bool UUMGPStyle::ParseSelector()
{
	FString SelectorString = Selector.ToString();
	if (SelectorString.Len() == 0 || SelectorString == TEXT("None"))
		return false;

	TArray<FString> Split;
	SelectorString.ParseIntoArray(Split, TEXT(" "), true);

	for (auto i = 0; i < Split.Num(); i++)
	{
		FString Str = Split[i];
		if (Str.StartsWith(TEXT(".")))
		{
			Str.RemoveFromStart(TEXT("."));
			Classes.Add(FName(*Str));
		}
		else if (Str.StartsWith(TEXT("#")))
		{
			Str.RemoveFromStart(TEXT("#"));
			Ids.Add(FName(*Str));
		}
		else
			Widgets.Add(UUMGPlusFunctionLibrary::GetWidgetFromString(Str));
	}

	return true;
}