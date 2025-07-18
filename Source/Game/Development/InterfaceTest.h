#pragma once

#include "Engine/Scripting/Script.h"
#include "../Gameplay/IInterface.h"

API_CLASS() class GAME_API InterfaceTest : public Script, public IInterface
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(InterfaceTest);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;


    void Damage(float Damage) override;
};
