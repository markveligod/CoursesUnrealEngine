// ShootTheMap

#include "Characters/Components/HealthComponent.h"
#include "GameFramework/Actor.h"
//#include "Characters/Dev/STMFireDamageType.h"
//#include "Characters/Dev/SMPIceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShake.h"
#include "GameModes/STMGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

float UHealthComponent::GetHealth() const
{
    return (this->Health);
}

bool UHealthComponent::IsDead() const
{
    return (FMath::IsNearlyZero(this->Health));
}

float UHealthComponent::GetHealthPercent() const
{
    return (this->Health / this->MaxHealth);
}

bool UHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (HealthAmount <= 0.f || FMath::IsNearlyEqual(this->Health, this->MaxHealth))
        return false;
    this->SetHealth(this->Health + HealthAmount);
    return (true);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(this->MaxHealth > 0);

    // ...
    this->SetHealth(this->MaxHealth);
    // this->Health = this->MaxHealth;
    AActor *TempParentActor = GetOwner();
    if (TempParentActor)
    {
        TempParentActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
    }
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                             AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || this->IsDead() || !GetWorld())
        return;

    this->SetHealth(this->Health - Damage);
    // this->Health = FMath::Clamp(this->Health - Damage, 0.0f, this->MaxHealth);

    GetWorld()->GetTimerManager().ClearTimer(this->HealTimerHandle);

    if (IsDead())
    {
        this->Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (this->bAutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(this->HealTimerHandle, this, &UHealthComponent::HealUpdate,
                                               this->HealUpdateTime, true, this->HealDelay);
    }
    /*if (DamageType)
    {
        if (DamageType->IsA<USTMFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Warning, TEXT("So HOT!!!"));
        }
        if (DamageType->IsA<USMPIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Warning, TEXT("So COLD!!!"));
        }
    }*/
    this->PlayCameraShake();
}

void UHealthComponent::HealUpdate()
{
    /*this->Health = FMath::Clamp(this->Health + this->HealModifier, 0.0f, this->MaxHealth);*/
    // this->Health = FMath::Min(this->Health + this->HealModifier, this->MaxHealth);
    this->SetHealth(this->Health + this->HealModifier);

    if (FMath::IsNearlyEqual(this->Health, this->MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(this->HealTimerHandle);
    }
}

void UHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.f, this->MaxHealth);
    const auto HealthDelta = NextHealth - this->Health;

    this->Health = NextHealth;
    OnDeathChange.Broadcast(this->Health, HealthDelta);
}

void UHealthComponent::PlayCameraShake()
{
    if (this->IsDead())
        return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    Controller->PlayerCameraManager->StartCameraShake(this->CameraShake);

}

void UHealthComponent::Killed(AController *Controller)
{
    const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(Controller, VictimController);
}
