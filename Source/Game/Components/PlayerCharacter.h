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
#include "Engine/Core/Types/LayersMask.h"
#include "../Gameplay/IInterface.h"
#include "PlayerCamera.h"



#define PLAYER_HORIZONTAL_INPUT Input::GetAxisRaw(TEXT("Horizontal"))
#define PLAYER_VERTICAL_INPUT Input::GetAxisRaw(TEXT("Vertical"))
#define PLAYER_ROTATION_INPUT_H Input::GetAxis(TEXT("LookRight"))
#define PLAYER_ROTATION_INPUT_V Input::GetAxis(TEXT("LookUp"))
#define PLAYER_AIM_START Input::GetAction(TEXT("StartAim"));
#define PLAYER_AIM_STOP Input::GetAction(TEXT("StopAim"));
#define PLAYER_FIRE_START Input::GetAction(TEXT("StartFire"));
#define PLAYER_FIRE_STOP Input::GetAction(TEXT("StopFire"));
#define PLAYER_JUMP Input::GetAction(TEXT("Jump"));



API_CLASS() class GAME_API PlayerCharacter : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerCharacter);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnLateUpdate() override;

public:

    API_FIELD() ScriptingObjectReference<PlayerCamera> m_CharacterCamera = nullptr;
    API_FIELD() ScriptingObjectReference<CharacterController> m_CharacterController = nullptr;
    API_FIELD() float CharacterMoveSpeed = 400;
    API_FIELD() float GravityValue = -4;
    API_FIELD() bool bIsAiming;
    API_FIELD() float WeaponDistance = 5000;
    API_FIELD() float SwordDistance = 150;
    API_FIELD() float JumpForce = 5.0f;
    API_FIELD() LayersMask RayLayers;


    Vector3 MovementVector = Vector3(0.0f);
    float JumpVelocity = 0.0f;

private:

    void MoveCharacter();
    void CameraHandler();
    void Gravity();
    void FireWeapon();
    void SwordAttack();
    void AimCheck();
    void AttackCheck();
    float LerpC(float l1, float l2, float LerpSpeed);

    float yRotation = 0.0f;
    float xRotation = 0.0f;
    float CameraLookSpeed = 0.2f;
    
};
