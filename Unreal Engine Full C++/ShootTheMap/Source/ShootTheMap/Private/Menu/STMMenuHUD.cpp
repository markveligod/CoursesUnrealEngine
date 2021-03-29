// ShootTheMap


#include "Menu/STMMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTMMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (this->MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
