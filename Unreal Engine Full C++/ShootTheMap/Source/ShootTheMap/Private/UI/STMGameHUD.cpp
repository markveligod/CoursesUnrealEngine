// ShootTheMap

#include "UI/STMGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/STMBaseWidget.h"
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

    this->GameWidgets.Add(ESTMMatchState::InProgress,
                          CreateWidget<USTMBaseWidget>(GetWorld(), this->PlayerHudWidgetClass));
    this->GameWidgets.Add(ESTMMatchState::Pause, CreateWidget<USTMBaseWidget>(GetWorld(), this->PauseHudWidgetClass));
    this->GameWidgets.Add(ESTMMatchState::GameOver,
                          CreateWidget<USTMBaseWidget>(GetWorld(), this->GameOverHudWidgetClass));
    

    for (auto TempGameWidgetPair : this->GameWidgets)
    {
        const auto TempGameValueWidget = TempGameWidgetPair.Value;
        if (!TempGameValueWidget) continue;

        TempGameValueWidget->AddToViewport();
        TempGameValueWidget->SetVisibility(ESlateVisibility::Hidden);
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
    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (this->GameWidgets.Contains(NewState))
    {
        this->CurrentWidget = this->GameWidgets[NewState];
    }

    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        this->CurrentWidget->Show();
    }

    UE_LOG(LogSTMGameHUD, Display, TEXT("Match State: %s"), *UEnum::GetValueAsString(NewState))
}
