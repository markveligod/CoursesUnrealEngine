// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "HealthComponent.generated.h"

class UCameraShakeBase;

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

    UFUNCTION(BlueprintCallable)
    float GetHealthPercent() const;

    FOnDeath OnDeath;
    FOnDeathChange OnDeathChange;

    bool TryToAddHealth(float HealthAmount);

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor",
              meta = (ClampMin = "1.0", ClampMax = "200.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor")
    bool bAutoHeal = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor",
              meta = (ClampMin = "0.01", ClampMax = "10.0", EditCondition = "bAutoHeal"))
    float HealUpdateTime = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor",
              meta = (ClampMin = "0.5", ClampMax = "10.0", EditCondition = "bAutoHeal"))
    float HealDelay = 3.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Editor",
              meta = (ClampMin = "0.5", ClampMax = "10.0", EditCondition = "bAutoHeal"))
    float HealModifier = 5.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    // Called when the game starts
    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);

    void PlayCameraShake();
    void Killed(AController *Controller);
};
