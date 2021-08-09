// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ino_OSS : ModuleRules
{
    public Ino_OSS(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "Ino_OSS/FirsPersonTemplate",
                "Ino_OSS/Settings",
            }
        );

        PublicIncludePaths.AddRange(
            new string[]
            {
                

            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "HeadMountedDisplay",

                "ApplicationCore",

                "OnlineSubsystem",
                "OnlineSubsystemUtils",

                "Http",
                "Json",
                "JsonUtilities",

                "Sockets",
                "Networking",

                

            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "OnlineSubsystemIno",
                "InoJson",
            }
        );
    }
}
