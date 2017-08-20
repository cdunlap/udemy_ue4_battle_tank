// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "BattleTank.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (!ensure(TurretToSet && BarrelToSet)) {
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::Initialize setting empty turret and barrel!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent initializing"));
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(const FVector & HitLocation)
{
	if (!ensure(Barrel))
		return;

	float time = GetWorld()->GetTimeSeconds();
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());
	// Figure out the output velocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity,
		StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, IgnoreActors))
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%f %s Aiming at %s"), time, *GetOwner()->GetName(), *AimDirection.ToString());

		// Orient the barrel mesh to the direction
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector & AimDirection)
{
	if (!ensure(Barrel && Turret)) return;

	FRotator AimRotator = AimDirection.Rotation();

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotatorBarrel = AimRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotatorBarrel.Pitch);

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator DeltaTurretRotator = AimRotator - TurretRotator;
	Turret->Rotate(DeltaRotatorBarrel.Yaw);
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("UTankAImingComponent::TickComponent"));
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if(FiringState != EFiringState::Reloading)
	{
		LastFireTime = GetWorld()->GetTimeSeconds();

		FVector ProjectileStart = Barrel->GetSocketLocation(FName("Projectile"));
		AProjectile * projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(LaunchSpeed);
	}
}