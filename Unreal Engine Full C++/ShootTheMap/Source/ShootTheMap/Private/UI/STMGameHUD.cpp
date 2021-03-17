// ShootTheMap

#include "UI/STMGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTMGameHUD::DrawHUD()
{
    Super::DrawHUD();
    //this->DrawCrossHair();
}

void ASTMGameHUD::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), this->PlayerHudWidgetClass);
    if (PlayerHudWidget)
    {
        PlayerHudWidget->AddToViewport();
    }
}

void ASTMGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.f;
    const float LineThinkness = 2.f;
    const FLinearColor LineColor = FLinearColor::Green;
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThinkness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThinkness);
}
