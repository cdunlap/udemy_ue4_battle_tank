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
		AimDirection = LaunchVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%f %s Aiming at %s"), time, *GetOwner()->GetName(), *AimDirection.ToString());

		// Orient the barrel mesh to the direction
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel && Turret)) return;

	FRotator AimRotator = AimDirection.Rotation();

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotatorBarrel = AimRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotatorBarrel.Pitch);

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator DeltaTurretRotator = AimRotator - TurretRotator;

	/// Always yaw the shortest way
	if (DeltaTurretRotator.Yaw < 180.0f)
	{
		Turret->Rotate(DeltaRotatorBarrel.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotatorBarrel.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) return false;
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
	CurrentAmmo = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAmmo <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if(FiringState != EFiringState::Reloading && FiringState != EFiringState::NoAmmo)
	{
		LastFireTime = GetWorld()->GetTimeSeconds();

		FVector ProjectileStart = Barrel->GetSocketLocation(FName("Projectile"));
		AProjectile * projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(LaunchSpeed);

		CurrentAmmo--;
	}
}