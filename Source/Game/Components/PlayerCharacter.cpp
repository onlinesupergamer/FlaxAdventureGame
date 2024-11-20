/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent         										**
**																			**
**	File name:		    PlayerCharacter.cpp								    **
**																			**
**	Creation Date:		11/16/2024							                **
**																			**
**	Script Author:  	Ant Man 											**
**																			**
*****************************************************************************/

#include "PlayerCharacter.h"
#include "Engine/Input/Input.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Level/Actors/Camera.h"
#include "Engine/Engine/Screen.h"
#include "Engine/Engine/Time.h"


PlayerCharacter::PlayerCharacter(const SpawnParams& params)
    : Script(params)
{
    
    _tickUpdate = true;
    _tickLateUpdate = true;

    CharacterMoveSpeed = 300.0f;
    GravityValue = -4.0f;
    bIsAiming = false;
    
}

void PlayerCharacter::OnEnable()
{
    Screen::SetCursorLock(CursorLockMode::Locked);
    Screen::SetCursorVisible(false);
}

void PlayerCharacter::OnDisable()
{
    
}

void PlayerCharacter::OnUpdate()
{
    /*
        This should be moved into its own function
    */

    if (Input::GetAction(TEXT("StartAim")))
    {
        bIsAiming = true;
        _CharacterCamera->bIsAiming = true;
        _CharacterCamera->StartAim();
    }
    else if (Input::GetAction(TEXT("StopAim"))) 
    {
        bIsAiming = false;
        _CharacterCamera->bIsAiming = false;
        _CharacterCamera->StopAim();
    }

    MoveCharacter();
    Gravity();
    

    bIsGrounded = _CharacterController->IsGrounded();
}

void PlayerCharacter::OnLateUpdate() 
{
    //Should be after the main update loop
    CameraHandler();
}

void PlayerCharacter::MoveCharacter() 
{
    if (!_CharacterController || !_CharacterCamera) 
    {
        DebugLog::Log(LogType::Error, TEXT("Character Controller Or Character Camera Is Missing"));
        return;
    }

    Vector3 MoveVector;
    
    //We have to do a type conversion because the compiler is retarded
    PlayerCamera* _Camera = static_cast<ScriptingObjectReference<PlayerCamera>>(_CharacterCamera);
    Transform CameraTransform = _Camera->GetActor()->GetTransform();
    Vector3 CamForward = CameraTransform.GetForward();
    Vector3 CamRight = CameraTransform.GetRight();
    CamRight.Y = (float)0;
    CamForward.Y = (float)0;
    CamForward.Normalize();
    CamRight.Normalize();
    Vector3 NewForwardVec = (float)PLAYER_VERTICAL_INPUT * CamForward;
    Vector3 NewRightVec = (float)PLAYER_HORIZONTAL_INPUT * CamRight;
    MoveVector = NewForwardVec + NewRightVec;

    _CharacterController->Move((MoveVector * CharacterMoveSpeed) * GetDT());

    float RotSmoothing = 20.0f;
    float RotFactor = Math::Saturate(RotSmoothing * GetDT());
    Quaternion Rot;

    if (PLAYER_HORIZONTAL_INPUT != 0 || PLAYER_VERTICAL_INPUT != 0) 
    {
        float TargetAngle = Math::Atan2(MoveVector.X, MoveVector.Z) * RadiansToDegrees;

        if (!bIsAiming) 
        {
            Rot = Quaternion::Lerp(GetActor()->GetOrientation(), Quaternion::Euler(0.0f, TargetAngle, 0.0f), RotFactor);
            GetActor()->SetOrientation(Rot);
        }
    }

    if (bIsAiming) 
    {
        Rot = Quaternion::Lerp(GetActor()->GetOrientation(), _Camera->GetActor()->GetOrientation(), RotFactor);
        Quaternion AdjustedRot = Rot.Euler((float)0, Rot.GetEuler().Y, (float)0);
        GetActor()->SetOrientation(AdjustedRot);
    }
}

void PlayerCharacter::CameraHandler()
{
    if (!_CharacterCamera)
    {
        DebugLog::Log(LogType::Error, TEXT("Main Camera Is Missing"));
        return;
    }


    PlayerCamera* _Camera = static_cast<ScriptingObjectReference<PlayerCamera>>(_CharacterCamera);
    Transform Target = GetActor()->GetPosition();
    Quaternion TargetRotation;
    xRotation = Math::Clamp(xRotation + PLAYER_ROTATION_INPUT_V, (float)-180, (float)250);
    yRotation += PLAYER_ROTATION_INPUT_H;
    TargetRotation = Quaternion::Euler(xRotation * CameraLookSpeed, yRotation * CameraLookSpeed, (float)0);
    _Camera->GetActor()->SetPosition(Target.Translation - TargetRotation * _Camera->Offset + Vector3(0, 1, 0) * _Camera->Height);
    _Camera->GetActor()->SetOrientation(TargetRotation);
}

void PlayerCharacter::Gravity() 
{
    Vector3 GravityVector(0, GravityValue, 0);
    _CharacterController->Move(GravityVector);
}

float PlayerCharacter::GetDT() 
{
    //Returns DeltaTime
    float DT = Time::GetDeltaTime();
    return DT;
}

float PlayerCharacter::LerpC(float l1, float l2, float LerpSpeed)
{
    float f = Math::Lerp(l1, l2, (1.0f / LerpSpeed) * Time::GetDeltaTime());
    return f;
}