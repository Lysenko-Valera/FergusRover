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
}


void loop() {
    String message;

    // Check for a complete incoming UART message.
    if (uart.receiveMessage(message)) {

        Serial.print("Received: ");
        Serial.println(message);

        // Process the incoming JSON message.
        Protocol::HandlerResult result = protocolHandler.handle(message);

        // Print parsing result.
        Serial.print("Parsed: ");
        Serial.println(result.parsed ? "YES" : "NO");

        // Print validation result.
        Serial.print("Valid: ");
        Serial.println(result.valid ? "YES" : "NO");

        // Print command readiness.
        Serial.print("Command ready: ");
        Serial.println(result.commandReady ? "YES" : "NO");

        // Print ACK requirement.
        Serial.print("ACK required: ");
        Serial.println(result.ackRequired ? "YES" : "NO");

        Serial.println("-------------------------");
    }
}