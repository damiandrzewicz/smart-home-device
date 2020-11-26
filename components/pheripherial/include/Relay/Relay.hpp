#pragma once

#include <memory>

#include "Relay/RelayGpioOutputCommand.hpp"

#include "Relay/RelayState.hpp"

#include "Relay/RelayDelayedDisablerTask.hpp"

class Relay
{
public:
    Relay(std::shared_ptr<RelayGpioOutputCommand> command);

    std::shared_ptr<RelayGpioOutputCommand> getGpioCommand();
    RelayState getState();

    void setState(RelayState state, unsigned int timeout = 0);

protected:

private:
    static constexpr const char *TAG = "Relay";

    std::shared_ptr<RelayGpioOutputCommand> _gpioCommand;
    RelayState _state;

    std::shared_ptr<RelayDelayedDisablerTask> _relayDelayedDisablerTask;
};