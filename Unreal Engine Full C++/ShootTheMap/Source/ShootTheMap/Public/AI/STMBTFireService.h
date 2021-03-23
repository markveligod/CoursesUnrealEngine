// ShootTheMap

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "STMBTFireService.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMBTFireService : public UBTService
{
    GENERATED_BODY()
  public:
    USTMBTFireService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
