// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"  //First include
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast <ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast <ATank>(GetPawn());

	if (PlayerTank) {
		// TODO Move towards the player

		// Aim towards Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); // TODO Limit firing rate
	}
}