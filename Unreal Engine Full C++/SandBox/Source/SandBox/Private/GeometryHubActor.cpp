// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHubActor, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	//this->SpawnNewActors();
	this->SpawnNewActorsNone();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogGeometryHubActor, Warning, TEXT("Property ptr: %i, is valid: %i"), this->PropertyActor != nullptr, IsValid(this->PropertyActor));
	UE_LOG(LogGeometryHubActor, Error, TEXT("None Property ptr: %i, is valid: %i"), this->NonePropetryActor != nullptr, IsValid(this->NonePropetryActor));

}

void AGeometryHubActor::SpawnNewActors()
{
	UWorld* World = GetWorld();
	if (World)
	{
		//for(int32 i = 0; i < 10; ++i)
		//{
		//	const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 300.f));
		//	ABaseGeometryActor * TempBaseGeometry = World->SpawnActor<ABaseGeometryActor>(this->GeometryClass, GeometryTransform);

		//	if (TempBaseGeometry)
		//	{
		//		FGeometryDate Date;
		//		Date.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
		//		TempBaseGeometry->SetGeometryDate(Date);
		//	}
		//}

		//for (int32 i = 0; i < 10; ++i)
		//{
		//	const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 700.f));
		//	ABaseGeometryActor* TempBaseGeometry = World->SpawnActorDeferred<ABaseGeometryActor>(this->GeometryClass, GeometryTransform);

		//	if (TempBaseGeometry)
		//	{
		//		FGeometryDate Date;
		//		Date.BaseColor = FLinearColor::MakeRandomColor();
		//		TempBaseGeometry->SetGeometryDate(Date);
		//		TempBaseGeometry->FinishSpawning(GeometryTransform);
		//	}
		//}
		for (const FGeometryHubActorStruct obj : this->GeometryHubStructs)
		{
			ABaseGeometryActor* TempBaseGeometry = World->SpawnActorDeferred<ABaseGeometryActor>(obj.GeometryClass, obj.GeometryTransform);
			if (TempBaseGeometry)
			{
				TempBaseGeometry->SetGeometryDate(obj.Date);
				TempBaseGeometry->OnColorChanched.AddDynamic(this, &AGeometryHubActor::OnColorChanched);
				TempBaseGeometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				TempBaseGeometry->FinishSpawning(obj.GeometryTransform);
			}
		}
	}
	
}

void AGeometryHubActor::SpawnNewActorsNone()
{
	UWorld* World = GetWorld();
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.f, 300.f, 300.f));
	this->NonePropetryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.f, 300.f, 600.f));
	this->PropertyActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}

void AGeometryHubActor::OnColorChanched(const FLinearColor& Color, const FString Name)
{
	UE_LOG(LogGeometryHubActor, Warning, TEXT("Actor Name: %s => Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (Actor)
		UE_LOG(LogGeometryHubActor, Error, TEXT("Actor Name: %s => Timer is Finish"), *Actor->GetName());
	ABaseGeometryActor* BaseTempGeometry = Cast<ABaseGeometryActor>(Actor);
	if (BaseTempGeometry)
	{
		UE_LOG(LogGeometryHubActor, Error, TEXT("BaseTempGeometry Name: %s => Destroy"), *BaseTempGeometry->GetName());
		BaseTempGeometry->Destroy();
	}
}

