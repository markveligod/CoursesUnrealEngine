// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "STMPlayerHudWidget.generated.h"

/**
 *
 */

UCLASS()
class SHOOTTHEMAP_API USTMPlayerHudWidget : public UUserWidget
{
    GENERATED_BODY()
  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPrecent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData &UIData);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentAmmoData(FAmmoData &AmmoData);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    private:
    template <typename T> T *GetComponent() const;
};

template <typename T> T * USTMPlayerHudWidget::GetComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return (nullptr);
    const auto Component = Player->GetComponentByClass(T::StaticClass());
    return (Cast<T>(Component));
}
