// ShootTheMap


#include "Menu/STMMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STMGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

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
}

void USTMMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
