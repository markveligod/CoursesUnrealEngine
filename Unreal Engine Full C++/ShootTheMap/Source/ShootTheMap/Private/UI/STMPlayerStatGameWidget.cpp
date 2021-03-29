// ShootTheMap


#include "UI/STMPlayerStatGameWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTMPlayerStatGameWidget::SetPlayerName(const FText &Text)
{
    if (!this->PlayerNameTextBlock)
        return;
    this->PlayerNameTextBlock->SetText(Text);
}

void USTMPlayerStatGameWidget::SetKills(const FText &Text)
{
    if (!this->KillsTextBlock)
        return;
    this->KillsTextBlock->SetText(Text);
}

void USTMPlayerStatGameWidget::SetDeaths(const FText &Text)
{
    if (!this->DeathsTextBlock)
        return;
    this->DeathsTextBlock->SetText(Text);
}

void USTMPlayerStatGameWidget::SetTeamID(const FText &Text)
{
    if (!this->TeamIDTextBlock)
        return;
    this->TeamIDTextBlock->SetText(Text);
}

void USTMPlayerStatGameWidget::SetPlayerIndicatorVisibillity(bool Visible)
{
    if (!this->PlayerIndicatorImage)
        return;
    this->PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
