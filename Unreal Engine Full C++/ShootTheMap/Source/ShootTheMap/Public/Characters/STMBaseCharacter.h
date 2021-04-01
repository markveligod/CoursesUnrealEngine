// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"


class UCharacterMovementComponent;
class UHealthComponent;
class USTMWeaponComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMAP_API ASTMBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ASTMBaseCharacter(const FObjectInitializer &ObjInit);

  protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent *Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTMWeaponComponent *WeaponComp;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *DeathAnimMontage;

    UPROPERTY(EditAnywhere, Category = "Damage Edit")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditAnywhere, Category = "Damage Edit")
    FVector2D LandeDamage = FVector2D(10.f, 100.f);

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound Editor")
    USoundCue *DeathSound;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnDeath();

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    // Function Get booling run
    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor &Color);
  private:


    void OnHealthChanged(float NewHealth, float HealthDelta);

    UFUNCTION()
    void OnGroundLanded(const FHitResult &Hit);

    
};
