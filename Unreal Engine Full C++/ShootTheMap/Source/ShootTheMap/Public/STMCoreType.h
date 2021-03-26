#pragma once

#include "STMCoreType.generated.h"
// Weapon editor

class ASTMBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClimpEmptySignature, ASTMBaseWeapon*);

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
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDeathChange, float, float);


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

//VFX

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface *Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f;

};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_USTRUCT_BODY();
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayerSpawn = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 NumRounds = 4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "10", ClampMax = "300"))
    int32 RoundTime = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RespawnTime = 5;
};
