// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMAP_API ASTMBasePickUp : public AActor
{
    GENERATED_BODY()

  public:
    ASTMBasePickUp();
    virtual void Tick(float DeltaTime) override;
  protected:
    UPROPERTY(VisibleAnywhere, Category = "PickUp Editor Base")
    USphereComponent *CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
    float RespawnTime = 5.f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

  private:
    float RotationYaw = 0.f;
    float Direction;
    void PickUpWasTaken();
    void Respawn();
    virtual bool GivePickUpTo(APawn *Player);

    void GenerateRotationYaw();
};