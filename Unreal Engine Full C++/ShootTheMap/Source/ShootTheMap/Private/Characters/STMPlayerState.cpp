// ShootTheMap


#include "Characters/STMPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTMPlayerState, All, All);

void ASTMPlayerState::SetTeamID(int32 ID)
{
    this->TeamID = ID;
}

int32 ASTMPlayerState::GetTeamID() const
{
    return (this->TeamID);
}

void ASTMPlayerState::SetColor(FLinearColor Color)
{
    this->TeamColor = Color;
}

FLinearColor ASTMPlayerState::GetColor() const
{
    return (this->TeamColor);
}

void ASTMPlayerState::AddKill()
{
    this->KillsNum++;
}

void ASTMPlayerState::AddDeath()
{
    this->DeathsNum++;
}

int32 ASTMPlayerState::GetKillStats() const
{
    return (this->KillsNum);
}

int32 ASTMPlayerState::GetDeathStats() const
{
    return (this->DeathsNum);
}

void ASTMPlayerState::LogInfo()
{
    UE_LOG(LogSTMPlayerState, Display, TEXT("Name: %s TeamID: %i => Kill: %i, Death: %i"), *GetOwner()->GetName(), this->TeamID, this->KillsNum, this->DeathsNum);
}
