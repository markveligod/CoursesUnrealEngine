// ShootTheMap

#include "Notifys/STMEquipFinishAnimNotify.h"

void USTMEquipFinishAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    this->OnNotifySignature.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
