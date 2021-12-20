// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTAD2021GameMode.h"
#include "UTAD2021Character.h"
#include "UObject/ConstructorHelpers.h"

AUTAD2021GameMode::AUTAD2021GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
