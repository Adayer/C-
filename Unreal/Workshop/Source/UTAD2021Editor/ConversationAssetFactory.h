// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ConversationAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class UTAD2021EDITOR_API UConversationAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UConversationAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
