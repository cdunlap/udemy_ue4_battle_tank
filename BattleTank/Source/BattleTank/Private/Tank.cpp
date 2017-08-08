// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::Fire()
{
	if (!ensure(Barrel)) return;

	bool isReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeInSeconds;

	if (isReloaded)
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

void ATank::AimAt(const FVector & HitLocation)
{
	if (!ensure(AimingComponent)) return;

	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

