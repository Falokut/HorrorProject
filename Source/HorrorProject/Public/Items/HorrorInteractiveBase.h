// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/HorrorInteractiveInterface.h"
#include "HorrorInteractiveBase.generated.h"

UCLASS()
class HORRORPROJECT_API AHorrorInteractiveBase : public AActor, public IHorrorInteractiveInterface
{
    GENERATED_BODY()

public:
    AHorrorInteractiveBase();

    virtual void Interact_Implementation(AActor* Caller) override;
    virtual void StartFocus_Implementation() override;
    virtual void EndFocus_Implementation() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interact Propeties")
    UStaticMeshComponent* InteractiveMesh;

    virtual void BeginPlay() override;
};
