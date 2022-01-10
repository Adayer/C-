// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP2_PizzaGameMode.h"
#include "CPP2_PizzaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP2_PizzaGameMode::ACPP2_PizzaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
