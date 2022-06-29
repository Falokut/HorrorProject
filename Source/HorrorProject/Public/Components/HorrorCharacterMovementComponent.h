// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HorrorCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROJECT_API UHorrorCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
protected:
    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = 1.1f, UIMin = 1.1f, ClampMax = 2.0f, UIMax = 2.0f))
    float AccelerationModify = 1.5f;

    virtual float GetMaxSpeed() const override;
};
