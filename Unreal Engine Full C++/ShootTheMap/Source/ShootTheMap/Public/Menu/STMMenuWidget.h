// ShootTheMap

#pragma once

#include "UI/STMBaseWidget.h"
#include "CoreMinimal.h"
#include "STMMenuWidget.generated.h"

class UButton;
class USoundCue;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMMenuWidget : public USTMBaseWidget
{
    GENERATED_BODY()
  public:
    UFUNCTION(BlueprintCallable)
    bool IsToggleVolumeOn() const;
  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton *QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton *SoundGameButton;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation *HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound Editor")
    USoundCue *StartGameSound;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;


  private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    UFUNCTION()
    void ToggleVolume();
};
