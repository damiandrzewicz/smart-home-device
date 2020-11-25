#include <string>
#include <string.h>
#include <memory>

#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "RtosUtils/RtosAllocators.hpp"
#include "SmartDevice/DeviceCore.hpp"
#include "SmartDevice/DeviceType.hpp"

#include "Pheripherial/Test.h"

#include "DomainSmartMessage/RelayCommandHandler.hpp"

//Tag used for logging
static const char* TAG = "AppMain";

//Make app_main compatible with C++
extern "C"{ void app_main(void); }

void app_main(void)
{ 
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    auto &core = SmartDevice::DeviceCore::getInstance();
    core.getDeviceInfo().deviceType = SmartDevice::DeviceType::Value::RelayDriver;

    core.getMessageManager().registerMessageHandler(std::make_shared<RelayCommandHandler>());

    core.start();

    ESP_LOGI(TAG, "Core initialized!");

    Test t;
    t.test();
    
    while(1) { vTaskDelay(1000 / portTICK_PERIOD_MS); }
}
