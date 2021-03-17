// ShootTheMap

#include "UI/STMPlayerHudWidget.h"
#include "Components/HealthComponent.h"
#include "STMWeaponComponent.h"

float USTMPlayerHudWidget::GetHealthPrecent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return (0.f);
    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComp = Cast<UHealthComponent>(Component);
    if (!HealthComp)
        return (0.f);
    return (HealthComp->GetHealthPercent());
}

bool USTMPlayerHudWidget::GetWeaponUIData(FWeaponUIData &UIData)
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return (false);
    const auto Component = Player->GetComponentByClass(USTMWeaponComponent::StaticClass());
    const auto WeaponComp = Cast<USTMWeaponComponent>(Component);
    if (!WeaponComp)
        return (false);
    return (WeaponComp->GetWeaponUIData(UIData));
}
