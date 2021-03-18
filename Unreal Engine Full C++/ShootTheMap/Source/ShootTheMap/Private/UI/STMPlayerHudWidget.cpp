// ShootTheMap

#include "UI/STMPlayerHudWidget.h"
#include "Components/HealthComponent.h"
#include "STMWeaponComponent.h"

float USTMPlayerHudWidget::GetHealthPrecent() const
{
    const auto HealthComp = this->GetComponent<UHealthComponent>();
    if (!HealthComp)
        return (0.f);
    return (HealthComp->GetHealthPercent());
}

bool USTMPlayerHudWidget::GetCurrentWeaponUIData(FWeaponUIData &UIData)
{
    const auto WeaponComp = this->GetComponent<USTMWeaponComponent>();
    if (!WeaponComp)
        return (false);
    return (WeaponComp->GetWeaponUIData(UIData));
}

bool USTMPlayerHudWidget::GetCurrentAmmoData(FAmmoData &AmmoData)
{
    const auto WeaponComp = this->GetComponent<USTMWeaponComponent>();
    if (!WeaponComp)
        return (false);
    return (WeaponComp->GetAmmoUIData(AmmoData));
}

bool USTMPlayerHudWidget::IsPlayerAlive() const
{
    const auto HealthComp = this->GetComponent<UHealthComponent>();
    return (HealthComp && !HealthComp->IsDead());
}

bool USTMPlayerHudWidget::IsPlayerSpectating() const
{
    const auto Contoller = GetOwningPlayer();
    return (Contoller && Contoller->GetStateName() == NAME_Spectating);
}
