// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STMPlayerController.generated.h"

class USTMRestartComponent;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMPlayerController : public APlayerController
{
    GENERATED_BODY()
  public:
    ASTMPlayerController();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edit")
    USTMRestartComponent *STMRestartComponent;

    virtual void SetupInputComponent();

  private:
    void OnPauseGame();
};
