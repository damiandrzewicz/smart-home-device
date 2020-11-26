#pragma once

#include "SmartMessage/MessageHandler.hpp"

#include "DomainSmartMessage/RelayCommand.hpp"

#include "Relay/RelayManager.hpp"

class RelayCommandHandler : public MessageHandler
{
public:
    RelayCommandHandler(){
        setQos(1);
        getTopic().setCommand("RelayCommand");
    }

    void registerRelayManager(std::shared_ptr<RelayManager> relayManager){_relayManager = relayManager;}

protected:
    /* Message template
        {
            "relays":
            [
                { "number":1, "state":"ON", "timeout":5000 }
            ]
        }
    */
    virtual void _handle() override{
        auto relays = cJSON_GetObjectItem(getDataJsonObject(), "relays");
        if(!cJSON_IsArray(relays))
        {
            throw MessageJsonException("Object \"relays\" is not an array!");
        }

        int n = cJSON_GetArraySize(relays);
        for(int i = 0 ; i < n; i++)
        {
            RelayCommand cmd;
            auto item = cJSON_GetArrayItem(relays, i);
            if(!cJSON_IsObject(item))
            {
                char buff[100];
                sprintf(buff, "Item [%d] of object \"relays\" is not an object!", i);
                throw MessageJsonException(buff);
            }

            auto number = cJSON_GetObjectItem(item, "number");
            if(!cJSON_IsNumber(number))
            {
                throw MessageJsonException("Object \"number\" is not an number!");
            }
            cmd.number = number->valuedouble;

            auto state = cJSON_GetObjectItem(item, "state");
            if(!cJSON_IsString(state))
            {
                throw MessageJsonException("Object \"state\" is not a string!");
            }
            if(!cmd.state.set(state->valuestring))
            {
                throw MessageJsonException("Cannot map \"state\" value");
            }

            auto timeout = cJSON_GetObjectItem(item, "timeout");
            if(timeout)
            {
                if(!cJSON_IsNumber(timeout))
                {
                    throw MessageJsonException("Object \"timeout\" is not a number!");
                }
                cmd.timeout = timeout->valuedouble;
            }

            if(_relayManager) _relayManager->executeCommand(cmd);
        }
    }

private:
    std::shared_ptr<RelayManager> _relayManager;
};