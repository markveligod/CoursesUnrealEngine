// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STMGameInstance.generated.h"

class USoundClass;
/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMGameInstance : public UGameInstance
{
    GENERATED_BODY()

  public:
    FName GetStartUpLevelName() const;
    FName GetMenuLevelName() const;
    USoundClass* GetSoundMaterClass() const;

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game Level")
    FName StartUpLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game Level")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound Master")
    USoundClass *SoundMasterClass;
};
