// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ConversationFactory.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECTEDITOR_API UConversationFactory : public UFactory
{
	GENERATED_BODY()

public:
	UConversationFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, 
			EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
