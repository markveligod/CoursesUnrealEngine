// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMPauseWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMPauseWidget : public UUserWidget
{
	GENERATED_BODY()
  public:
    virtual bool Initialize() override;

	protected:
    UPROPERTY(meta = (BindWidget))
    UButton *ClearPauseButton;

    private:
    UFUNCTION()
    void OnClearPause();
};
