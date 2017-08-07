// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AIController begin play"));

	ATank * tank = GetControlledTank();
	if (tank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ControlledTank returned null. Check that the player is possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI posesing tank: %s"), *tank->GetName());
	}

	ATank * player = GetPlayerTank();
	if (player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *player->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank * player = GetPlayerTank();
	if (player)
	{
		// TODO: Move toward player

		// Aim towards player
		GetControlledTank()->AimAt(player->GetActorLocation());

		// Fire if ready
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController * pc = GetWorld()->GetFirstPlayerController();
	return Cast<ATank>(pc->GetPawn());
}
