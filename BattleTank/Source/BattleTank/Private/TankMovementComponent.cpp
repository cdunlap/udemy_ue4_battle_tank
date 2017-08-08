// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{

	if (!LeftTrackToSet || !RightTrackToSet) {
		UE_LOG(LogTemp, Error, TEXT("%f %s::Initialize; Left and right track not specified"), GetWorld()->GetTimeSeconds(), *GetName());
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// Don't call Super, we're overriding the behavior

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveDirection = MoveVelocity.GetSafeNormal();
	float ForwardAmount = FVector::DotProduct(TankForward, MoveDirection);
	IntendMoveForward(ForwardAmount);

	FVector RotationCross = FVector::CrossProduct(TankForward, MoveDirection);
	IntendTurnRight(RotationCross.Z);

	// UE_LOG(LogTemp, Warning, TEXT("%f: %s vectoring to %s"), GetWorld()->GetTimeSeconds(), *TankName, *MoveDirection.ToString());
}
