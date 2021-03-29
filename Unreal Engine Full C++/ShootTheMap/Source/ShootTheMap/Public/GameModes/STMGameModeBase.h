// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STMCoreType.h"
#include "STMGameModeBase.generated.h"

class AAIController;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

  public:
    ASTMGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual UClass *GetDefaultPawnClassForController_Implementation(AController *InController) override;

    void Killed(AController* Killer, AController *Victim);
    FGameData GetGameData() const;
    int32 GetCurrentRoundNum() const;
    int32 GetRoundSecondRemaining() const;
    void RespawnRequest(AController *Controller);
  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Stats")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Stats")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Stats")
    FGameData GameData;

    virtual bool SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
  private:
    ESTMMatchState MatchState = ESTMMatchState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameTimeHandler;

    void SpawnBots();
    void StartRound();
    void TimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController *Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController *Controller);
    void LogPlayerInfo();

    void StartRespawn(AController *Controller);

    void GameOver();
    void SetMatchState(ESTMMatchState NewMatchState);
};
