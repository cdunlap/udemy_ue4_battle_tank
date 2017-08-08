// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"



void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: %s throttle = %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);
}