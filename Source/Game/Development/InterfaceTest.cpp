#include "InterfaceTest.h"
#include <Engine/Debug/DebugLog.h>
#include <Engine/Level/Actor.h>


InterfaceTest::InterfaceTest(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void InterfaceTest::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
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
    Health -= Damage;
    DebugLog::Log(LogType::Info, String::Format(TEXT("{0}"), Health));
    
    if(Health <= 0)
    {
        GetActor()->DeleteObject();

    }
}
