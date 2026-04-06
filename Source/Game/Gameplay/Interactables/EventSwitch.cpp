#include "EventSwitch.h"

EventSwitch::EventSwitch(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void EventSwitch::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void EventSwitch::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void EventSwitch::OnUpdate()
{
    // Here you can add code that needs to be called every frame
}
