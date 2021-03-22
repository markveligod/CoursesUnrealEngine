// ShootTheMap

#include "AI/STMAICharacter.h"
#include "AI/STMAIController.h"

ASTMAICharacter::ASTMAICharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTMAIController::StaticClass();
}
