// ShootTheMap


#include "Menu/STMMenuGameModeBase.h"
#include "Menu/STMMenuPlayerController.h"
#include "Menu/STMMenuHUD.h"

ASTMMenuGameModeBase::ASTMMenuGameModeBase()
{
    PlayerControllerClass = ASTMMenuPlayerController::StaticClass();
    HUDClass = ASTMMenuHUD::StaticClass();
}
