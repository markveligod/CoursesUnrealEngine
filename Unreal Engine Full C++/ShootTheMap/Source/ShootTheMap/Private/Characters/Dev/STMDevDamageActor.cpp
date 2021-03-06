// ShootTheMap

#include "Characters/Dev/STMDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTMDevDamageActor::ASTMDevDamageActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Create Scene Component
    this->SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Component");
    SetRootComponent(this->SceneComp);
}

// Called when the game starts or when spawned
void ASTMDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASTMDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), this->Radius, 24, this->SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), this->Damage, GetActorLocation(), this->Radius, this->DamageType, {}, this,
                                        nullptr, this->DoFullDamage);
}
