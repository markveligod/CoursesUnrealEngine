// ShootTheMap


#include "UI/STMSpectatorWidget.h"
#include "STMUtils.h"
#include "PlayerControllers/STMRestartComponent.h"

bool USTMSpectatorWidget::GetRespawnTime(int32 &CountTimeData) const
{
    const auto RespawnComponent = STMUtils::GetComponent<USTMRestartComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;
    CountTimeData = RespawnComponent->GetRespawnCountDown();
    return (true);
}
