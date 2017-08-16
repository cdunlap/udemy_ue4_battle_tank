// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	void AimAt(const FVector & HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState AimState = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(const FVector & AimDirection);

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime = 0.0f;
};
