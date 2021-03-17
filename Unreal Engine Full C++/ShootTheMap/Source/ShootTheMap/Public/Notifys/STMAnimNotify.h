// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STMAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySignature, USkeletalMeshComponent *);

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API USTMAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
  public:
    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

    FOnNotifySignature OnNotifySignature;
};
