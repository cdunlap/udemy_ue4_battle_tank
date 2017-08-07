// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

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
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}