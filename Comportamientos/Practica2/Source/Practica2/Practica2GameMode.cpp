// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica2GameMode.h"
#include "Practica2Character.h"
#include "UObject/ConstructorHelpers.h"

APractica2GameMode::APractica2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
