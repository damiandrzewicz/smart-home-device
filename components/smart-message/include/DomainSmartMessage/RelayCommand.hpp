#pragma once

#include "Relay/RelayState.hpp"

#include <string>

struct RelayCommand
{
    int number = -1;
    RelayState state;
    unsigned int timeout = 0;

    std::string toString(){
        char buff[100];
        sprintf(buff, "RelayCommand: number=[%d], state:[%s], timeout=[%d]",
            number,
            state.toString(),
            timeout);

        return buff;
    }
};