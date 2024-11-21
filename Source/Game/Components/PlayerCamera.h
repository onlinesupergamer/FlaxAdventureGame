/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent         										**
**																			**
**	File name:		    PlayerCamera.h								        **
**																			**
**	Creation Date:		11/19/2024							                **
**																			**
**	Script Author:  	Ant Man 											**
**																			**
*****************************************************************************/

#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Level/Actor.h"

API_CLASS() class GAME_API PlayerCamera : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerCamera);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

public:
    API_FIELD() float Height = -75;
    API_FIELD() float Distance = 400;
    API_FIELD() float AimHeight = -50;
    API_FIELD() float AimDistance = 200;
    API_FIELD() float AimOffset = -125;

    Vector3 Offset;
    bool bIsAiming;
    void StartAim();
    void StopAim();


    API_FIELD() ScriptingObjectReference<Camera> _CharacterCamera;

};
