// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.333f;

	UPROPERTY(EditAnywhere)
		int32 LineTraceRange = 1e6;

	ATank * GetControlledTank() const;
	
	void AimTowardCrosshair();

	// Return true if hit landscape, HitLocation populated with the trace endpoint
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	// Gets the direction the tank is looking, in world space. Returns false if trace into the world fails
	bool GetLookDirection(const FVector2D & ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(const FVector & LookDirection, FVector & OutHitLocation) const;
};
