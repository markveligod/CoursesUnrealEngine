// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Lever.h"
#include "Particles/ParticleSystemComponent.h"
#include "Torch.generated.h"

UCLASS()
class UPMAZE_API ATorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UStaticMeshComponent")
	UStaticMeshComponent * BaseTorch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UPointLightComponent")
	UPointLightComponent * BasePoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UParticleSystemComponent")
	UParticleSystemComponent * BaseFire;

	UPROPERTY(EditAnywhere)
	AActor * ActorLever;

	ULever * CurrActorLever;

	
	bool bStopRunLight = false;
	bool bStartFire = false;
	float TempLightInt = 0.f;
	float MaxLightInt = 1000.f;

	UPROPERTY(EditAnywhere)
	float PowerRunLight = 2.f;

	void RunLight(float delta);

};
