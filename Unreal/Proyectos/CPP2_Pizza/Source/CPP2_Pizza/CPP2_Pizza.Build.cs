// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPP2_Pizza : ModuleRules
{
	public CPP2_Pizza(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
