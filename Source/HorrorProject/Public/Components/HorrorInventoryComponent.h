// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorInventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROJECT_API UHorrorInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHorrorInventoryComponent();

protected:
    virtual void BeginPlay() override;
};
