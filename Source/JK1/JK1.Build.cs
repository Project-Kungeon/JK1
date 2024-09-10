// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JK1 : ModuleRules
{
	public JK1(ReadOnlyTargetRules Target) : base(Target)
	{
        bEnableExceptions = true;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "NavigationSystem", "AIModule", "GameplayTasks" });


		PrivateDependencyModuleNames.AddRange(new string[] { "ThirdParty" });

		PrivateIncludePaths.AddRange(new string[]
        {
            "JK1/",
            "JK1/Network/",
            "JK1/Network/PacketHandler",
            "JK1/System/"
        });

		PrivateIncludePaths.AddRange(new string[]
		{
			"JK1/",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
