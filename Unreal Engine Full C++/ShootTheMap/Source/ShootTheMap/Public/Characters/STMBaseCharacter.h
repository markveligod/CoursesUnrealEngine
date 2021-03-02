// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class UCameraComponent;

UCLASS()
class SHOOTTHEMAP_API ASTMBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ASTMBaseCharacter();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
