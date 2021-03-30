// ShootTheMap


#include "Menu/STMMenuHUD.h"
#include "UI/STMBaseWidget.h"

void ASTMMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (this->MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USTMBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
