// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


// tick
	//super
	//AimTowardsCrosshair();

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name of the tank is: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not controlling any tank"))
	}

}

ATankPlayerController::ATankPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation)) //has "Side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location is: %s"), *HitLocation.ToString());
		
		//if it hits the landscape
			//TODO tell controlled tank to aim at this point
	}
	
}
//Get world location through crosshair of linetrace, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}


