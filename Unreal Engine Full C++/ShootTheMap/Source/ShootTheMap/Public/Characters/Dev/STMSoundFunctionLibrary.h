// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STMSoundFunctionLibrary.generated.h"

class USoundClass;
/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMSoundFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
  public:
    UFUNCTION(BlueprintCallable)
    static bool IsToggleVolumeOn(USoundClass *SoundClass);

	UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass *SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass *SoundClass);

};
