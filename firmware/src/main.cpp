#include <Arduino.h>

#include "communication/uart_transport.h"
#include "communication/protocol/protocol_handler.h"

// Communication objects.
UartTransport uart;
Protocol::ProtocolHandler protocolHandler;

void setup() {
    // Initialize USB serial for debugging.
    Serial.begin(115200);

    // Initialize UART2 for Raspberry Pi communication.
    uart.begin();

    Serial.println("Rover started");
    Serial.println("Protocol Layer initialized");
    Serial.println("Safety Layer initialized");
}

void loop() {
    // Check safety conditions on every loop iteration.
    protocolHandler.update();

    String message;

    // Check for a complete incoming UART message.
    if (uart.receiveMessage(message)) {

        Serial.print("Received: ");
        Serial.println(message);

        // Process the incoming JSON message.
        Protocol::HandlerResult result = protocolHandler.handle(message);

        Serial.print("Parsed: ");
        Serial.println(result.parsed ? "YES" : "NO");

        Serial.print("Valid: ");
        Serial.println(result.valid ? "YES" : "NO");

        Serial.print("Command ready: ");
        Serial.println(result.commandReady ? "YES" : "NO");

        Serial.print("ACK required: ");
        Serial.println(result.ackRequired ? "YES" : "NO");

        Serial.println("-------------------------");
    }
}