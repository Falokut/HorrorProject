// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/HorrorPickupBase.h"
#include "Player/HorrorCharacterBase.h"
#include "Components/HorrorInventoryComponent.h"
#include "HorrorUtils.h"

void AHorrorPickupBase::Interact_Implementation(AActor* Caller)
{
    if (bPickedUp) return;

    const auto Player = Cast<AHorrorCharacterBase>(Caller);
    if (!Player) return;
    const auto Inventory = HorrorUtils::GetHorrorPlayerComponent<UHorrorInventoryComponent>(Player);
    if (!Inventory) return;

    if (Inventory->AddItemToInventory(this)) OnPickedUp();
}

void AHorrorPickupBase::Use()
{
    UpdateAmount(-1);
    if (ItemData.Amount == 0)
    {
        Destroy();
        return;
    }
}

void AHorrorPickupBase::BeginPlay()
{
    Super::BeginPlay();
    checkf(InteractiveMesh, TEXT("Mesh isn't set"));
    checkf(ItemData.Amount < ItemData.MaxAmount, TEXT("Amount can't be bigger than MaxAmount"));
}

void AHorrorPickupBase::OnPickedUp()
{
    InteractiveMesh->SetVisibility(false, true);
    InteractiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    bPickedUp = true;
}

void AHorrorPickupBase::OnEquiped(bool bIsEquiping)
{
    if (bIsEquiping)
    {
        InteractiveMesh->SetVisibility(true, true);
        InteractiveMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
    else
    {
        InteractiveMesh->SetVisibility(false, true);
        InteractiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
