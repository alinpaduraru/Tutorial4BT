// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "PaduNEW_TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API APaduNEW_TankPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 

	void GetPawn() const;
	
};
