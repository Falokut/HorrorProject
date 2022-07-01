// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorInventoryComponent.h"
#include "Items/HorrorPickupBase.h"

static const int32 InventorySize = 5;

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UHorrorInventoryComponent::AddItemToInventory(AHorrorPickupBase* Item)
{
    if (!Item) return false;
    return Item->GetItemData().bIsStackable ? AddStackItemToInventory(Item) : AddNewItemToInventory(Item);
}

AHorrorPickupBase* UHorrorInventoryComponent::GetItemAtSlot(const int32 SlotIndex)
{
    if (!Inventory.IsValidIndex(SlotIndex)) return nullptr;
    return Inventory[SlotIndex];
}

void UHorrorInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    Inventory.SetNum(InventorySize);
}

bool UHorrorInventoryComponent::AddNewItemToInventory(AHorrorPickupBase* Item)
{
    const int32 AvalibleSlot = Inventory.Find(nullptr);
    if (AvalibleSlot == INDEX_NONE) return false;
    NewItemAdd.Broadcast(Item);

    Inventory[AvalibleSlot] = Item;
    return true;
}

bool UHorrorInventoryComponent::AddStackItemToInventory(AHorrorPickupBase* Item)
{
    if (Item->GetItemData().Amount == Item->GetItemData().MaxAmount) return AddNewItemToInventory(Item);

    const int32 AvalibleSlot = Inventory.IndexOfByPredicate([&Item](AHorrorPickupBase* FindItem)
        { return !FindItem ? false : Item->GetItemData().ItemUniqueName == FindItem->GetItemData().ItemUniqueName; });
    if (AvalibleSlot == INDEX_NONE) return AddNewItemToInventory(Item);

    if (Item->GetItemData().Amount + Inventory[AvalibleSlot]->GetItemData().Amount <= Item->GetItemData().MaxAmount)
    {
        const int32 Surplus = Item->GetItemData().MaxAmount - Item->GetItemData().Amount - Inventory[AvalibleSlot]->GetItemData().Amount;
        Inventory[AvalibleSlot]->UpdateAmount(Surplus);
        return true;
    }

    else
    {
        const int32 Surplus =
            FMath::Clamp(Item->GetItemData().Amount + Inventory[AvalibleSlot]->GetItemData().Amount, 0, Item->GetItemData().MaxAmount);
        Inventory[AvalibleSlot]->UpdateAmount(Surplus);
        Item->UpdateAmount(-Surplus);
        return AddStackItemToInventory(Item);
    }
}
