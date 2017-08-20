// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"


void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track hit"));
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Calculate slippage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	/// Work out the acceleration this frame to correct
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
		
	/// Calc and apply sideways force
	auto Tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (!ensure(Tank)) return;
	auto CorrectionForce = (Tank->GetMass() * CorrectionAcceleration) / 2;
	Tank->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	
	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent * Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}