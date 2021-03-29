// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMPauseWidget.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMPauseWidget : public UUserWidget
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
