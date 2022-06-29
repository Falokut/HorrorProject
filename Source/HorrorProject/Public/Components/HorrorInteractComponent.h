// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorInteractComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROJECT_API UHorrorInteractComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHorrorInteractComponent();

protected:
    virtual void BeginPlay() override;

public:
};
