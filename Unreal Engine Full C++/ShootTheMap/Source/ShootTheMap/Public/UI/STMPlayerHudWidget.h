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
    bool GetWeaponUIData(FWeaponUIData &UIData);
};
