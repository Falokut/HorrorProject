// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorrorCharacterBase.generated.h"

class UCameraComponent;
class UHorrorInteractComponent;
class UHorrorInventoryComponent;

UCLASS()
class HORRORPROJECT_API AHorrorCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    AHorrorCharacterBase(const FObjectInitializer& ObjInit);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UHorrorInteractComponent* InteractComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UHorrorInventoryComponent* InventoryComponent;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    bool IsRunning() const { return bIsRunning && !GetVelocity().IsZero() && bIsMovingForward; }

private:
    bool bIsRunning = false;
    bool bIsMovingForward = false;

    void MoveForward(float Value);
    void MoveRight(float Value);

    void Run();
    void StopRunning();
    void StartCrouching();
    void StopCrouching();
};
