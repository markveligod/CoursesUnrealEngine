#pragma once

#include "GameFramework/Pawn.h"
#include "Characters/STMPlayerState.h"

class STMUtils
{
  public:
    template <typename T> static T *GetComponent(AActor *Player);
    bool static AreEnemies(AController *Controller1, AController *Controller2);
};

inline bool STMUtils::AreEnemies(AController *Controller1, AController *Controller2)
{
    if (!Controller1 || !Controller2 || Controller1 == Controller2)
        return (false);

    const auto PlayerState1 = Cast<ASTMPlayerState>(Controller1->PlayerState);
    const auto PlayerState2 = Cast<ASTMPlayerState>(Controller2->PlayerState);

    return (PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID());
}

template <typename T> T *STMUtils::GetComponent(AActor *Player)
{
    if (!Player)
        return (nullptr);
    const auto Component = Player->GetComponentByClass(T::StaticClass());
    return (Cast<T>(Component));
}
