// ShootTheMap

#include "UI/STMGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "GameModes/STMGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTMGameHUD, All, All);

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

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTMGameHUD::OnMatchChanged);
        }
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

void ASTMGameHUD::OnMatchChanged(ESTMMatchState NewState)
{
    UE_LOG(LogSTMGameHUD, Display, TEXT("Match State: %s"), *UEnum::GetValueAsString(NewState))
}
