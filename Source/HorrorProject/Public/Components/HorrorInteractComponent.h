// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorCoreTypes.h"
#include "HorrorInteractComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROJECT_API UHorrorInteractComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHorrorInteractComponent();
    void Interact();
    UFUNCTION(BlueprintNativeEvent)
    void Inspect();
    void Inspect_Implementation();
    UPROPERTY(BlueprintAssignable, Category = "Interact Delegates")
    FOnStartFocusSignature OnStartFocus;

    UPROPERTY(BlueprintAssignable, Category = "Interact Delegates")
    FOnEndFocusSignature OnEndFocus;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactions")
    float TraceDistance = 1000.f;

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
};
