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

#include "Engine/Scripting/Script.h"

API_INTERFACE() class GAME_API IInterface
{
DECLARE_SCRIPTING_TYPE_MINIMAL(IInterface);

	API_FUNCTION() virtual void Damage(float Damage) = 0;

};
