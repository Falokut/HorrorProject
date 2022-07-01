// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/HorrorInteractiveBase.h"

AHorrorInteractiveBase::AHorrorInteractiveBase()
{
    PrimaryActorTick.bCanEverTick = false;
    InteractiveMesh = CreateDefaultSubobject<UStaticMeshComponent>("InteractiveMesh");
}

void AHorrorInteractiveBase::Interact_Implementation(AActor* Caller)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, TEXT("Interaction"));
}

void AHorrorInteractiveBase::StartFocus_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, TEXT("StartFocus"));
}

void AHorrorInteractiveBase::EndFocus_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, TEXT("EndFocus"));
}

void AHorrorInteractiveBase::BeginPlay()
{
    Super::BeginPlay();
}
