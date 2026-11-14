#pragma once

#include <Arduino.h>

// Handles low-level UART communication.
class UartTransport {
public:
    void begin(); // Initializes UART.

    bool receiveMessage(String& message); // Receives a complete message.

    void sendMessage(const String& message); // Sends a message.

private:
    HardwareSerial serial{2};

    String receiveBuffer;
    bool bufferOverflow = false;
};