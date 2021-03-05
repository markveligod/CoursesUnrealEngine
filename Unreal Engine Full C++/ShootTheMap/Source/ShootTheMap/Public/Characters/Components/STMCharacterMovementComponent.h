// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STMCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunMode = 2.f;

    virtual float GetMaxSpeed() const override;


  private:
    
};
