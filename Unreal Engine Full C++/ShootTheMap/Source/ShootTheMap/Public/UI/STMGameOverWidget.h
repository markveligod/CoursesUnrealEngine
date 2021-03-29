// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "STMGameOverWidget.generated.h"

class UVerticalBox;
class UButton;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox *PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PLayerStatWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton *ResetLevelButton;

    virtual void NativeOnInitialized() override;

    private:
    void OnMatchStateChanged(ESTMMatchState State);
    void UpdatePlayerState();

    UFUNCTION()
    void OnResetLevel();
};
