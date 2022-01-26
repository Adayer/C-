// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica3GameMode.h"
#include "Practica3PlayerController.h"
#include "Practica3Character.h"
#include "UObject/ConstructorHelpers.h"

APractica3GameMode::APractica3GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APractica3PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}