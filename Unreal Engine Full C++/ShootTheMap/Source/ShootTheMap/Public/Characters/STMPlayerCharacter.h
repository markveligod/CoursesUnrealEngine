// ShootTheMap

#pragma once

#include "Characters/STMBaseCharacter.h"
#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

#include "STMPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMPlayerCharacter : public ASTMBaseCharacter
{
    GENERATED_BODY()
  public:
    ASTMPlayerCharacter(const FObjectInitializer &ObjInit);

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    virtual bool IsRunning() const override;

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent *CameraCollision;

    virtual void OnDeath() override;
    virtual void BeginPlay() override;

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

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
                                       UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult & SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
                                     UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

    void CheckCameraOverlap();
};


