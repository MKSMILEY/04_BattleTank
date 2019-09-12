// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "BattleTank.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Rotate the barrel the right amount this frame
	// With a revolving rotation of 0-360 degrees

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	auto NewRotation = RawNewRotation;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
	//UE_LOG(LogTemp, Warning, TEXT("Rotation is happening."));
}


