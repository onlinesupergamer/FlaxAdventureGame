#include "InterfaceTest.h"
#include <Engine/Debug/DebugLog.h>

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
    DebugLog::Log(LogType::Info, TEXT("Damage Interface Method"));

}
