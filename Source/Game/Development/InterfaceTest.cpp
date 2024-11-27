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

#include "InterfaceTest.h"
#include "Engine/Debug/DebugLog.h"

InterfaceTest::InterfaceTest(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void InterfaceTest::OnEnable()
{
    IInterface* i;
    ScriptingObject* sc = this;
    /*
        The issue is that the ACTOR is not the same thing as a SCRIPTINGOBJECT which is 
        what the Interface needs, that's why its not working, I THINK


        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////

    
    */
    i = ToInterface<IInterface>(sc);

    if (i) 
    {
        //DebugLog::Log(LogType::Info, TEXT("mmmmmmmmmmmmmmmmmmmmmmmm"));

    }

}

void InterfaceTest::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void InterfaceTest::OnUpdate()
{
    // Here you can add code that needs to be called every frame
}

void InterfaceTest::Damage(float Damage) 
{
    DebugLog::Log(LogType::Info, TEXT("true"));

}
