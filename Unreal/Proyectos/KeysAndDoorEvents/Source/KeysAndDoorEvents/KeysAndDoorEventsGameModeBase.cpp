// Copyright Epic Games, Inc. All Rights Reserved.


#include "KeysAndDoorEventsGameModeBase.h"

void AKeysAndDoorEventsGameModeBase::OnLevelComplete()
{
	LevelCompleteEvent.Broadcast();
}