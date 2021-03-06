// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h" //First include
#include "Engine/World.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *controlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast <ATank>(GetPawn());;
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter

	if (GetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		
		// TODO Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

//  Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D((ViewportSizeX * CrosshairXLocation), (ViewportSizeY * CrosshairYLocation));

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along the LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		// Line Trace didn't succeed
		HitLocation = FVector(0);
		return false;
	}
}
