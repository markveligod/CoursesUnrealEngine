// ShootTheMap

#include "GameModes/STMGameModeBase.h"
#include "Characters/STMBaseCharacter.h"
#include "PlayerControllers/STMPlayerController.h"
#include "UI/STMGameHUD.h"
#include "AIController.h"
#include "Characters/STMPlayerState.h"
#include "STMUtils.h"
#include "PlayerControllers/STMRestartComponent.h"
#include "EngineUtils.h"
#include "STMWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTMGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ASTMGameModeBase::ASTMGameModeBase()
{
    DefaultPawnClass = ASTMBaseCharacter::StaticClass();
    PlayerControllerClass = ASTMPlayerController::StaticClass();
    HUDClass = ASTMGameHUD::StaticClass();
    PlayerStateClass = ASTMPlayerState::StaticClass();
}

void ASTMGameModeBase::StartPlay()
{
    Super::StartPlay();
    this->SpawnBots();
    this->CreateTeamsInfo();
    this->CurrentRound = 1;
    this->StartRound();
    this->SetMatchState(ESTMMatchState::InProgress);
}

UClass * ASTMGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTMGameModeBase::Killed(AController *Killer, AController *Victim)
{
    const auto KillerPlayerState = Killer ? Cast<ASTMPlayerState>(Killer->PlayerState) : nullptr;
    const auto VictimPlayerState = Victim ? Cast<ASTMPlayerState>(Victim->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }
    StartRespawn(Victim);
}

FGameData ASTMGameModeBase::GetGameData() const
{
    return (this->GameData);
}

int32 ASTMGameModeBase::GetCurrentRoundNum() const
{
    return (this->CurrentRound);
}

int32 ASTMGameModeBase::GetRoundSecondRemaining() const
{
    return (this->RoundCountDown);
}

void ASTMGameModeBase::RespawnRequest(AController *Controller)
{
    ResetOnePlayer(Controller);
}

bool ASTMGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
    const auto TempResPause = Super::SetPause(PC, CanUnpauseDelegate);

    if (TempResPause)
        this->SetMatchState(ESTMMatchState::Pause);

    return (TempResPause);
}

void ASTMGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < this->GameData.PlayerSpawn - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto TempAIController = GetWorld()->SpawnActor<AAIController>(this->AIControllerClass, SpawnInfo);
        RestartPlayer(TempAIController);
    }
}

void ASTMGameModeBase::StartRound()
{
    this->RoundCountDown = GameData.RoundTime;
    GetWorld()->GetTimerManager().SetTimer(this->GameTimeHandler, this, &ASTMGameModeBase::TimerUpdate, 1.f, true);
}

void ASTMGameModeBase::TimerUpdate()
{
    UE_LOG(LogSTMGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), this->RoundCountDown, this->CurrentRound, this->GameData.NumRounds);

    if (--this->RoundCountDown == 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(this->GameTimeHandler);
        if (this->CurrentRound + 1 <= this->GameData.NumRounds)
        {
            this->CurrentRound++;
            this->ResetPlayers();
            this->StartRound();
        }
        else
        {
            this->GameOver();
            
        }
    }
}

void ASTMGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTMGameModeBase::ResetOnePlayer(AController *Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    this->SetPlayerColor(Controller);
}

void ASTMGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;
    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetColor(this->DetermineByTeamID(TeamID));
        this->SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;

    }
}

FLinearColor ASTMGameModeBase::DetermineByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return (GameData.TeamColors[TeamID - 1]);
    }
    UE_LOG(LogSTMGameModeBase, Warning, TEXT("No color for team id %i, set to default: %s"), TeamID,
           *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}

void ASTMGameModeBase::SetPlayerColor(AController *Controller)
{
    if (!Controller)
        return;
    const auto Character = Cast<ASTMBaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetColor());
}

void ASTMGameModeBase::LogPlayerInfo()
{
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;
        const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
}

void ASTMGameModeBase::StartRespawn(AController *Controller)
{
    const auto RespawnAvailable = this->RoundCountDown > MinRoundTimeForRespawn + this->GameData.RespawnTime;
    if (!RespawnAvailable)
        return;
    const auto RespawnComponent = STMUtils::GetComponent<USTMRestartComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTMGameModeBase::GameOver()
{
    UE_LOG(LogSTMGameModeBase, Display, TEXT("===========GAME OVER==========="));
    this->LogPlayerInfo();

    for (auto Pawn: TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
            const auto WeaponComp = STMUtils::GetComponent<USTMWeaponComponent>(Pawn);
            if (WeaponComp)
            {
                WeaponComp->StopFire();
            }
        }
    }
    this->SetMatchState(ESTMMatchState::GameOver);
}

void ASTMGameModeBase::SetMatchState(ESTMMatchState NewMatchState)
{
    if (this->MatchState == NewMatchState) return;

    this->MatchState = NewMatchState;
    this->OnMatchStateChanged.Broadcast(this->MatchState);
}
