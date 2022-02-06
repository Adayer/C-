// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practica4 : ModuleRules
{
	public Practica4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
