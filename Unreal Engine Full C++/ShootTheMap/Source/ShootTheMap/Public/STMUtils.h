#pragma once

#include "GameFramework/Pawn.h"

class STMUtils
{
  public:
    template <typename T> static T *GetComponent(AActor *Player);
};

template <typename T> T *STMUtils::GetComponent(AActor *Player)
{
    if (!Player)
        return (nullptr);
    const auto Component = Player->GetComponentByClass(T::StaticClass());
    return (Cast<T>(Component));
}
