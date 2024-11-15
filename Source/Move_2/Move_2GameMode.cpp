// Copyright Epic Games, Inc. All Rights Reserved.

#include "Move_2GameMode.h"
#include "Move_2Character.h"
#include "UObject/ConstructorHelpers.h"

AMove_2GameMode::AMove_2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
