// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMAP_API ASTMBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ASTMBaseWeapon();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMesh;

    virtual void BeginPlay() override;

  private:
};
