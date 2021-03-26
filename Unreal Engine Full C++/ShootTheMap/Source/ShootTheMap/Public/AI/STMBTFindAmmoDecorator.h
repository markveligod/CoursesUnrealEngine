// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STMBTFindAmmoDecorator.generated.h"

class ASTMBaseWeapon;

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMBTFindAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	public:
    USTMBTFindAmmoDecorator();
	protected:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
      TSubclassOf<ASTMBaseWeapon> TypeWeapon;
      virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
