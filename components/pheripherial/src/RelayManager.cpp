#include "Relay/RelayManager.hpp"

#include "esp_log.h"

RelayManager::RelayManager()
{
    _xMutex = xSemaphoreCreateMutex();
    if(_xMutex == NULL)
    {
        ESP_LOGE(TAG, "Cannot create mutex, ho heap left...");
    }
}

void RelayManager::registerRelay(std::shared_ptr<RelayGpioOutputCommand> gpioCommand)
{
    
    SemaphoreGuard lock(_xMutex);
    int number = _relays.size();
    auto relay = std::make_shared<Relay>(gpioCommand);
    _relays.insert(std::make_pair(number, relay));
    ESP_LOGD(TAG, "Registered relay number: [%d]", number);
}

void RelayManager::command(std::list<RelayCommand> relayCommands)
{
    

    for(auto cmd : relayCommands)
    {
        ESP_LOGD(TAG, "Executing command: [%s]", cmd.toString().c_str());
        
        auto relayItem = _relays.find(cmd.number);
        if(relayItem == _relays.end()) return;

        auto relay = relayItem->second;
        
        relay->setState(cmd.state, cmd.timeout);
    }


}