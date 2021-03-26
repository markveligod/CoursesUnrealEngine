// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32 &CountTimeData) const;
	
};
