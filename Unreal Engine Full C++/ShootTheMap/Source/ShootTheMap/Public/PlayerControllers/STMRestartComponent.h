// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STMRestartComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMAP_API USTMRestartComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    USTMRestartComponent();

    void Respawn(int32 RespawnTime);
    int32 GetRespawnCountDown() const;
    bool IsRespawnInProgress() const;
  private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

    void RespawnTimerUpdate();
};
