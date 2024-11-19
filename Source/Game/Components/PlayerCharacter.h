/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent         										**
**																			**
**	File name:		    PlayerCharacter.h								    **
**																			**
**	Creation Date:		11/16/2024							                **
**																			**
**	Script Author:  	Ant Man												**
**																			**
*****************************************************************************/

#pragma once

#include "Engine/Scripting/Script.h"
#include <Engine/Scripting/ScriptingObjectReference.h>
#include <Engine/Level/Actor.h>
#include "Engine/Physics/Colliders/CharacterController.h"
#include "PlayerCamera.h"



#define PLAYER_HORIZONTAL_INPUT Input::GetAxisRaw(TEXT("Horizontal"))
#define PLAYER_VERTICAL_INPUT Input::GetAxisRaw(TEXT("Vertical"))
#define PLAYER_ROTATION_INPUT_H Input::GetAxisRaw(TEXT("Mouse X"))
#define PLAYER_ROTATION_INPUT_V Input::GetAxisRaw(TEXT("Mouse Y"))
#define PLAYER_AIM_START Input::GetAction(TEXT("StartAim"));
#define PLAYER_AIM_STOP Input::GetAction(TEXT("StopAim"));



API_CLASS() class GAME_API PlayerCharacter : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerCharacter);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void OnLateUpdate() override;

public:

    API_FIELD() ScriptingObjectReference<PlayerCamera> _CharacterCamera;
    API_FIELD() ScriptingObjectReference<CharacterController> _CharacterController;
    API_FIELD() float CharacterMoveSpeed;
    API_FIELD() float GravityValue;
    API_FIELD() bool bIsGrounded;
    API_FIELD() float timer = 0.0f;
    API_FIELD() bool bIsAiming;


private:

    void MoveCharacter();
    void CameraHandler();
    void Gravity();
    float GetDT();              //Should be set in a Utility file
    float LerpC(float l1, float l2, float LerpSpeed);

    float yRotation = 0.0f;
    float xRotation = 0.0f;
    float CameraLookSpeed = 0.2f;
    


};
