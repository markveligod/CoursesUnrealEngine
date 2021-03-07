// ShootTheMap

#include "Weapons/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


ASTMBaseWeapon::ASTMBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    this->WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
    SetRootComponent(this->WeaponMesh);
}

void ASTMBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
