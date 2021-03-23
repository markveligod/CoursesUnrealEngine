// ShootTheMap

#pragma once


#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "BTNextLocationTaskNode.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API UBTNextLocationTaskNode : public UBTTaskNode
{
    GENERATED_BODY()

  public:
    UBTNextLocationTaskNode();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool SelfCenter = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
    FBlackboardKeySelector CenterActorKey;
};
