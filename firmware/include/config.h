#pragma once

#include <Arduino.h>

// Centralized configuration parameters.
namespace Config {
    namespace UART {
        constexpr uint32_t BAUD_RATE = 115200;
        constexpr size_t MAX_MESSAGE_LENGTH = 128;
    }
}