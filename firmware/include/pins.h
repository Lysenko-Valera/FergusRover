#pragma once

#include <Arduino.h>

// GPIO pin assignments for ESP32.
namespace Pins {

    // UART2 connection to Raspberry Pi.
    constexpr uint8_t UART_RX = 16;
    constexpr uint8_t UART_TX = 17;

    // I2C connection to peripheral devices.
    constexpr uint8_t I2C_SDA = 21;
    constexpr uint8_t I2C_SCL = 22;
}