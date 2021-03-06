// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMAP_API ASTMDevDamageActor : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ASTMDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent *SceneComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "100.0", ClampMax = "1000.0"))
    float Radius = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float Damage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = false;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
