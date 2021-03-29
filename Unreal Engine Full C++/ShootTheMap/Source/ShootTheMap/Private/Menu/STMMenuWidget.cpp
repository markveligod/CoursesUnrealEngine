// ShootTheMap


#include "Menu/STMMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTMMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (this->StartGameButton)
    {
        this->StartGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnStartGame);
    }

}

void USTMMenuWidget::OnStartGame()
{
    const FName NameLevel = "TestLevel";
    UGameplayStatics::OpenLevel(this, NameLevel);
}
