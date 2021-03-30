// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMCoreType.h"
#include "STMGameHUD.generated.h"

class USTMBaseWidget;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMGameHUD : public AHUD
{
    GENERATED_BODY()
  public:
    virtual void DrawHUD() override;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseHudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverHudWidgetClass;

    virtual void BeginPlay() override;

  private:
    UPROPERTY()
    TMap<ESTMMatchState, USTMBaseWidget *> GameWidgets;

    UPROPERTY()
    USTMBaseWidget *CurrentWidget;

    void DrawCrossHair();
    void OnMatchChanged(ESTMMatchState NewState);
};
