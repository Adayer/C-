// Fill out your copyright notice in the Description page of Project Settings.


#include "UTAD2021EditorModule.h"

#include "Modules/ModuleManager.h"
#include "ConversationAssetAction.h"


IMPLEMENT_MODULE(FUTAD2021EditorModule, UTAD2021Editor)

void FUTAD2021EditorModule::StartupModule() 
{
	ConversationActions = MakeShareable(new FConversationAssetAction());
	FAssetToolsModule& AssetToolsMod = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsMod.Get();
	AssetTools.RegisterAssetTypeActions(ConversationActions.ToSharedRef());
}

void FUTAD2021EditorModule::ShutdownModule() 
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(ConversationActions.ToSharedRef());
	}
	ConversationActions.Reset();
}
