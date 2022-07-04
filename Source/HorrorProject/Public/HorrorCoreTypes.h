#pragma once

#include "CoreTypes.h"
#include "HorrorCoreTypes.generated.h"

#pragma region ItemsAndInventory

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Design")
    UTexture2D* ItemThumbnail = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Amount")
    bool bIsStackable = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Amount",
        meta = (ClampMin = "1", UIMin = "1", ClampMax = "999", UIMax = "999"), meta = (EditCondition = "bIsStackable"))
    int32 MaxAmount = 1;

    // Amount can't be bigger, than MaxAmount
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Amount",
        meta = (ClampMin = "1", UIMin = "1", ClampMax = "999", UIMax = "999"), meta = (EditCondition = "bIsStackable"))
    int32 Amount = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp Properties")
    FString ItemUniqueName = "Enter item name here";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp Propeties")
    FString Description = "Enter description here";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp Propeties")
    TSubclassOf<AHorrorPickupBase> ItemClass;
};

class AHorrorPickupBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewItemAddSignature, AHorrorPickupBase*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAddSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoveSignature, int32, ItemIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartFocusSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndFocusSignature);
#pragma endregion
