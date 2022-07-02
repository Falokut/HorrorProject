// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorInventoryComponent.h"
#include "Items/HorrorPickupBase.h"
#include "GameFramework/Character.h"
#include "Containers/Array.h"

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

bool UHorrorInventoryComponent::IsInventoryEmpty() const
{
    const int32 Slot = Inventory.Find(nullptr);
    return Slot != INDEX_NONE;
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

    const int32 AvalibleSlot = Inventory.IndexOfByPredicate(
        [&Item](AHorrorPickupBase* FindItem)
        {
            return FindItem && FindItem->GetItemData().MaxAmount > FindItem->GetItemData().Amount &&
                   FindItem->GetItemData().ItemUniqueName == Item->GetItemData().ItemUniqueName;
        });

    if (AvalibleSlot == INDEX_NONE) return AddNewItemToInventory(Item);

    OnItemAdd.Broadcast();

    if (Item->GetItemData().Amount + Inventory[AvalibleSlot]->GetItemData().Amount > Item->GetItemData().MaxAmount)
    {
        const int32 Surplus = Item->GetItemData().Amount + Inventory[AvalibleSlot]->GetItemData().Amount - Item->GetItemData().MaxAmount;
        Inventory[AvalibleSlot]->UpdateAmount(Surplus);
        Item->UpdateAmount(-Surplus);
        return AddStackItemToInventory(Item);
    }

    else
    {
        Inventory[AvalibleSlot]->UpdateAmount(Item->GetItemData().Amount);
        return true;
    }
}
void UHorrorInventoryComponent::SpawnEquipedItem()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || !Character->GetMesh()) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Inventory[CurrentIndex]->AttachToComponent(Character->GetMesh(), AttachmentRules, EquipmentSoketName);
    Inventory[CurrentIndex]->OnEquiped(true);
}

void UHorrorInventoryComponent::UseEquipedItem()
{
    if (!Inventory[CurrentIndex]) return;
    Inventory[CurrentIndex]->Use();
    if (Inventory[CurrentIndex]->GetItemData().Amount == 0)
    {
        Inventory[CurrentIndex] = nullptr;
        OnItemRemove.Broadcast(CurrentIndex);

        //Переключение на следующий предмет
        const int32 NewIndex = Inventory.IndexOfByPredicate([](AHorrorPickupBase* FindItem) { return FindItem; });
        if (NewIndex != INDEX_NONE) EquipItemAtSlot(NewIndex);
    }
}

void UHorrorInventoryComponent::EquipItemAtSlot(const unsigned int Slot)
{
    if (!Inventory.IsValidIndex(Slot) || !Inventory[Slot]) return;

    Inventory[Slot]->OnEquiped(false);
    CurrentIndex = Slot;
    SpawnEquipedItem();
}
