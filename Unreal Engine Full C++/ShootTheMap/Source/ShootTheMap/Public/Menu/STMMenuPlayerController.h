// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STMMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMAP_API ASTMMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
  protected:
	virtual void BeginPlay() override;
};
