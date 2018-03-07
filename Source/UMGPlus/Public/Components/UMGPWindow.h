#pragma once

#include "CoreMinimal.h"

#include "UMGPWindow.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UMGPLUS_API UUMGPWindow
	: public UVerticalBox
{
	GENERATED_BODY()

public:
	UUMGPWindow()
		: bRequiresServerToOpen(false),
		bCanMove(true),
		bCanResize(false),
		bCanClose(true),
		bCanMinimize(false),
		bIsModal(false) { }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Multiplayer")
	bool bRequiresServerToOpen;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanMove;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanResize;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanClose;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanMinimize;
	
	/* Forces the user to interact with this window and nothing else. */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsModal;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};