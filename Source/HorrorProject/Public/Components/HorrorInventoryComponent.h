// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorInventoryComponent.generated.h"

class AHorrorPickupBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROJECT_API UHorrorInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHorrorInventoryComponent();
    bool AddItemToInventory(AHorrorPickupBase* Item);

protected:
    virtual void BeginPlay() override;
    bool AddUnstackItemToInventory(AHorrorPickupBase* Item);
    bool AddStackItemToInventory(AHorrorPickupBase* Item);

private:
    TArray<AHorrorPickupBase*> Inventory;
};
