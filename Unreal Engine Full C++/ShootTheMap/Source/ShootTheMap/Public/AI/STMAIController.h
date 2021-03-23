// ShootTheMap

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "STMAIController.generated.h"

class USTMAIPerceptionComponent;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMAIController : public AAIController
{
    GENERATED_BODY()

  public:
    ASTMAIController();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception")
    USTMAIPerceptionComponent *STMAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn *InPawn) override;

    virtual void Tick(float DeltaSeconds) override;

    private:
    AActor *GetFocusActor() const;
};
