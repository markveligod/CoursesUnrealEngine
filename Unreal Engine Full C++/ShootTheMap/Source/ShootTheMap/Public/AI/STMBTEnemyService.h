// ShootTheMap

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "STMBTEnemyService.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMBTEnemyService : public UBTService
{
    GENERATED_BODY()
  public:
    USTMBTEnemyService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;
};
