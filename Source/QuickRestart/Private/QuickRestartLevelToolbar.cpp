// Copyright © 2025 Playton. All Rights Reserved.


#include "QuickRestartLevelToolbar.h"

#include "QuickRestartModule.h"

#define LOCTEXT_NAMESPACE "QuickRestartLevelToolbar"

void FQuickRestartLevelToolbar::RegisterToolbar(const TSharedPtr<FUICommandList>& CommandList)
{
	FToolMenuOwnerScoped OwnerScoped(UE_MODULE_NAME);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");

	FToolMenuSection& Section = Menu->FindOrAddSection("File", TAttribute<FText>());
	FToolMenuEntry Entry = FToolMenuEntry::InitComboButton
	(
		"ApplicationActions",
		FUIAction(),
		FOnGetContent::CreateStatic(&GetApplicationActions),
		TAttribute<FText>(),
		LOCTEXT("ApplicationActions_ToolTip", "Application Actions"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.Exit"),
		false,
		NAME_None
	);
	Entry.SetCommandList(CommandList);
	Entry.InsertPosition = FToolMenuInsert("SaveAllLevels", EToolMenuInsertType::First);
	
	Section.AddEntry(Entry);
}

TSharedRef<SWidget> FQuickRestartLevelToolbar::GetApplicationActions()
{
	TSharedPtr<const FUICommandList> CommandList = IQuickRestartModule::Get().GetCommandList();
	
	FMenuBuilder MenuBuilder(true, CommandList);
	
	MenuBuilder.AddMenuEntry(
		FQuickRestartCommands::Get().ExitEditor,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.Exit")
		);
	
	MenuBuilder.AddMenuEntry(
		FQuickRestartCommands::Get().RestartEditor,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "GenericCommands.Undo")
		);
	
	return MenuBuilder.MakeWidget(nullptr, 200.f);
}

FQuickRestartCommands::FQuickRestartCommands()
	: TCommands(TEXT("QuickRestart"),
		LOCTEXT("QuickRestartCommands", "Quick Restart Commands"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FQuickRestartCommands::RegisterCommands()
{
	UI_COMMAND
	(
		RestartEditor,
		"Restart",
		"Restarts the Application.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::R)
	);

	UI_COMMAND
	(
		ExitEditor,
		"Exit",
		"Exits the Application.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::E)
	);
}

#undef LOCTEXT_NAMESPACE