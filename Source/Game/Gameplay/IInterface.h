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



API_INTERFACE() 

class IInterface
{
DECLARE_SCRIPTING_TYPE_NO_SPAWN(IInterface);

	API_FUNCTION() virtual void Damage(float Damage) = 0;

};
