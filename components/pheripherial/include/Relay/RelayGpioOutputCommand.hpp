#pragma once

#include "GpioUtils/GpioOutputCommand.h"

#include "driver/gpio.h"

#include "esp_log.h"

class RelayGpioOutputCommand : public GpioOutputCommand
{
public:
    RelayGpioOutputCommand(int gpioNumber)
        : _gpioNumber(static_cast<gpio_num_t>(gpioNumber))
    {
        init();
    }

    virtual void on() override
    {
        gpio_set_level(_gpioNumber, 1);
        ESP_LOGD(TAG, "Set gpio=[%d] to HIGH", static_cast<int>(_gpioNumber));
    }

    virtual void off() override
    {
        gpio_set_level(_gpioNumber, 0);
        ESP_LOGD(TAG, "Set gpio=[%d] to LOW", static_cast<int>(_gpioNumber));
    }

protected:
    virtual void init() override
    {
        gpio_config_t io_conf;
        //disable interrupt
        io_conf.intr_type = static_cast<gpio_int_type_t>(GPIO_PIN_INTR_DISABLE);
        //set as output mode
        io_conf.mode = GPIO_MODE_OUTPUT;
        //bit mask of the pins that you want to set,e.g.GPIO18/19
        io_conf.pin_bit_mask = (1ULL<<_gpioNumber);
        //disable pull-down mode
        io_conf.pull_down_en = static_cast<gpio_pulldown_t>(GPIO_PULLDOWN_ENABLE);
        //disable pull-up mode
        io_conf.pull_up_en = static_cast<gpio_pullup_t>(GPIO_PULLUP_DISABLE);
        //configure GPIO with the given settings
        gpio_config(&io_conf);

        ESP_LOGD(TAG, "Initialized RelayGpioOutputCommand: gpio=[%d]", static_cast<int>(_gpioNumber));
    }

private:
    static constexpr const char *TAG = "RelayGpioOutputCommand";

    gpio_num_t _gpioNumber;
};