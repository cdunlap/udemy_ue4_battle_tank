// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank * tank = Cast<ATank>(GetPawn());
	ATank * player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player)
	{
		// TODO: Move toward player

		// Aim towards player
		tank->AimAt(player->GetActorLocation());

		// Fire
		tank->Fire();
	}

}