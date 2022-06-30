#pragma once

#include "CoreTypes.h"
#include "HorrorCoreTypes.generated.h"

#pragma Items
UENUM(BlueprintType)
enum ETypeOfItem : uint8
{
    Equipment UMETA(DisplayName = "Equipment"),
    QuestItem UMETA(DisplayName = "Quest Item"),
    Consumables UMETA(DisplayName = "Consumables")
};

USTRUCT(BlueprintType)
struct FItemData
{
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Design")
    UTexture2D* ItemThumbnail;

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
    FString ItemUniqueName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Propeties")
    TEnumAsByte<ETypeOfItem> ItemType;
};
#pragma endregion