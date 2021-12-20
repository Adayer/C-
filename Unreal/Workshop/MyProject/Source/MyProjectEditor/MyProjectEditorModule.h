// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FConversationAssetAction;

class FMyProjectEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	TSharedPtr<FConversationAssetAction> ConversationActions;
};