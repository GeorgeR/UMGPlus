#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUMGPlusModule
    : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
