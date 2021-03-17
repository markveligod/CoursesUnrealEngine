// ShootTheMap


#include "Notifys/STMAnimNotify.h"

void USTMAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    this->OnNotifySignature.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
