#pragma once

#include <functional>

#include "RtosUtils/DelayedSingleShootTask.hpp"


class RelayDelayedDisablerTask : public DelayedSingleShootTask
{
public:
    RelayDelayedDisablerTask() 
        : DelayedSingleShootTask(TAG, 1, 0, 3*1024){}

    void setFunction(std::function<void()> fun){
        _func = fun;
    }

protected:
    virtual void task() override{
        if(!_func) return;
        _func();
    }

private:
    static constexpr const char *TAG = "RelayDelayedDisablerTask";

    std::function<void()> _func = nullptr;
};