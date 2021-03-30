// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMBaseWidget.generated.h"

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
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation *ShowAnimation;
};
