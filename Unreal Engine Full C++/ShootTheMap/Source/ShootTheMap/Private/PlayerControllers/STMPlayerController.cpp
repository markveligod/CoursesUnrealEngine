// ShootTheMap

#include "PlayerControllers/STMPlayerController.h"
#include "PlayerControllers/STMRestartComponent.h"
#include "GameModes/STMGameModeBase.h"

ASTMPlayerController::ASTMPlayerController()
{
    this->STMRestartComponent = CreateDefaultSubobject<USTMRestartComponent>("Restart Component");
}

void ASTMPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("Pause", IE_Pressed, this, &ASTMPlayerController::OnPauseGame);
}

void ASTMPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}
