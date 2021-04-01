// ShootTheMap


#include "Characters/Dev/STMSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTMSoundFunctionLibrary, All, All);

bool USTMSoundFunctionLibrary::IsToggleVolumeOn(USoundClass *SoundClass)
{
    return (SoundClass->Properties.Volume > 0.f);
}

void USTMSoundFunctionLibrary::SetSoundClassVolume(USoundClass *SoundClass, float Volume)
{
    if (!SoundClass)
        return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f);
    UE_LOG(LogSTMSoundFunctionLibrary, Display, TEXT("%s set volume => %f"), *SoundClass->GetName(),
           SoundClass->Properties.Volume);
}

void USTMSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass *SoundClass)
{
    if (!SoundClass)
        return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
