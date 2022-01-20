// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practica2 : ModuleRules
{
	public Practica2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
