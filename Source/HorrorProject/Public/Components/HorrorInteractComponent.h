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
    void Interact();
    void Inspect();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactions")
    float TraceDistance = 1000.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactions")
    float TraceRate = 1.f;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

    UFUNCTION(BlueprintNativeEvent)
    void TraceForward();
    void TraceForward_Implementation();

private:
    AActor* FocusedActor = nullptr;
    void EndFocus();
    FTimerHandle TraceTimerHandle;
};
