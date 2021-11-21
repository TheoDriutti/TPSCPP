// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSCPPGameMode.h"
#include "TPSCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPSCPPGameMode::ATPSCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATPSCPPGameMode::OnPlayerKilled(AController* controller)
{
	if (IsValid(controller))
	{
		controller->UnPossess();
		RestartPlayer(controller);
	}
}
