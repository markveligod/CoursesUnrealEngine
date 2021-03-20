// ShootTheMap

#include "PickUps/STMBasePickUp.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp, All, All);

// Sets default values
ASTMBasePickUp::ASTMBasePickUp()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // Create sphere component
    this->CollisionComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
    this->CollisionComponent->InitSphereRadius(50.f);
    this->CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    this->CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(this->CollisionComponent);
}

// Called when the game starts or when spawned
void ASTMBasePickUp::BeginPlay()
{
    Super::BeginPlay();
    check(this->CollisionComponent);
    this->GenerateRotationYaw();
}

void ASTMBasePickUp::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (this->GivePickUpTo(Pawn))
    {
        this->PickUpWasTaken();
    }
    UE_LOG(LogBasePickUp, Display, TEXT("Overlap with %s"), *OtherActor->GetName());
}

// Called every frame
void ASTMBasePickUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.f, this->RotationYaw, 0.f));
}

void ASTMBasePickUp::PickUpWasTaken()
{
    this->CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
        GetRootComponent()->SetVisibility(false, true);
    FTimerHandle RespawnTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ASTMBasePickUp::Respawn, this->RespawnTime);
}

void ASTMBasePickUp::Respawn()
{
    this->GenerateRotationYaw();
    this->CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
        GetRootComponent()->SetVisibility(true, true);
}

bool ASTMBasePickUp::GivePickUpTo(APawn *Player)
{
    return (false);
}

void ASTMBasePickUp::GenerateRotationYaw()
{
    this->Direction = FMath::RandBool() ? 1.f : (-1.f);
    this->RotationYaw = FMath::RandRange(1.f, 2.f) * this->Direction;
}
