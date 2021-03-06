// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathChange, float)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMAP_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UHealthComponent();

    float GetHealth() const;

    UFUNCTION(BlueprintCallable)
    bool IsDead() const;

    FOnDeath OnDeath;
    FOnDeathChange OnDeathChange;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor",
              meta = (ClampMin = "1.0", ClampMax = "200.0"))
    float MaxHealth = 100.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);
};
