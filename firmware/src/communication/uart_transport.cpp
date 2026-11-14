#include "uart_transport.h"

#include "config.h"
#include "pins.h"


// Initialize UART with configured pins and baud rate.
void UartTransport::begin() {
    serial.begin(
        Config::UART::BAUD_RATE,
        SERIAL_8N1,
        Pins::UART_RX,
        Pins::UART_TX
    );
}


// Read incoming bytes until a complete message is received.
bool UartTransport::receiveMessage(String& message) {
    while (serial.available() > 0) {
        char incomingByte = serial.read();

        // A newline character marks the end of a message.
        if (incomingByte == '\n') {

            // Discard the entire message if the buffer overflowed.
            if (bufferOverflow) {
                bufferOverflow = false;
                receiveBuffer = "";
                continue;
            }

            // Remove carriage return if CRLF line endings are used.
            if (receiveBuffer.endsWith("\r")) {
                receiveBuffer.remove(receiveBuffer.length() - 1);
            }

            // Ignore empty messages.
            if (receiveBuffer.length() == 0) {
                continue;
            }

            // Return the completed message and clear the buffer.
            message = receiveBuffer;
            receiveBuffer = "";

            return true;
        }

        // Ignore remaining bytes of an oversized message.
        if (bufferOverflow) {
            continue;
        }

        // Store the byte if the buffer has available space.
        if (receiveBuffer.length() < Config::UART::MAX_MESSAGE_LENGTH) {
            receiveBuffer += incomingByte;
        } else {
            // Mark the message as invalid and discard its contents.
            bufferOverflow = true;
            receiveBuffer = "";
        }
    }

    // No complete message is available yet.
    return false;
}


// Send a message followed by a newline character.
void UartTransport::sendMessage(const String& message) {

    // Reject messages that exceed the configured size limit.
    if (message.length() > Config::UART::MAX_MESSAGE_LENGTH) {
        return;
    }

    serial.print(message);
    serial.write('\n');
}