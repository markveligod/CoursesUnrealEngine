// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

    virtual void BeginPlay() override;

  private:
    void DrawCrossHair();
};
