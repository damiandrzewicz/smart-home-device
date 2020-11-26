#pragma once

#include <map>
#include <memory>

#include "RtosUtils/SemaphoreGuard.hpp"

#include "RtosUtils/RoutineTask.hpp"

#include "Relay/Relay.hpp"
#include "Relay/RelayGpioOutputCommand.hpp"

#include "DomainSmartMessage/RelayCommand.hpp"

class RelayManager
{
public:
    RelayManager();

    void registerRelay(std::shared_ptr<RelayGpioOutputCommand> gpioCommand);

    void executeCommand(RelayCommand relayCommand);

private:
    static constexpr const char *TAG = "RelayManager";

    std::map<int, std::shared_ptr<Relay>> _relays;
    SemaphoreHandle_t _xMutex;;
};