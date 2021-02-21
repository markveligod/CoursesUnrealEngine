// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthActorComponent.h"
#include "GameFramework/Controller.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthActorComponent::UHealthActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthActorComponent::BeginPlay()
{
	Super::BeginPlay();

	this->Health = this->DefaultHealth;
	this->GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthActorComponent::TakeDamage);

}

void UHealthActorComponent::TakeDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser) 
{
	if (Damage == 0.f || this->Health <= 0.f)
	{
		return ;
	}
	this->Health = FMath::Clamp(this->Health - Damage, 0.f, this->DefaultHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s to damage: %f => %s"), *DamageCauser->GetName(), Damage, *GetOwner()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Health %s : %f"), *GetOwner()->GetName(), this->Health);
	
	if (this->Health <= 0.f)
	{
		if (this->GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameModeRef don't ref !(*_*)!"));
		}
	}

}

