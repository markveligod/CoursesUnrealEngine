// ShootTheMap


#include "AI/STMAIPerceptionComponent.h"
#include "AIController.h"
#include "STMUtils.h"
#include "Characters/Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor * USTMAIPerceptionComponent::GetClosesEnemy() const
{
    TArray<AActor *> PerciveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerciveActors);

    const auto Controller = Cast<AController>(GetOwner());

    if (PerciveActors.Num() == 0 || !Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor *BestActor = nullptr;
    for (const auto Actor : PerciveActors)
    {
        const auto HealthComp = STMUtils::GetComponent<UHealthComponent>(Actor);

        const auto PercievePawn = Cast<APawn>(Actor);
        const auto AreEnemies = PercievePawn && STMUtils::AreEnemies(Controller, PercievePawn->Controller);
        if (HealthComp && !HealthComp->IsDead() && AreEnemies) // TODO: check enemy or not
        {
            const auto CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestActor = Actor;
            }
        }
    }
    return (BestActor);
}
