// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"  //First include
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {


		// TODO Move towards the player

		// Aim towards Player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast <ATank>(GetPawn());;
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast <ATank>(PlayerPawn);
}