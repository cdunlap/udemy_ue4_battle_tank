// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController begin play"));

	ATank * tank = GetControlledTank();
	if (tank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ControlledTank returned null. Check that the player is possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlled tank: %s"), *tank->GetName());
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}