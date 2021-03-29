// ShootTheMap


#include "Menu/STMMenuPlayerController.h"

void ASTMMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
