// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorCoreTypes.h"
#include "HorrorInventoryComponent.generated.h"

class AHorrorPickupBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROJECT_API UHorrorInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHorrorInventoryComponent();
    bool AddItemToInventory(AHorrorPickupBase* Item);
    void UseEquipedItem();

    //Возвращает индекс экипированного предмета
    UFUNCTION(BlueprintCallable, Category = "Inventory functions")
    int32 GetCurrentIndex() const { return CurrentIndex; }

    void EquipItemAtSlot(const unsigned int Slot);

    UPROPERTY(BlueprintAssignable, Category = "Inventory Delegates")
    FOnNewItemAddSignature NewItemAdd;

    UPROPERTY(BlueprintAssignable, Category = "Inventory Delegates")
    FOnItemAddSignature OnItemAdd;
    UPROPERTY(BlueprintAssignable, Category = "Inventory Delegates")
    FOnItemRemoveSignature OnItemRemove;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
    FName EquipmentSoketName = "EquipmentSoket";

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsInventoryEmpty() const;

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    bool AddNewItemToInventory(AHorrorPickupBase* Item);
    bool AddStackItemToInventory(AHorrorPickupBase* Item);

private:
    TArray<AHorrorPickupBase*> Inventory;
    void SpawnEquipedItem();

    //Индекс экипированного предмета
    unsigned int CurrentIndex = 0;
};
