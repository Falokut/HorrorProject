// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorCharacterMovementComponent.h"
#include "Player/HorrorCharacterBase.h"

float UHorrorCharacterMovementComponent::GetMaxSpeed() const
{
    const auto Character = Cast<AHorrorCharacterBase>(GetOwner());
    if (!Character) return 0.0f;

    const float MaxSpeed = Super::GetMaxSpeed();
    return Character->IsRunning() ? MaxSpeed * AccelerationModify : MaxSpeed;
}
