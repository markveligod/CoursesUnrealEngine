// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API ASTMMenuHUD : public AHUD
{
	GENERATED_BODY()
  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
    virtual void BeginPlay() override;
};
