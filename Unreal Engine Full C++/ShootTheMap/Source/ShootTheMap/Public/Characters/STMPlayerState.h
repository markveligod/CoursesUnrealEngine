// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STMPlayerState.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMPlayerState : public APlayerState
{
    GENERATED_BODY()
  public:
    void SetTeamID(int32 ID);
    int32 GetTeamID() const;

    void SetColor(FLinearColor Color);
    FLinearColor GetColor() const;

    void AddKill();
    void AddDeath();

    int32 GetKillStats() const;
    int32 GetDeathStats() const;

    void LogInfo();
  private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
