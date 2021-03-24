// ShootTheMap

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "STMBTChangeWeaponService.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMBTChangeWeaponService : public UBTService
{
    GENERATED_BODY()
  public:
    USTMBTChangeWeaponService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
