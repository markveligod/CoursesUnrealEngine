// ShootTheMap


#include "Characters/Components/HealthComponent.h"
#include "GameFramework/Actor.h"
//#include "Characters/Dev/STMFireDamageType.h"
//#include "Characters/Dev/SMPIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UHealthComponent::GetHealth() const
{
    return (this->Health);
}

bool UHealthComponent::IsDead() const
{
    return(this->Health <= 0.0f);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    this->Health = this->MaxHealth;
    AActor *TempParentActor = GetOwner();
    if (TempParentActor)
    {
        TempParentActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
    }
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                              AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || this->IsDead()) return;
    this->Health = FMath::Clamp(this->Health - Damage, 0.0f, this->MaxHealth);
    OnDeathChange.Broadcast(Health);
    if (IsDead())
    {
        OnDeath.Broadcast();
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
}
