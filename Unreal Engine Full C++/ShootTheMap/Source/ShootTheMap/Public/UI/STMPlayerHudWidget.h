// ShootTheMap

#pragma once

#include "UI/STMBaseWidget.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "STMPlayerHudWidget.generated.h"

/**
 *
 */

UCLASS()
class SHOOTTHEMAP_API USTMPlayerHudWidget : public USTMBaseWidget
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

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

  protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation *DamageAnim;
    virtual void NativeOnInitialized() override;

  private:
    void OnHealthChanched(float Health, float HealthDelta);
    void OnNewPawn(APawn *NewPawn);
};
