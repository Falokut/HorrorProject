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
    const auto Inventory = HorrorUtils::GetShooterPlayerComponent<UHorrorInventoryComponent>(Player);
    if (!Inventory) return;

    if (Inventory->AddItemToInventory(this)) OnPickedUp();
}

void AHorrorPickupBase::Use()
{
    if (ItemData.Amount == 0)
    {
        Destroy();
        return;
    }
    UpdateAmount(-1);
}

void AHorrorPickupBase::OnPickedUp()
{
    InteractiveMesh->SetVisibility(false, true);
    InteractiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    bPickedUp = true;
}
