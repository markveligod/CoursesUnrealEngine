// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMGoToMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *GoToMenuButton;

    virtual void NativeOnInitialized() override;

    private:
    UFUNCTION()
    void OnGoToMenu();
};
