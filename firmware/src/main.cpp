#include <Arduino.h>

#include "communication/uart_transport.h"

// Create the UART communication object.
UartTransport uart;


void setup() {
    // Initialize USB serial for debugging.
    Serial.begin(115200);

    // Initialize UART2 for communication with Raspberry Pi.
    uart.begin();

    Serial.println("Rover started");
}


void loop() {
    String message;

    // Check whether a complete UART message has arrived
    if (uart.receiveMessage(message)) {

        Serial.print("Received: ");
        Serial.println(message);

        // Return the received message to Raspberry Pi
        uart.sendMessage(message);
    }
}