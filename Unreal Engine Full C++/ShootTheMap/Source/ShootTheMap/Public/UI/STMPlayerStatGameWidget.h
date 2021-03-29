// ShootTheMap

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STMPlayerStatGameWidget.generated.h"

class UImage;
class UTextBlock;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMPlayerStatGameWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    void SetPlayerName(const FText &Text);
    void SetKills(const FText &Text);
    void SetDeaths(const FText &Text);
    void SetTeamID(const FText &Text);
    void SetPlayerIndicatorVisibillity(bool Visible);

  protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock *PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *TeamIDTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage *PlayerIndicatorImage;
};
