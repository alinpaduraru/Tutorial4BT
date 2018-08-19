// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetAIControlledTank();
	auto PlayerTank = GetPlayerTank();
	//Getting the name of the controlled AI tank.
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAICOntroller.cpp: Name of the AI tank is: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAICOntroller.cpp: Not controlling any tank"))
	}

	//Getting player controller tank
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAICOntroller.cpp: Player controller Tank found and its name is %s."),*PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAICOntroller.cpp: No PlayerControllerTank"))
	}
	
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}


