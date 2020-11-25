#pragma once

#include "SmartMessage/MessageHandler.hpp"

class RelayCommandHandler : public MessageHandler
{
public:
    RelayCommandHandler(){
        setQos(1);
    }

protected:
    /* Message template
    {
        "relay":
        {
            "number":"1"
            "state":"ON" //OFF
            "timeout":"5000" //ms, only for enabled states
            "blockRelaysTillTimeout": //drop all commands for these relays until timeout - prevent short cuitcuit!!!
            {
                "number":"2"
                "number":"5"
            }
        }
    }
    */
    virtual void _handle() override{
        //TODO message template

    }
};