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
        float z = Math::Lerp(Offset.Z, AimDistance, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float x = Math::Lerp(Offset.X, AimOffset, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float h = Math::Lerp(Offset.Y, AimHeight, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        Offset = Vector3(x, h, z);
    }
    else
    {   
        float z = Math::Lerp(Offset.Z, Distance, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float x = Math::Lerp(Offset.X, 0.0f, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        float h = Math::Lerp(Offset.Y, Height, Math::Saturate(Time::GetDeltaTime() * 10.0f));
        Offset = Vector3(x, h, z);
    }

}

void PlayerCamera::StartAim() 
{


}

void PlayerCamera::StopAim() 
{


}

