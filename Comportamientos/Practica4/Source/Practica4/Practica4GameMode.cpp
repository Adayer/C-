// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica4GameMode.h"
#include "Practica4Character.h"
#include "UObject/ConstructorHelpers.h"

APractica4GameMode::APractica4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
