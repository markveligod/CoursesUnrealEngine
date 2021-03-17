#pragma once
#include "Animation/AnimSequenceBase.h"

class AnimUtils
{
  public:
    template <typename T> static T *FindNotifyByClass(UAnimSequenceBase *Animation);
};

template <typename T> T *AnimUtils::FindNotifyByClass(UAnimSequenceBase *Animation)
{
    if (!Animation)
        return (nullptr);
    const auto NotifyEvents = Animation->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto AnimNotify = Cast<T>(NotifyEvent.Notify);
        if (AnimNotify)
        {
            return (AnimNotify);
        }
    }
    return (nullptr);
}
