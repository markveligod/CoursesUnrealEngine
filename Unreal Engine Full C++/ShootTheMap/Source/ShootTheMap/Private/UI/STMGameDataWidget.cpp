// ShootTheMap


#include "UI/STMGameDataWidget.h"
#include "Characters/STMPlayerState.h"
#include "GameModes/STMGameModeBase.h"

int32 USTMGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = this->GetSTMPlayerState();
    return (PlayerState ? PlayerState->GetKillStats() : 0);
}

int32 USTMGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = this->GetSTMGameMode();
    return (GameMode ? GameMode->GetCurrentRoundNum() : 0);
}

int32 USTMGameDataWidget::GetTotalRoundNum() const
{
    const auto GameMode = this->GetSTMGameMode();
    return (GameMode ? GameMode->GetGameData().NumRounds : 0);
}

int32 USTMGameDataWidget::GetRoundSecondRemaining() const
{
    const auto GameMode = this->GetSTMGameMode();
    return (GameMode ? GameMode->GetRoundSecondRemaining() : 0);
}

ASTMGameModeBase * USTMGameDataWidget::GetSTMGameMode() const
{
    return (GetWorld() ? Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr);
}

ASTMPlayerState * USTMGameDataWidget::GetSTMPlayerState() const
{
    return (GetOwningPlayer() ? Cast<ASTMPlayerState>(GetOwningPlayer()->PlayerState) : nullptr);
}
