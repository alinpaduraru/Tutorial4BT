// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/PaduNEW_TankPlayerController.h"



ATank* APaduNEW_TankPlayerController::GetPawn() const
{
	return Cast<ATank>(GetPawn());
}
