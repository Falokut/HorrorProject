// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorInventoryComponent.h"

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHorrorInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}
