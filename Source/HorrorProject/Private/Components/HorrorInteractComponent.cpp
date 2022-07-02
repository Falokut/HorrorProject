// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HorrorInteractComponent.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Player/HorrorCharacterBase.h"
#include "Items/HorrorInteractiveInterface.h"

UHorrorInteractComponent::UHorrorInteractComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UHorrorInteractComponent::Interact()
{
    if (!FocusedActor) return;

    const auto Interface = Cast<IHorrorInteractiveInterface>(FocusedActor);
    if (!Interface) return;
    Interface->Execute_Interact(FocusedActor, GetOwner());
}

void UHorrorInteractComponent::Inspect_Implementation()
{
    if (!FocusedActor) return;
    //Логика осмотра
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Parent inspect foo implementation");
}

void UHorrorInteractComponent::BeginPlay()
{
    Super::BeginPlay();
    check(GetWorld());
}

void UHorrorInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TraceForward_Implementation();
}

APlayerController* UHorrorInteractComponent::GetPlayerController() const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return nullptr;

    const auto Controller = Character->GetController<APlayerController>();
    return Controller;
}

bool UHorrorInteractComponent::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

bool UHorrorInteractComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceDistance;
    return true;
}

void UHorrorInteractComponent::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
    TraceEnd = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
}

void UHorrorInteractComponent::TraceForward_Implementation()
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (!HitResult.bBlockingHit) return;

    AActor* Interactiable = HitResult.GetActor();

    if (!Interactiable)
    {
        EndFocus();
        FocusedActor = nullptr;
        return;
    }

    if (FocusedActor != Interactiable)
    {
        if (FocusedActor) EndFocus();
        FocusedActor = Interactiable;

        IHorrorInteractiveInterface* Interface = Cast<IHorrorInteractiveInterface>(FocusedActor);
        if (Interface)
        {
            Interface->Execute_StartFocus(Interactiable);
            OnStartFocus.Broadcast();
        }
    }
}

void UHorrorInteractComponent::EndFocus()
{
    if (!FocusedActor) return;

    IHorrorInteractiveInterface* Interface = Cast<IHorrorInteractiveInterface>(FocusedActor);
    if (Interface) Interface->Execute_EndFocus(FocusedActor);
    OnEndFocus.Broadcast();
}
