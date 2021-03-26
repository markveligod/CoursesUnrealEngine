// ShootTheMap

#include "PlayerControllers/STMRestartComponent.h"
#include "GameModes/STMGameModeBase.h"

// Sets default values for this component's properties
USTMRestartComponent::USTMRestartComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTMRestartComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;

    this->RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(this->RespawnTimerHandle, this, &USTMRestartComponent::RespawnTimerUpdate, 1.f, true);
}

int32 USTMRestartComponent::GetRespawnCountDown() const
{
    return (this->RespawnCountDown);
}

bool USTMRestartComponent::IsRespawnInProgress() const
{
    return (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(this->RespawnTimerHandle));
}

void USTMRestartComponent::RespawnTimerUpdate()
{
    if (--this->RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(this->RespawnTimerHandle);
        const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());

        if (!GameMode)
            return;
        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
