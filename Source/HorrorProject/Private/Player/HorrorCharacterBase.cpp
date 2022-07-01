// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/HorrorCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/HorrorCharacterMovementComponent.h"
#include "Components/HorrorInteractComponent.h"
#include "Components/HorrorInventoryComponent.h"

AHorrorCharacterBase::AHorrorCharacterBase(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UHorrorCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    InteractComponent = CreateDefaultSubobject<UHorrorInteractComponent>("InteractComponent");
    InventoryComponent = CreateDefaultSubobject<UHorrorInventoryComponent>("InventoryComponent");

    CameraComponent->SetupAttachment(GetRootComponent());
    GetMesh()->SetupAttachment(CameraComponent);

    bUseControllerRotationPitch = true;
    GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AHorrorCharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void AHorrorCharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    check(InventoryComponent);
    check(InteractComponent);
}

void AHorrorCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("StopJumping", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHorrorCharacterBase::Run);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AHorrorCharacterBase::StopRunning);

    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHorrorCharacterBase::StartCrouching);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHorrorCharacterBase::StopCrouching);

    PlayerInputComponent->BindAction("Interact", IE_Released, InteractComponent, &UHorrorInteractComponent::Interact);
    PlayerInputComponent->BindAction("Inspect", IE_Released, InteractComponent, &UHorrorInteractComponent::Interact);

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
void AHorrorCharacterBase::StartCrouching()
{
    Super::Crouch();
}
void AHorrorCharacterBase::StopCrouching()
{
    Super::UnCrouch();
}
