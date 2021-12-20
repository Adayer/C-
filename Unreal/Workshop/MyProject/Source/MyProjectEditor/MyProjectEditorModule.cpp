// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectEditorModule.h"
#include "ConversationAssetAction.h"

IMPLEMENT_MODULE(FMyProjectEditorModule, MyProjectEditor)

void FMyProjectEditorModule::StartupModule()
{
	ConversationActions = MakeShareable(new FConversationAssetAction());
	FAssetToolsModule& AssetToolsMod = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsMod.Get();
	AssetTools.RegisterAssetTypeActions(ConversationActions.ToSharedRef());
}
void FMyProjectEditorModule::ShutdownModule()
{

}