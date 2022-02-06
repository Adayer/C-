// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica5GameMode.h"
#include "Practica5PlayerController.h"
#include "Practica5Character.h"
#include "UObject/ConstructorHelpers.h"

APractica5GameMode::APractica5GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APractica5PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}