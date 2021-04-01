// ShootTheMap


#include "UI/STMBaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USTMBaseWidget::Show()
{
    PlayAnimation(this->ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), this->OpenWidgetSound);
}
