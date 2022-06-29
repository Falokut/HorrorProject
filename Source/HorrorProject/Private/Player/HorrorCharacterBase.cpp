// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/HorrorCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/HorrorCharacterMovementComponent.h"
#include "Components/HorrorInteractComponent.h"

AHorrorCharacterBase::AHorrorCharacterBase(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UHorrorCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    InteractComponent = CreateDefaultSubobject<UHorrorInteractComponent>("InteractComponent");

    CameraComponent->SetupAttachment(GetRootComponent());
    GetMesh()->SetupAttachment(CameraComponent);

    bUseControllerRotationPitch = true;
}

void AHorrorCharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void AHorrorCharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHorrorCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("StopJumping", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHorrorCharacterBase::Run);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AHorrorCharacterBase::StopRunning);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &UHorrorInteractComponent::Interact);

    PlayerInputComponent->BindAxis("MoveForward", this, &AHorrorCharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AHorrorCharacterBase::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void AHorrorCharacterBase::MoveForward(float Value)
{
    if (!Controller) return;
    if (Value == 0.0f) return;

    bIsMovingForward = true;
    AddMovementInput(GetActorForwardVector(), Value);
}

void AHorrorCharacterBase::MoveRight(float Value)
{
    if (!Controller) return;
    if (Value == 0.0f) return;

    AddMovementInput(GetActorRightVector(), Value);
}

void AHorrorCharacterBase::Run()
{
    bIsRunning = true;
}

void AHorrorCharacterBase::StopRunning()
{
    bIsRunning = false;
}
