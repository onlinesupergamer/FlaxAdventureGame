/*****************************************************************************
**																			**
**																		   	**
**				   Copyright (C) 2024 - All Rights Reserved				   	**
**																			**
******************************************************************************
**																			**
**	Project:		    Advent      										**
**																			**
**	File name:		    MusicController.h								    **
**																			**
**	Creation Date:		11/21/2024							                **
**																			**
**	Script Author:  	Ant Man												**
**																			**
*****************************************************************************/

#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Audio/AudioClip.h"
#include "Engine/Audio/AudioSource.h"


API_CLASS() class GAME_API MusicController : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(MusicController);

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void SetupMusic();
    void PlayMusic();

    API_FIELD() ScriptingObjectReference<AudioClip> LevelMusic;
    API_FIELD() ScriptingObjectReference<AudioSource> Source;
    API_FIELD() float MusicVolume;
    
};
