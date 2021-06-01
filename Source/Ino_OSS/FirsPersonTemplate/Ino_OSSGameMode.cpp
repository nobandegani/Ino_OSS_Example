// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ino_OSSGameMode.h"
#include "Ino_OSSHUD.h"
#include "Ino_OSSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIno_OSSGameMode::AIno_OSSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AIno_OSSHUD::StaticClass();
}
