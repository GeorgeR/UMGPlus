#pragma once

UCLASS(BlueprintType, Blueprintable)
class UMGPLUS_API UViewWidget
	: public UUserWidget
{
	GENERATED_BODY()
	
public:


private:
	UPROPERTY()
	UWidgetAnimation* PlayAnimation;
	
	UPROPERTY()
	UWidgetAnimation* IdleAnimation;
	
	UPROPERTY()
	UWidgetAnimation* CloseAnimation;
};