// ShootTheMap

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "STMHealthPercentBTDecorator.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMHealthPercentBTDecorator : public UBTDecorator
{
    GENERATED_BODY()
  public:
    USTMHealthPercentBTDecorator();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPrecent = 0.6f;
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
