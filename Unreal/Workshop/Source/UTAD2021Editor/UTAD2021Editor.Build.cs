// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UTAD2021Editor : ModuleRules
{
	public UTAD2021Editor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
		"HeadMountedDisplay" });
	
		PublicDependencyModuleNames.Add("UTAD2021");
	
		PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "XmlParser", "EditorStyle", 
		"Slate", "SlateCore", "GraphEditor", "AppFramework", "PropertyEditor" });
	}
}
