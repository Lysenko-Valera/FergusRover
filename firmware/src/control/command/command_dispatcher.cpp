#include "command_dispatcher.h"

namespace Control {

bool CommandDispatcher::dispatch(
    const Protocol::IncomingMessage& message
) {
    switch (message.type) {

        case Protocol::MessageType::Drive:
            return handleDrive(message);

        case Protocol::MessageType::Stop:
            return handleStop();

        case Protocol::MessageType::ClearFault:
            return handleClearFault();

        default:
            Serial.println("[Dispatcher] Unknown command");
            return false;
    }
}

bool CommandDispatcher::handleDrive(
    const Protocol::IncomingMessage& message
) {
    Serial.println("[Dispatcher] DRIVE command");

    if (!safetyController.handleDrive(message)) {
        return false;
    }

    for (uint8_t i = 0; i < Protocol::MOTOR_COUNT; i++) {
        Serial.print("Motor ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(message.motors[i]);
    }

    return true;
}

bool CommandDispatcher::handleStop() {
    Serial.println("[Dispatcher] STOP command");

    return safetyController.handleStop();
}

bool CommandDispatcher::handleClearFault() {
    Serial.println("[Dispatcher] CLEAR_FAULT command");

    return safetyController.handleClearFault();
}

void CommandDispatcher::update() {
    safetyController.update();
}

}
