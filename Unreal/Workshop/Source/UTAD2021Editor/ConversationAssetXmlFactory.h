// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ConversationAssetXmlFactory.generated.h"

/**
 * 
 */
UCLASS()
class UTAD2021EDITOR_API UConversationAssetXmlFactory : public UFactory
{
	GENERATED_BODY()

public:
	UConversationAssetXmlFactory();

	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
