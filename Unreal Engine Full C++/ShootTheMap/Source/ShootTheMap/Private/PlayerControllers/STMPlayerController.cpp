// ShootTheMap

#include "PlayerControllers/STMPlayerController.h"
#include "PlayerControllers/STMRestartComponent.h"

ASTMPlayerController::ASTMPlayerController()
{
    this->STMRestartComponent = CreateDefaultSubobject<USTMRestartComponent>("Restart Component");
}
