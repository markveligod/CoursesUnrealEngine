// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanched, const FLinearColor&, Color, const FString, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryDate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Amplitude = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Frequence = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		EMovementType MoveType = EMovementType::Static;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bXSin = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bYSin = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bZSin = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
		FLinearColor BaseColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
		float TimerRate = 3.f;
};

UCLASS()
class SANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMeshActor;

	UFUNCTION(BlueprintCallable)
		FGeometryDate GetGeometryDate();

	UPROPERTY(BlueprintAssignable)
		FOnColorChanched OnColorChanched;
	
	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapons")
		int32 WeaponsNum = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
		int32 KillNum = 7;
	UPROPERTY(EditInstanceOnly, Category = "Health")
		float Health = 34.34f;
	UPROPERTY(EditAnywhere, Category = "Health")
		bool bIsDead = false;
	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		bool bHasWeapon = true;

	UPROPERTY(EditAnywhere, Category = "Geometry Date")
		FGeometryDate GeometryMoveDate;

	



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGeometryDate(const FGeometryDate & Date);

private:
	//VARIBLE's
	FVector InitialLocation;
	FRotator RotatorActor;
	FVector LocActor;
	FVector ScaleActor;

	FTimerHandle TimerHandle;
	const int32 CountTimer = 7;
	int32 CurrCountTimer = 0;

	//FUNCTION's
	void printTypes();
	void printString();
	void printStatMesh();
	void HandleMovement();

	void SetColor(const FLinearColor & Color);

	void OnTimerFired();


	
};
