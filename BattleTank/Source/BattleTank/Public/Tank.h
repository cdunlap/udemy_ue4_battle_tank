// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent * AimingComponent = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	void AimAt(const FVector & HitLocation);

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel * Barrel = nullptr; // Local barrel reference for spawning projectile

	float LastFireTime = 0.0f;
};
