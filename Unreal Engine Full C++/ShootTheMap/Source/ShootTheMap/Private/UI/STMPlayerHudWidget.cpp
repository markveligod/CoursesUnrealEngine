// ShootTheMap

#include "UI/STMPlayerHudWidget.h"
#include "Components/HealthComponent.h"
#include "STMWeaponComponent.h"
#include "STMUtils.h"

float USTMPlayerHudWidget::GetHealthPrecent() const
{
    const auto HealthComp = STMUtils::GetComponent<UHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComp)
        return (0.f);
    return (HealthComp->GetHealthPercent());
}

bool USTMPlayerHudWidget::GetCurrentWeaponUIData(FWeaponUIData &UIData)
{
    const auto WeaponComp = STMUtils::GetComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComp)
        return (false);
    return (WeaponComp->GetWeaponUIData(UIData));
}

bool USTMPlayerHudWidget::GetCurrentAmmoData(FAmmoData &AmmoData)
{
    const auto WeaponComp = STMUtils::GetComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComp)
        return (false);
    return (WeaponComp->GetAmmoUIData(AmmoData));
}

bool USTMPlayerHudWidget::IsPlayerAlive() const
{
    const auto HealthComp = STMUtils::GetComponent<UHealthComponent>(GetOwningPlayerPawn());
    return (HealthComp && !HealthComp->IsDead());
}

bool USTMPlayerHudWidget::IsPlayerSpectating() const
{
    const auto Contoller = GetOwningPlayer();
    return (Contoller && Contoller->GetStateName() == NAME_Spectating);
}
