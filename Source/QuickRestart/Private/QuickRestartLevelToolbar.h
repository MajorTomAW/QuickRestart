// Copyright © 2025 Playton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FUICommandList;
class SWidget;

class FQuickRestartLevelToolbar
{
public:
	static void RegisterToolbar(const TSharedPtr<FUICommandList>& CommandList);
	
private:
	static TSharedRef<SWidget> GetApplicationActions();
};

class FQuickRestartCommands
	: public TCommands<FQuickRestartCommands>
{
public:
	FQuickRestartCommands();

	//~ Begin TCommands Interface
	virtual void RegisterCommands() override;
	//~ End TCommands Interface

public:
	TSharedPtr<FUICommandInfo> RestartEditor;
	TSharedPtr<FUICommandInfo> ExitEditor;
};