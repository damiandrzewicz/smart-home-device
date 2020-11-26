#pragma once

#include "string.h"

class RelayState
{   
public:
    enum class Value{
        On,
        Off
    };

    RelayState(){};
    RelayState(Value value){_value = value;}

    void operator=(Value value){
        _value = value;
    }

    bool isOn(){
        return _value == Value::On;
    }

    bool isOff(){
        return _value == Value::Off;
    }

    bool set(const char *str){
        if(!strcasecmp(str, "on")) 
        {
            _value = Value::On;
            return true;
        }
        else if(!strcasecmp(str, "off"))
        {
            _value = Value::Off;
            return true;
        }
        return false;
    }

    const char *toString(){
        if(isOn()){return "On";}
        else {return "Off";}
    }

private:
    Value _value = Value::Off;
};