// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickRestartModule.h"

#include "QuickRestartLevelToolbar.h"
#include "Interfaces/IMainFrameModule.h"

#define LOCTEXT_NAMESPACE "QuickRestart"

class FQuickRestartModule final : public IQuickRestartModule
{
public:
	//~ Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface

	virtual TSharedPtr<FUICommandList> GetCommandList() const override;

private:
	void RestartApplication() const;
	void ExitApplication() const;
	
	TSharedPtr<FUICommandList> CommandList;
};
IMPLEMENT_MODULE(FQuickRestartModule, QuickRestart)

void FQuickRestartModule::StartupModule()
{
	// Commands & Toolbar
	FQuickRestartCommands::Register();
	CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction
	(
		FQuickRestartCommands::Get().RestartEditor,
		FExecuteAction::CreateRaw(this, &FQuickRestartModule::RestartApplication),
		FCanExecuteAction()
	);
	CommandList->MapAction
	(
		FQuickRestartCommands::Get().ExitEditor,
		FExecuteAction::CreateRaw(this, &FQuickRestartModule::ExitApplication),
		FCanExecuteAction()
	);

	// Let the main frame module know about our commands
	IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	MainFrame.GetMainFrameCommandBindings()->Append(CommandList.ToSharedRef());

	FQuickRestartLevelToolbar::RegisterToolbar(CommandList);
}

void FQuickRestartModule::ShutdownModule()
{
}

void FQuickRestartModule::RestartApplication() const
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

void FQuickRestartModule::ExitApplication() const
{
	FSlateApplication::Get().LeaveDebuggingMode();
	GEngine->DeferredCommands.Add(TEXT("CLOSE_SLATE_MAINFRAME"));
}

TSharedPtr<FUICommandList> FQuickRestartModule::GetCommandList() const
{
	return CommandList;
}


#undef LOCTEXT_NAMESPACE
