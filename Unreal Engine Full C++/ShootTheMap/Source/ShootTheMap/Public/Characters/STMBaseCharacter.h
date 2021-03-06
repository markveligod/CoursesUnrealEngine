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

UCLASS()
class SHOOTTHEMAP_API ASTMBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ASTMBaseCharacter(const FObjectInitializer& ObjInit);

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent *Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent *HealthTextComp;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *DeathAnimMontage;

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
};
