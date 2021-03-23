// ShootTheMap

#pragma once

#include "Characters/STMBaseCharacter.h"
#include "CoreMinimal.h"
#include "STMAICharacter.generated.h"

class UBehaviorTree;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMAICharacter : public ASTMBaseCharacter
{
    GENERATED_BODY()

  public:
    ASTMAICharacter(const FObjectInitializer &ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tree")
    UBehaviorTree *BehaviorTreeAsset;
};
