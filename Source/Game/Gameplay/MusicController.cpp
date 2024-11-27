/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent      										**
**																			**
**	File name:		    MusicController.cpp								    **
**																			**
**	Creation Date:		11/21/2024							                **
**																			**
**	Script Author:  	Ant Man												**
**																			**
*****************************************************************************/

#include "MusicController.h"
#include "Engine/Core/Random.h"

MusicController::MusicController(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
    MusicVolume = 0.15f;
    
}

void MusicController::OnEnable()
{
    if (Source) 
    {
        SetupMusic();
        PlayMusic();  
    }
}

void MusicController::OnDisable()
{
    
}

void MusicController::OnUpdate()
{
    
}

void MusicController::SetupMusic() 
{
    Source->SetVolume(MusicVolume);
    Source->Clip = LevelMusic;
}

void MusicController::PlayMusic() 
{
    if (Source->Clip) 
    {
        Source->Play();
    }
}


