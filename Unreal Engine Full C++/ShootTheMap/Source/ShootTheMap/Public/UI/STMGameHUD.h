// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMCoreType.h"
#include "STMGameHUD.generated.h"

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

    virtual void BeginPlay() override;

  private:
    UPROPERTY()
    TMap<ESTMMatchState, UUserWidget *> GameWidgets;

    UPROPERTY()
    UUserWidget *CurrentWidget;

    void DrawCrossHair();
    void OnMatchChanged(ESTMMatchState NewState);
};
