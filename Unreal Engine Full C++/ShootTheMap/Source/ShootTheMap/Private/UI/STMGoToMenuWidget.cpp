// ShootTheMap


#include "UI/STMGoToMenuWidget.h"
#include "Components/Button.h"
#include "STMGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All);

void USTMGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (this->GoToMenuButton)
    {
        this->GoToMenuButton->OnClicked.AddDynamic(this, &USTMGoToMenuWidget::OnGoToMenu);
    }
}

void USTMGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld())
        return;

    const auto STMGameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!STMGameInstance)
        return;

    if (STMGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogGoToMenuWidget, Error, TEXT("Menu Level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, STMGameInstance->GetMenuLevelName());
}
