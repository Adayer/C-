// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProjectEditor : ModuleRules
{
	public MyProjectEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MyProject" });

		PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "XmlParser", "EditorStyle", "Slate", "SlateCore",
			"GraphEditor", "AppFramework", "PropertyEditor"});
	}
}
