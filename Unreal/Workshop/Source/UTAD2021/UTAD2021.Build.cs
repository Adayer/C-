// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UTAD2021 : ModuleRules
{
	public UTAD2021(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
