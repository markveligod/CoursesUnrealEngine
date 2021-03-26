// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API UEnvQueryTest_PickUpCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
  public:
    UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjectInitializer);

  protected:
    virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;
};
