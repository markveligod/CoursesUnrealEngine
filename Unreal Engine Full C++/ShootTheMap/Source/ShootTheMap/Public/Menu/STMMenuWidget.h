// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMMenuWidget.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMMenuWidget : public UUserWidget
{
    GENERATED_BODY()
  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;

    virtual void NativeOnInitialized() override;

  private:
    UFUNCTION()
    void OnStartGame();
};
