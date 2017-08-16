// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent * AimCompRef);
private:
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.333f;

	UPROPERTY(EditDefaultsOnly)
		int32 LineTraceRange = 1e6;
	
	void AimTowardCrosshair();

	// Return true if hit landscape, HitLocation populated with the trace endpoint
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	// Gets the direction the tank is looking, in world space. Returns false if trace into the world fails
	bool GetLookDirection(const FVector2D & ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(const FVector & LookDirection, FVector & OutHitLocation) const;
};
