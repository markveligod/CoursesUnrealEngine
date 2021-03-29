// ShootTheMap


#include "UI/STMPauseWidget.h"
#include "GameModes/STMGameModeBase.h"
#include "Components/Button.h"

void USTMPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (this->ClearPauseButton)
    {
        this->ClearPauseButton->OnClicked.AddDynamic(this, &USTMPauseWidget::OnClearPause);
    }
}

void USTMPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
