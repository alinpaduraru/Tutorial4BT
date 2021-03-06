// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


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
		
		GetControlledTank()->AimAt(HitLocation);
		//if it hits the landscape
			//TODO tell controlled tank to aim at this point
	}
	
}
//Get world location through crosshair of linetrace, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector LookDirection;
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction (That's a "De-projection")
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-Trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector WorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
		
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;//Line trace didn't succeed.
}






