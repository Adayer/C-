// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationFactory.h"
#include "MyProject/ConversationAsset.h"
#include "Misc/FeedbackContext.h"

UConversationFactory::UConversationFactory() 
{
	SupportedClass = UConversationAsset::StaticClass();
	bCreateNew = true;
}

UObject* UConversationFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, 
	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UConversationAsset* NewConversation = nullptr;
	if (Warn->YesNof(FText::FromString(TEXT("Are you sure about that?"))))
	{
		NewConversation = NewObject<UConversationAsset>(InParent, InClass, InName, Flags);
	}
	return NewConversation;
}
