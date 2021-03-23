// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STMAIPerceptionComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMAIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()
    public:
    AActor *GetClosesEnemy() const;
};
