#pragma once

class HorrorUtils
{
public:
    template <typename T>
    static T* GetHorrorPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};
