// ShootTheMap


#include "Menu/STMMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STMGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "Characters/Dev/STMSoundFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);


void USTMMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (this->StartGameButton)
    {
        this->StartGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnStartGame);
    }
    if (this->QuitGameButton)
    {
        this->QuitGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnQuitGame);
    }
    if (this->SoundGameButton)
    {
        this->SoundGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::ToggleVolume);
    }

}

void USTMMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if (!GetWorld() || this->HideAnimation != Animation)
        return;

    const auto STMGameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!STMGameInstance)
        return;

    if (STMGameInstance->GetStartUpLevelName().IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Level name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, STMGameInstance->GetStartUpLevelName());
}

void USTMMenuWidget::OnStartGame()
{
    PlayAnimation(this->HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), this->StartGameSound);
}

void USTMMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTMMenuWidget::ToggleVolume()
{
    if (!GetWorld())
        return;

    const auto STMGameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!STMGameInstance)
        return;

    USTMSoundFunctionLibrary::ToggleSoundClassVolume(STMGameInstance->GetSoundMaterClass());
}

bool USTMMenuWidget::IsToggleVolumeOn() const
{
    if (!GetWorld())
        return false;

    const auto STMGameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!STMGameInstance)
        return false;
    return USTMSoundFunctionLibrary::IsToggleVolumeOn(STMGameInstance->GetSoundMaterClass());
}
