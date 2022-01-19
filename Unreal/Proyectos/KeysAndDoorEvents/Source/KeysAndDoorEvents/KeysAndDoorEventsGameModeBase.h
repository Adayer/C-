// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateCombinations.h"
#include "KeysAndDoorEventsGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventsCompletedSignature);

UCLASS()
class KEYSANDDOOREVENTS_API AKeysAndDoorEventsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FLevelEventsCompletedSignature LevelCompleteEvent;
public:
	UFUNCTION(BlueprintCallable)
		void OnLevelComplete();
};
