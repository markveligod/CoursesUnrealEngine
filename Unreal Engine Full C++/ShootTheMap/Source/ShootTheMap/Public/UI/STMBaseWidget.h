// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMBaseWidget.generated.h"

class USoundCue;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMBaseWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    void Show();

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound Editor")
    USoundCue *OpenWidgetSound;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation *ShowAnimation;
};
