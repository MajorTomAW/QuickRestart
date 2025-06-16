// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuickRestart : ModuleRules
{
	public QuickRestart(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateDependencyModuleNames.AddRange( new []
		{ 
			"Core",
			"CoreUObject",
			"Slate",
			"SlateCore",
			"Engine",
			"InputCore",
			"MainFrame",
			"ToolMenus",
			"UnrealEd",
		});
	}
}
