// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "BattleTank.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Rotating turret %f"), RelativeSpeed);
	float NewYaw = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0, NewYaw, 0));
}