// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandBoxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API ASandBoxPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	//Variable's
	UPROPERTY()
	TArray<AActor*> Pawns;

	int32 CurrentPawnIndex = 0;

	//function
	void ChangePawn();
};
