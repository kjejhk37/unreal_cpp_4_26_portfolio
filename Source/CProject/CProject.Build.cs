// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CProject : ModuleRules
{
	public CProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //  "AIModule" 추가해야할듯
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GameplayTasks","UMG", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "CProject" });

        PublicIncludePaths.Add(ModuleDirectory);



        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
