#include "Relay/Relay.hpp"

Relay::Relay(std::shared_ptr<RelayGpioOutputCommand> command)
    :_gpioCommand(command)
{
    _relayDelayedDisablerTask = std::make_shared<RelayDelayedDisablerTask>();
}

RelayState Relay::getState()
{
    return _state;
}

void Relay::setState(RelayState state, unsigned int timeout)
{
    _state = state;
    if(state.isOn())
    {
        _gpioCommand->on();

        if(timeout)
        {
            _relayDelayedDisablerTask->setDelay(timeout);
            _relayDelayedDisablerTask->setFunction([&](){
                _gpioCommand->off();
            });
            _relayDelayedDisablerTask->start();
        }
    }
    else if(state.isOff())
    {
        _relayDelayedDisablerTask->stop();
        _gpioCommand->off();
    }
}