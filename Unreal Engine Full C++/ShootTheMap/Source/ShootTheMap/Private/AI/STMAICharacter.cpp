// ShootTheMap

#include "AI/STMAICharacter.h"
#include "AI/STMAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/STMAIWeaponComponent.h"
#include "BrainComponent.h"

ASTMAICharacter::ASTMAICharacter(const FObjectInitializer &ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTMAIWeaponComponent>("Weapon Component"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTMAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
    }
}

void ASTMAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto STMController = Cast<AAIController>(Controller);
    if (STMController && STMController->BrainComponent)
    {
        STMController->BrainComponent->Cleanup();
    }
}
