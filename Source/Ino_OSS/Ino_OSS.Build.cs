// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ino_OSS : ModuleRules
{
	public Ino_OSS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                "Ino_Oss/Settings",
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "OnlineSubsystem",
                "OnlineSubsystemUtils",

                "HeadMountedDisplay",
            }
        );
        
	}
}
