// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HorrorInteractiveBase.h"
#include "HorrorCoreTypes.h"
#include "HorrorPickupBase.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROJECT_API AHorrorPickupBase : public AHorrorInteractiveBase
{
    GENERATED_BODY()
public:
    virtual void Interact_Implementation(AActor* Caller) override;

    UFUNCTION(BlueprintCallable, Category = "Pickup functions")
    FItemData GetItemData() const { return ItemData; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup propeties")
    FItemData ItemData;
};
