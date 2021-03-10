// ShootTheMap

#include "Weapons/STMProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTMProjectile::ASTMProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    //Create sphere component
    this->CollisionComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
    this->CollisionComponent->InitSphereRadius(5.f);
    this->CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    this->CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(this->CollisionComponent);

    this->MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
    this->MovementComponent->InitialSpeed = 2000.f;
    this->MovementComponent->ProjectileGravityScale = 0.f;
}

void ASTMProjectile::SetShotDirection(const FVector Direction)
{
    this->ShootDirection = Direction;
}

// Called when the game starts or when spawned
void ASTMProjectile::BeginPlay()
{
    Super::BeginPlay();
    check(this->MovementComponent);
    check(this->CollisionComponent);

    this->MovementComponent->Velocity = this->ShootDirection * MovementComponent->InitialSpeed;
    this->CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    this->CollisionComponent->OnComponentHit.AddDynamic(this, &ASTMProjectile::OnProjectileHit);
    SetLifeSpan(this->LifeSeconds);
}

void ASTMProjectile::OnProjectileHit(UPrimitiveComponent *HitComponent,
    AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!GetWorld())
        return;

    MovementComponent->StopMovementImmediately();

    //make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(),
        this->DamageAmount,
        GetActorLocation(),
        this->DamageRadius,
        UDamageType::StaticClass(),
        {GetOwner()},
        this,
        this->GetController(),
        this->DoFullDamage);
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.f);
    Destroy();
}

AController * ASTMProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return (Pawn ? Pawn->GetController() : nullptr);
}
