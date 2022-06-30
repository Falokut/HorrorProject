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
}

void UHorrorInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UHorrorInventoryComponent::AddUnstackItemToInventory(AHorrorPickupBase* Item)
{
    return false;
}

bool UHorrorInventoryComponent::AddStackItemToInventory(AHorrorPickupBase* Item)
{
    return false;
}
