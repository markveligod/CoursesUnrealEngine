// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/SandBoxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandBox/Public/Pawns/SandBoxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandBoxPlayerController, All, All)

void ASandBoxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandBoxPlayerController::ChangePawn);
	}
}

void ASandBoxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandBoxPawn::StaticClass(), this->Pawns);
}

void ASandBoxPlayerController::ChangePawn()
{
	if (this->Pawns.Num() < 1) return;

	ASandBoxPawn* CurrentPawn = Cast<ASandBoxPawn>(this->Pawns[CurrentPawnIndex]);
	this->CurrentPawnIndex = (this->CurrentPawnIndex + 1) % this->Pawns.Num();

	if (!CurrentPawn) return;
	
	Possess(CurrentPawn);
	UE_LOG(LogSandBoxPlayerController, Warning, TEXT("Change Pawn"))
}
