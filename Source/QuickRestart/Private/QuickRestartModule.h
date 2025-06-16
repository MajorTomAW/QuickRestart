// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class IQuickRestartModule : public IModuleInterface
{
public:
	static IQuickRestartModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IQuickRestartModule>("QuickRestart");
	}
	
	virtual TSharedPtr<FUICommandList> GetCommandList() const = 0;
};