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
#include "Engine/Physics/Physics.h"
#include "Engine/Debug/DebugDraw.h"



PlayerCharacter::PlayerCharacter(const SpawnParams& params)
    : Script(params)
{
    _tickUpdate = true;
    _tickFixedUpdate = true;
    _tickLateUpdate = true;

    
}

void PlayerCharacter::OnEnable()
{
    Screen::SetCursorLock(CursorLockMode::Locked);
    Screen::SetCursorVisible(false);
    CrosshairImage->SetIsActive(false);


    if(Playermodel)
    {
        const String m_Speed = TEXT("Speed");
        const String m_Falling = TEXT("bIsFalling");
        
        AnimSpeedParameter = Playermodel.As<AnimatedModel>()->GetParameter(m_Speed);
        AnimFallingParameter = Playermodel.As<AnimatedModel>()->GetParameter(m_Falling);
    }

}

void PlayerCharacter::OnDisable()
{
    
}

void PlayerCharacter::OnUpdate()
{
    AimCheck();
    MoveCharacter();
    AttackCheck();
    PlayerAnimations();
    
}

void PlayerCharacter::OnFixedUpdate()
{

}

void PlayerCharacter::OnLateUpdate() 
{
    CameraHandler();
}

void PlayerCharacter::MoveCharacter() 
{
    if (!m_CharacterController || !m_PlayerCamera) 
    {
        DebugLog::Log(LogType::Error, TEXT("Character Controller Or Character Camera Is Missing"));
        return;
    }


    Transform CameraTransform = m_PlayerCamera->GetActor()->GetTransform();
    Vector3 CamForward = CameraTransform.GetForward();
    Vector3 CamRight = CameraTransform.GetRight();
    CamRight.Y = 0;
    CamForward.Y = 0;
    CamForward.Normalize();
    CamRight.Normalize();
    Vector3 NewForwardVec = (float)PLAYER_VERTICAL_INPUT * CamForward;
    Vector3 NewRightVec = (float)PLAYER_HORIZONTAL_INPUT * CamRight;
    MovementVector = NewForwardVec + NewRightVec;

    Gravity();

    MovementVector.Y = JumpVelocity;
    m_CharacterController->Move((MovementVector * CharacterMoveSpeed) * Time::GetDeltaTime());

    float RotSmoothing = 20.0f;
    float RotFactor = Math::Saturate(RotSmoothing * Time::GetDeltaTime());
    Quaternion Rot;

    if (PLAYER_HORIZONTAL_INPUT != 0 || PLAYER_VERTICAL_INPUT != 0) 
    {
        float TargetAngle = Math::Atan2(MovementVector.X, MovementVector.Z) * RadiansToDegrees;

        if (!bIsAiming) 
        {
            Rot = Quaternion::Lerp(GetActor()->GetOrientation(), Quaternion::Euler(0.0f, TargetAngle, 0.0f), RotFactor);
            GetActor()->SetOrientation(Rot);
        }
    }

    if (bIsAiming) 
    {
        Rot = Quaternion::Lerp(GetActor()->GetOrientation(), m_PlayerCamera->GetActor()->GetOrientation(), RotFactor);
        Quaternion AdjustedRot = Rot.Euler(0, Rot.GetEuler().Y, 0);
        GetActor()->SetOrientation(AdjustedRot);
    }
}

void PlayerCharacter::CameraHandler()
{
    /*
      ////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////

        This should probably be placed into PlayerCamera.cpp, since this 
        is directly camera related

      ////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
    */


    if (!m_PlayerCamera)
    {
        DebugLog::Log(LogType::Error, TEXT("Main Camera Is Missing"));
        return;
    }

    float PlayerVerticalOffset = 30.0f;
    Transform Target = GetActor()->GetPosition();
    Target.Translation.Y = Target.Translation.Y + PlayerVerticalOffset;
    Quaternion TargetRotation;
    xRotation = Math::Clamp(xRotation + PLAYER_ROTATION_INPUT_V, -180.0f, 250.0f);
    yRotation += PLAYER_ROTATION_INPUT_H;
    TargetRotation = Quaternion::Euler(xRotation * (CameraLookSpeed * 1.0f), yRotation * (CameraLookSpeed * 1.0f), 0);
    m_PlayerCamera->GetActor()->SetPosition(Target.Translation - TargetRotation * m_PlayerCamera->Offset + Vector3(0, 1, 0));
    m_PlayerCamera->GetActor()->SetOrientation(TargetRotation);
}

void PlayerCharacter::Gravity() 
{
    if(m_CharacterController->IsGrounded())
    {
        JumpVelocity = -0.75f;

        if(Input::GetAction(TEXT("Jump")))
        {
            JumpVelocity = JumpForce;
        }
    }

    else
    {
        JumpVelocity -= GravityValue * Time::GetDeltaTime();
        JumpVelocity = Math::Clamp(JumpVelocity, -3.5f, 3.5f);
        //Clamping the velocity so the player can't fall at mach jesus
    }
}

void PlayerCharacter::AimCheck() 
{
    if (Input::GetAction(TEXT("StartAim")))
    {
        bIsAiming = true;
        m_PlayerCamera->bIsAiming = true;
        CrosshairImage->SetIsActive(true);
        m_PlayerCamera->StartAim();
    }

    else if (Input::GetAction(TEXT("StopAim")))
    {
        bIsAiming = false;
        m_PlayerCamera->bIsAiming = false;
        CrosshairImage->SetIsActive(false);
        m_PlayerCamera->StopAim();
    }

}

void PlayerCharacter::AttackCheck() 
{
    if (bIsAiming && Input::GetAction(TEXT("StartFire")))
    {
        FireWeapon();
    }
    
    if (!bIsAiming && Input::GetAction(TEXT("StartFire")))
    {
        SwordAttack();
    }
}


void PlayerCharacter::FireWeapon() 
{ 
    DebugLog::Log(LogType::Info, TEXT("Fire Gun"));
    RayCastHit Hit;
    //Using a spherecast to create depth since using a normal raycast was too precise and was annoying to aim

    if (Physics::SphereCast(m_PlayerCamera->GetActor()->GetPosition(), 18.0f, m_PlayerCamera->GetActor()->GetDirection(), Hit, WeaponDistance, RayLayers))
    {
        DEBUG_DRAW_SPHERE(BoundingSphere(Hit.Point, 18), Color::AliceBlue, 10.0f, true);

        if(Hit.Collider)
        {
            auto scripts = Hit.Collider->GetParent()->Scripts;
            for(Script* script : scripts)
            {
                if(auto* interface = dynamic_cast<IInterface*>(script))
                {
                    interface->Damage(15.0f);
                    break;   
                }
            }
        }
    }

    DEBUG_DRAW_SPHERE(BoundingSphere(m_PlayerCamera->GetActor()->GetPosition(), 18), Color::Blue, 10.0f, true);
}

void PlayerCharacter::SwordAttack() 
{
    //This is a bit repetitive with the above, but still slightly different

    DebugLog::Log(LogType::Info, TEXT("Attack With Sword"));
    RayCastHit Hit;
    float AttackOffset = 100.0f;
    float HitSize = 80.0f;
    Vector3 Position = GetActor()->GetPosition() + GetActor()->GetDirection() * AttackOffset;
    if (Physics::SphereCast(Position, HitSize, GetActor()->GetDirection(), Hit, SwordDistance, RayLayers))
    {
        if (Hit.Collider)
        {
            DebugLog::Log(LogType::Info, TEXT("Hit"));

            auto scripts = Hit.Collider->GetParent()->Scripts;
            for (Script* script : scripts)
            {
                if (auto* interface = dynamic_cast<IInterface*>(script))
                {
                    interface->Damage(10.0f);
                    break;
                }
            }
        }
    }
    DEBUG_DRAW_SPHERE(BoundingSphere(Position, HitSize), Color::Blue, 10.0f, true);

    //Update these to check for ALL entities that have been hit
}

void PlayerCharacter::PlayerAnimations()
{
    float Speed = m_CharacterController->GetVelocity().Length();
    float n = Speed / CharacterMoveSpeed;
    AnimSpeedParameter->Value = n;
    AnimFallingParameter->Value = !m_CharacterController->IsGrounded();
    //This is a simple implementation to get things working
}


float PlayerCharacter::LerpC(float l1, float l2, float LerpSpeed)
{
    float f = Math::Lerp(l1, l2, (1.0f / LerpSpeed) * Time::GetDeltaTime());
    return f;
}