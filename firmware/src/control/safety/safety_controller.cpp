#include "safety_controller.h"

namespace Control {

void SafetyController::update() {
    if (currentState == SafetyState::Driving) {
        if (millis() - lastDriveTime >= DRIVE_TIMEOUT_MS) {
            currentState = SafetyState::FailStopped;

            Serial.println("[Safety] DRIVE TIMEOUT");
            Serial.println("[Safety] FAIL_STOPPED");
        }
    }
}

bool SafetyController::handleDrive(
    const Protocol::IncomingMessage& message
) {
    if (currentState == SafetyState::FailStopped) {
        Serial.println("[Safety] DRIVE rejected: fault active");
        return false;
    }

    // Check whether at least one motor is commanded to move.
    bool hasMovement = false;

    for (uint8_t i = 0; i < Protocol::MOTOR_COUNT; i++) {
        if (message.motors[i] != 0) {
            hasMovement = true;
            break;
        }
    }

    // A zero command is treated as a stop.
    if (!hasMovement) {
        return handleStop();
    }

    lastDriveTime = millis();
    currentState = SafetyState::Driving;

    Serial.println("[Safety] State: DRIVING");

    return true;
}

bool SafetyController::handleStop() {
    currentState = SafetyState::Stopped;
    lastDriveTime = 0;

    Serial.println("[Safety] State: STOPPED");

    return true;
}

bool SafetyController::handleClearFault() {
    if (currentState != SafetyState::FailStopped) {
        Serial.println("[Safety] CLEAR_FAULT rejected: invalid state");
        return false;
    }

    currentState = SafetyState::Stopped;
    lastDriveTime = 0;

    Serial.println("[Safety] Fault cleared");
    Serial.println("[Safety] State: STOPPED");

    return true;
}

SafetyState SafetyController::getState() const {
    return currentState;
}

}
