/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent         										**
**																			**
**	File name:		    PlayerCamera.cpp								    **
**																			**
**	Creation Date:		11/19/2024							                **
**																			**
**	Script Author:  	Ant Man 											**
**																			**
*****************************************************************************/

#include "PlayerCamera.h"
#include "Engine/Debug/DebugLog.h"
#include "Engine/Engine/Time.h"

PlayerCamera::PlayerCamera(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
    Offset = Vector3(0, 0, 230.0f);
    Height = 65.0f;
    bIsAiming = false;
}

void PlayerCamera::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void PlayerCamera::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void PlayerCamera::OnUpdate()
{
    if (bIsAiming) 
    {
        float z = Math::Lerp(Offset.Z, 170.0f, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float x = Math::Lerp(Offset.X, -50.0f, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float h = Math::Lerp(Height, 55.0f, Math::Saturate(Time::GetDeltaTime()) * 10.0f);
        Offset = Vector3(x, 0, z);
        Height = h;
    }
    else
    {   
        float z = Math::Lerp(Offset.Z, 230.0f, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float x = Math::Lerp(Offset.X, 0.0f, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float h = Math::Lerp(Height, 65.0f, Math::Saturate(Time::GetDeltaTime()) * 10.0f);
        Offset = Vector3(x, 0, z);
        Height = h;
    }

}

void PlayerCamera::StartAim() 
{
    DebugLog::Log(LogType::Info, TEXT("Starting Aim"));

}

void PlayerCamera::StopAim() 
{
    DebugLog::Log(LogType::Info, TEXT("Stopping Aim"));

}
