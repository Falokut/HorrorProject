#pragma once

#include "CoreTypes.h"
#include "HorrorCoreTypes.generated.h"

#pragma region ItemsAndInventory

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Design")
    UTexture2D* ItemThumbnail = nullptr;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Amount")
    bool bIsStackable = false;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Amount", meta = (ClampMin = "1", UIMin = "1", ClampMax = "999", UIMax = "999"),
        meta = (EditCondition = "bIsStackable"))
    int32 MaxAmount = 1;

    // Amount can't be bigger, than MaxAmount
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Amount", meta = (ClampMin = "1", UIMin = "1", ClampMax = "999", UIMax = "999"),
        meta = (EditCondition = "bIsStackable"))
    int32 Amount = 1;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "PickUp Properties")
    FString ItemUniqueName = "Enter item name here";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Propeties")
    FString Description = "Enter description here";
};

class AHorrorPickupBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewItemAddSignature, AHorrorPickupBase*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAddSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoveSignature, int32, ItemIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartFocusSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndFocusSignature);
#pragma endregion
