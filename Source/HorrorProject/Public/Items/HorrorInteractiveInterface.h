// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorInteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHorrorInteractiveInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class HORRORPROJECT_API IHorrorInteractiveInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* Caller);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void StartFocus();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void EndFocus();
};
