// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn * tank = GetPawn();
	APawn * player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(player && tank)) return;

	// Move toward player
	MoveToActor(player, AcceptanceRadius);
	
	// Aim towards player
	UTankAimingComponent * aimingComponent = tank->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(player->GetActorLocation());

	// Fire
	if (aimingComponent->GetFiringState() == EFiringState::Locked)
	{
		aimingComponent->Fire();
	}
}