// ShootTheMap


#include "UI/STMGameOverWidget.h"
#include "GameModes/STMGameModeBase.h"
#include "Characters/STMPlayerState.h"
#include "UI/STMPlayerStatGameWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTMGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTMGameOverWidget::OnMatchStateChanged);
        }
    }
    if (this->ResetLevelButton)
    {
        this->ResetLevelButton->OnClicked.AddDynamic(this, &USTMGameOverWidget::OnResetLevel);
    }
}

void USTMGameOverWidget::OnMatchStateChanged(ESTMMatchState State)
{
    if (State == ESTMMatchState::GameOver)
    {
        this->UpdatePlayerState();
    }
}

void USTMGameOverWidget::UpdatePlayerState()
{
    if (!GetWorld() || !this->PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();

    for (auto it = GetWorld()->GetControllerIterator(); it; ++it)
    {
        const auto Controller = it->Get();
        if (!Controller)
            continue;
        const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        const auto GameStatWidget = CreateWidget<USTMPlayerStatGameWidget>(GetWorld(), this->PLayerStatWidgetClass);
        if (!GameStatWidget)
            continue;

        GameStatWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        GameStatWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKillStats())));
        GameStatWidget->SetDeaths(FText::FromString(FString::FromInt(PlayerState->GetDeathStats())));
        GameStatWidget->SetTeamID(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
        GameStatWidget->SetPlayerIndicatorVisibillity(Controller->IsPlayerController());

        this->PlayerStatBox->AddChild(GameStatWidget);
    }
}

void USTMGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
