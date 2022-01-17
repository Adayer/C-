// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMBEditorUtility.h"

#define LOCTEXT_NAMESPACE "FUMBEditorUtilityModule"

void FUMBEditorUtilityModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUMBEditorUtilityModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUMBEditorUtilityModule, UMBEditorUtility)