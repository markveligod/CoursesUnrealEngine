// ShootTheMap


#include "UI/STMPauseWidget.h"
#include "GameModes/STMGameModeBase.h"
#include "Components/Button.h"

bool USTMPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (this->ClearPauseButton)
    {
        this->ClearPauseButton->OnClicked.AddDynamic(this, &USTMPauseWidget::OnClearPause);
    }
    return (InitStatus);
}

void USTMPauseWidget::OnClearPause()
{

}
