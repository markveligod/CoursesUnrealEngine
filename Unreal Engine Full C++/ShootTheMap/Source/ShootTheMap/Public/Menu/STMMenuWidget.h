// ShootTheMap

#pragma once

#include "UI/STMBaseWidget.h"
#include "CoreMinimal.h"
#include "STMMenuWidget.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMMenuWidget : public USTMBaseWidget
{
    GENERATED_BODY()
  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton *QuitGameButton;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation *HideAnimation;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;


  private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();
};
