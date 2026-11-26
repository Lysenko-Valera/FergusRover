#pragma once

#include <Arduino.h>
#include "communication/protocol/protocol_types.h"

namespace Control {

enum class SafetyState {
    Stopped,
    Driving,
    FailStopped
};

class SafetyController {
public:
    void update();

    bool handleDrive(const Protocol::IncomingMessage& message);
    bool handleStop();
    bool handleClearFault();

    SafetyState getState() const;

private:
    SafetyState currentState = SafetyState::Stopped;

    uint32_t lastDriveTime = 0;

    static constexpr uint32_t DRIVE_TIMEOUT_MS = 250;
};

}
