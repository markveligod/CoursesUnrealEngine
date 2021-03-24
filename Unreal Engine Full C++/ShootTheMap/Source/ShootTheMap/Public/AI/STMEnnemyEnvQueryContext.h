// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STMEnnemyEnvQueryContext.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMEnnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()
  protected:
    virtual void ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
