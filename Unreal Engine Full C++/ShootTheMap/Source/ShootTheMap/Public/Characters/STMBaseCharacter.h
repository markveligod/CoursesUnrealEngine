// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
class UHealthComponent;
class UTextRenderComponent;
class USTMWeaponComponent;

DECLARE_MULTICAST_DELEGATE(FOnDestroyWeapon);

UCLASS()
class SHOOTTHEMAP_API ASTMBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ASTMBaseCharacter(const FObjectInitializer &ObjInit);

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent *Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent *HealthTextComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTMWeaponComponent *WeaponComp;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *DeathAnimMontage;

    UPROPERTY(EditAnywhere, Category = "Damage Edit")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditAnywhere, Category = "Damage Edit")
    FVector2D LandeDamage = FVector2D(10.f, 100.f);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // Function Get booling run
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    FOnDestroyWeapon OnDestroyWeapon;

  private:
    UCharacterMovementComponent *MovementComponent;
    bool bRunAction = false;
    bool bIsMovingFrw = false;

    // Function
    void MoveForward(float amount);
    void MoveRight(float amount);

    // void LookUp(float amount);
    // void TurnAround(float amount);

    void StartRun();
    void StopRun();

    void OnDeath();
    void OnHealthChanged(float NewHealth);

    UFUNCTION()
    void OnGroundLanded(const FHitResult &Hit);

    
};
