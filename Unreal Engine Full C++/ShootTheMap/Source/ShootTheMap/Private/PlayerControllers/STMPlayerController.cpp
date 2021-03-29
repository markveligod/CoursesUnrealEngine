// ShootTheMap

#include "PlayerControllers/STMPlayerController.h"
#include "PlayerControllers/STMRestartComponent.h"
#include "GameModes/STMGameModeBase.h"

ASTMPlayerController::ASTMPlayerController()
{
    this->STMRestartComponent = CreateDefaultSubobject<USTMRestartComponent>("Restart Component");
}

void ASTMPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTMPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTMPlayerController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    this->OnNewPawn.Broadcast(InPawn);
}

void ASTMPlayerController::OnMatchStateChanged(ESTMMatchState State)
{
    if (State == ESTMMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeGameAndUI());
        bShowMouseCursor = true;
    }
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
