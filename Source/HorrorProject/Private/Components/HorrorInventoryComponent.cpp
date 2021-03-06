// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorInventoryComponent.h"
#include "Items/HorrorPickupBase.h"
#include "HorrorCoreTypes.h"
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
    Inventory[AvalibleSlot] = Item;
    NewItemAdd.Broadcast(AvalibleSlot);

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

    OnItemAdd.Broadcast(AvalibleSlot);

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
        Item->Destroy();
        return true;
    }
}
void UHorrorInventoryComponent::SpawnEquipedItem()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || !Character->GetMesh() || !Inventory[CurrentIndex]) return;

    if (!Inventory.IsValidIndex(CurrentIndex) || !Inventory[CurrentIndex]) return;
    FAttachmentTransformRules AttachmentRules(
        EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
    Inventory[CurrentIndex]->AttachToComponent(Character->GetMesh(), AttachmentRules, EquipmentSoketName);
    Inventory[CurrentIndex]->OnEquiped(true);
}

void UHorrorInventoryComponent::RemoveCurrentItem()
{
    Inventory[CurrentIndex] = nullptr;
    OnItemRemove.Broadcast(CurrentIndex);
    CurrentIndex = INDEX_NONE;
}

void UHorrorInventoryComponent::UseEquipedItem()
{
    if (!Inventory.IsValidIndex(CurrentIndex) || !Inventory[CurrentIndex]) return;

    Inventory[CurrentIndex]->Use();
    if (Inventory[CurrentIndex]->GetItemData().Amount == 0)
    {
        RemoveCurrentItem();
    }
}

void UHorrorInventoryComponent::EquipItemAtSlot(char Index)
{
    int32 NewIndex = (Index - '0');
    if (!Inventory.IsValidIndex(NewIndex)) return;

    if (!Inventory.IsValidIndex(CurrentIndex) || !Inventory[CurrentIndex])
    {
        CurrentIndex = NewIndex;
    }
    else
    {
        Inventory[CurrentIndex]->OnEquiped(false);
        CurrentIndex = NewIndex;
    }
    OnItemEquipped.Broadcast(CurrentIndex);
    SpawnEquipedItem();
}

AHorrorPickupBase* UHorrorInventoryComponent::GetItemAtInventoryByIndex(const int32 Index) const
{
    if (!Inventory.IsValidIndex(Index)) return nullptr;
    return Inventory[Index];
}

void UHorrorInventoryComponent::DropEquipedItem()
{
    if (CurrentIndex == INDEX_NONE || !Inventory[CurrentIndex]) return;

    FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, false);

    if (Inventory[CurrentIndex]->GetItemData().Amount == 1)
    {
        Inventory[CurrentIndex]->DetachFromActor(DetachmentRules);
        Inventory[CurrentIndex]->OnDropped();
        RemoveCurrentItem();
        return;
    }

    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    const int32 DroppingRange = 100;
    FVector Location = Character->GetMesh()->GetSocketLocation(EquipmentSoketName) + Character->GetActorForwardVector() * DroppingRange;

    const auto NewItem =
        GetWorld()->SpawnActor<AHorrorPickupBase>(Inventory[CurrentIndex]->GetItemData().ItemClass, Location, FRotator::ZeroRotator);
    if (!NewItem) return;

    NewItem->DetachFromActor(DetachmentRules);
    NewItem->OnDropped();
    Inventory[CurrentIndex]->UpdateAmount(-1);
}
