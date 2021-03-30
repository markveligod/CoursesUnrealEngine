// ShootTheMap

#pragma once

#include "UI/STMBaseWidget.h"
#include "CoreMinimal.h"
#include "STMPauseWidget.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMPauseWidget : public USTMBaseWidget
{
    GENERATED_BODY()

  protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton *ClearPauseButton;

  private:
    UFUNCTION()
    void OnClearPause();
};
