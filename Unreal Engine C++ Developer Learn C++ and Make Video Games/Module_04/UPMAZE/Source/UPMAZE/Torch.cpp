// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"

// Sets default values
ATorch::ATorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BaseTorch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BASE"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindAssets(TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Torch.SM_Torch'"));

	this->BasePoint = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));

	this->BaseFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));

	if (this->BaseTorch && FindAssets.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Base torch done!"));
		this->BaseTorch->SetStaticMesh(FindAssets.Object);
		this->BaseTorch->SetupAttachment(RootComponent);
		this->BaseTorch->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	if (this->BasePoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("Light done!"));
		this->BasePoint->SetupAttachment(this->BaseTorch);
		this->BasePoint->SetRelativeLocation(FVector(0.0f, 209.0f, 54.0f));
		this->BasePoint->SetWorldScale3D(FVector(1.f));
		this->BasePoint->SetLightColor(FLinearColor(255.f, 0.f, 0.f));
	}

	if (this->BaseFire)
	{
		UE_LOG(LogTemp, Warning, TEXT("FIRE IS DONE!"));
		this->BaseFire->SetupAttachment(this->BaseTorch);
		this->BaseFire->SetRelativeLocation(FVector(0.0f, 57.0f, 55.0f));
	}

}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();
	if (this->ActorLever)
	{
		this->BaseFire->SetWorldScale3D(FVector(0.f));
		this->BasePoint->SetIntensity(this->TempLightInt);
		UE_LOG(LogTemp, Warning, TEXT("IS ActorLever"));
		this->CurrActorLever =  this->ActorLever->FindComponentByClass<ULever>();
		if (this->CurrActorLever)
			UE_LOG(LogTemp, Warning, TEXT("IS CurrActorLever"));
	}
	else
	{
		this->BasePoint->SetIntensity(this->MaxLightInt);
		this->BaseFire->SetWorldScale3D(FVector(1.f));
	}
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->CurrActorLever && this->CurrActorLever->IsRunDownLever() && this->bStopRunLight == false)
	{
		if (!this->bStartFire)
		{
			this->BaseFire->SetWorldScale3D(FVector(1.f));
			this->bStartFire = true;
		}
		this->RunLight(DeltaTime);
		if (this->TempLightInt >= this->MaxLightInt)
			this->bStopRunLight = true;
	}
}

void ATorch::RunLight(float delta)
{
	this->TempLightInt = FMath::Lerp(this->TempLightInt, this->MaxLightInt, this->PowerRunLight * delta);
	this->BasePoint->SetIntensity(this->TempLightInt);
}