#pragma once

#ifndef __UMGPLUSEDITOR_H__
#define __UMGPLUSEDITOR_H__

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "ModuleManager.h"

class FUMGPlusEditorModule 
	: public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
#endif