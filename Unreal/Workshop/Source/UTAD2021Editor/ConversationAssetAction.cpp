// Fill out your copyright notice in the Description page of Project Settings.

#include "ConversationAssetAction.h"

void FConversationAssetAction::GetActions(
	const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Invertir Conversacion")),
		FText::FromString(TEXT("Invierte el orden de la conversacion")),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.ViewOptions"),
		FUIAction());
}