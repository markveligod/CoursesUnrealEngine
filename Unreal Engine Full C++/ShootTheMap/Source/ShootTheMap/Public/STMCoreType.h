#pragma once
#include "STMCoreType.generated.h"
// Weapon editor

DECLARE_MULTICAST_DELEGATE(FOnClimpEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
    int32 Bullet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (EditCondition = "!bInfinity"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
    bool bInfinity;
};

class ASTMBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    UAnimMontage *AnimReload;
};

// Health editor

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathChange, float);


//Widget Editor

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY();
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *MainIcon;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *CrosshairIcon;
};
