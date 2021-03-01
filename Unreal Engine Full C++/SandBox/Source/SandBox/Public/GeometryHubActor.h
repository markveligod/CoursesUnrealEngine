// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Public/Actors/BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

class ABaseGeometryActor;

USTRUCT(BlueprintType)
struct FGeometryHubActorStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseGeometryActor> GeometryClass;
	UPROPERTY(EditAnywhere)
		FGeometryDate Date;
	UPROPERTY(EditAnywhere)
		FTransform GeometryTransform;
};

UCLASS()
class SANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TArray<FGeometryHubActorStruct> GeometryHubStructs;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnNewActors();

	UFUNCTION()
	void OnColorChanched(const FLinearColor& Color, const FString Name);
	void OnTimerFinished(AActor* Actor);
};
