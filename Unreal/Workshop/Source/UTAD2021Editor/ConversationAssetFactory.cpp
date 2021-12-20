// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAssetFactory.h"
#include "UTAD2021/ConversationAsset.h"
#include "Misc/FeedbackContext.h"

UConversationAssetFactory::UConversationAssetFactory()
{
	SupportedClass = UConversationAsset::StaticClass();
	bCreateNew = true;
}

UObject* UConversationAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UConversationAsset* NewAsset = nullptr;
	if (Warn->YesNof(FText::FromString(TEXT("Are you sure?"))))
	{
		NewAsset = NewObject<UConversationAsset>(InParent, InClass, InName, Flags);
	}
	return NewAsset;
}
