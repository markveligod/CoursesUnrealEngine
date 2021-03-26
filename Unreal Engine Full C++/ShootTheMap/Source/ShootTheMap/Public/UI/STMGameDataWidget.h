// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMGameDataWidget.generated.h"

class ASTMGameModeBase;
class ASTMPlayerState;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMGameDataWidget : public UUserWidget
{
    GENERATED_BODY()
  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondRemaining() const;

  private:
    ASTMGameModeBase *GetSTMGameMode() const;
    ASTMPlayerState *GetSTMPlayerState() const;
};
