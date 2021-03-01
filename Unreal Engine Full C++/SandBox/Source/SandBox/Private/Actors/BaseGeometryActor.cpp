// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseGeometryActor.h"
#include "Math/UnrealMathUtility.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryBase, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create object mesh static component
	this->BaseMeshActor = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	SetRootComponent(BaseMeshActor);
}

FGeometryDate ABaseGeometryActor::GetGeometryDate()
{
	return (this->GeometryMoveDate);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogGeometryBase, Display, TEXT("BeginPlay!!!"));
	this->InitialLocation = GetActorTransform().GetLocation();
	this->SetColor(this->GeometryMoveDate.BaseColor);
	
	// Logs
	//this->printTypes();
	//this->printString();
	//this->printStatMesh();

	GetWorldTimerManager().SetTimer(this->TimerHandle, this, &ABaseGeometryActor::OnTimerFired, this->GeometryMoveDate.TimerRate, true);
	
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->HandleMovement();
}

void ABaseGeometryActor::SetGeometryDate(const FGeometryDate& Date)
{
	this->GeometryMoveDate = Date;
}

void ABaseGeometryActor::printTypes()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapons num: %d, kills num: %d"), this->WeaponsNum, this->KillNum);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), this->Health);
	UE_LOG(LogTemp, Warning, TEXT("isDead: %d, HasWeapon: %d"), static_cast<int>(this->bIsDead), static_cast<int>(this->bHasWeapon));
}

void ABaseGeometryActor::printString()
{
	FString name("Hello World");
	FString integer = "INT: " + FString::FromInt(this->WeaponsNum) + " " + FString::FromInt(this->KillNum);
	FString floating = "FLOAT: " + FString::SanitizeFloat(this->Health);
	FString isDead = "IS DEAD: " + FString(this->bIsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT("ALL stat: \n%s, \n%s, \n%s"), *integer, *floating, *isDead);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, name);
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, Stat, true, FVector2D(2.f, 2.f));

}

void ABaseGeometryActor::printStatMesh()
{
	this->RotatorActor = GetActorTransform().Rotator();
	this->LocActor = GetActorTransform().GetLocation();
	this->ScaleActor = GetActorTransform().GetScale3D();
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, FString("Location: " + this->LocActor.ToString()), true, FVector2D(2.f, 2.f));
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, FString("Rotator: " + this->RotatorActor.ToString()), true, FVector2D(2.f, 2.f));
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, FString("Scale: " + this->ScaleActor.ToString()), true, FVector2D(2.f, 2.f));

}

void ABaseGeometryActor::HandleMovement()
{
	switch (this->GeometryMoveDate.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		float time = GetWorld()->GetTimeSeconds();
		if (this->GeometryMoveDate.bXSin)
			CurrentLocation.X = this->InitialLocation.X + this->GeometryMoveDate.Amplitude * FMath::Sin(this->GeometryMoveDate.Frequence * time);
		if (this->GeometryMoveDate.bYSin)
			CurrentLocation.Y = this->InitialLocation.Y + this->GeometryMoveDate.Amplitude * FMath::Sin(this->GeometryMoveDate.Frequence * time);
		if (this->GeometryMoveDate.bZSin)
			CurrentLocation.Z = this->InitialLocation.Z + this->GeometryMoveDate.Amplitude * FMath::Sin(this->GeometryMoveDate.Frequence * time);
		SetActorLocation(CurrentLocation);
	}
	break;

	case EMovementType::Static:
		break;

	default:
		break;

	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial = this->BaseMeshActor->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++this->CurrCountTimer <= this->CountTimer)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogGeometryBase, Warning, TEXT("New color #%d: %s"), this->CurrCountTimer, *NewColor.ToString());
		this->SetColor(NewColor);
		this->OnColorChanched.Broadcast(NewColor, GetName());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(this->TimerHandle);
		this->OnTimerFinished.Broadcast(this);
	}
}


