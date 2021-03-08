// ShootTheMap

#include "GameModes/STMGameModeBase.h"
#include "Characters/STMBaseCharacter.h"
#include "PlayerControllers/STMPlayerController.h"
#include "UI/STMGameHUD.h"

ASTMGameModeBase::ASTMGameModeBase()
{
    DefaultPawnClass = ASTMBaseCharacter::StaticClass();
    PlayerControllerClass = ASTMPlayerController::StaticClass();
    HUDClass = ASTMGameHUD::StaticClass();
}
