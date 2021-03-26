// ShootTheMap

#include "AI/EnvQueryTest_PickUpCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "PickUps/STMBasePickUp.h"

UEnvQueryTest_PickUpCouldBeTaken::UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickUpCouldBeTaken::RunTest(FEnvQueryInstance &QueryInstance) const
{
    UObject *DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);

    bool bWantsHit = BoolValue.GetValue();
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor *ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickUpActor = Cast<ASTMBasePickUp>(ItemActor);
        if (!PickUpActor)
            continue;
        const auto CouldBeTaken = PickUpActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, bWantsHit);


    }
}
