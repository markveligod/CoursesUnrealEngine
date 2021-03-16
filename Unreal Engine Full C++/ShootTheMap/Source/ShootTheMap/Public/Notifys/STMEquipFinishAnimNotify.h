// ShootTheMap

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "STMEquipFinishAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySignature, USkeletalMeshComponent*);

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMEquipFinishAnimNotify : public UAnimNotify
{
    GENERATED_BODY()
  public:
    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

    FOnNotifySignature OnNotifySignature;
};
