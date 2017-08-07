// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevating at %f"), DegreesPerSecond);
}

void UTankBarrel::Rotate(float DegreesPerSecond)
{
}
