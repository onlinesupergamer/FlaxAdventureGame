/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2000 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    <project name>										**
**																			**
**	File name:		    <filename>.h/.cpp								    **
**																			**
**	Creation Date:		00/00/00							                **
**																			**
**	Script Author:  	<Name>												**
**																			**
*****************************************************************************/

#pragma once

#include "../Gameplay/IInterface.h"
#include "Engine/Scripting/Script.h"

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
