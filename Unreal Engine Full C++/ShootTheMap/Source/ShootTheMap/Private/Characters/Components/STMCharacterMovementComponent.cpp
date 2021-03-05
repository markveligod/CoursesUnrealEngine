// ShootTheMap


#include "Characters/Components/STMCharacterMovementComponent.h"
#include "Characters/STMBaseCharacter.h"

float USTMCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTMBaseCharacter *Player = Cast<ASTMBaseCharacter>(GetPawnOwner());
    return (Player && Player->IsRunning() ? MaxSpeed * this->RunMode : MaxSpeed );
}
