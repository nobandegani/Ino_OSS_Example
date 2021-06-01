// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ino_OSS : ModuleRules
{
	public Ino_OSS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
