// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"

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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank * PosessedTank = Cast<ATank>(InPawn);

		if (!ensure(PosessedTank)) return;

		// TODO: Subscribe to tank death
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPosessedTankDeath);
	}
}

void ATankAIController::OnPosessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Posessed tank died"));
	GetPawn()->DetachFromControllerPendingDestroy();
}
