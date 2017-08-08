// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"



void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	UE_LOG(LogTemp, Warning, TEXT("%f: %s force = %s"), GetWorld()->GetTimeSeconds(), *GetName(), *ForceApplied.ToString());

	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent * Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}