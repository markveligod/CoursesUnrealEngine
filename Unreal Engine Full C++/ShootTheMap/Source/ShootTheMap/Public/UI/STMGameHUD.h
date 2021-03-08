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

  private:
    void DrawCrossHair();
};
