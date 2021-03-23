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

    virtual void OnPossess(APawn *InPawn) override;

    virtual void Tick(float DeltaSeconds) override;
};
