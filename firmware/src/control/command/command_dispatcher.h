#pragma once

#include "communication/protocol/protocol_types.h"
#include "control/safety/safety_controller.h"

namespace Control {

class CommandDispatcher {
public:
    bool dispatch(const Protocol::IncomingMessage& message);

    void update();

private:
    SafetyController safetyController;

    bool handleDrive(const Protocol::IncomingMessage& message);
    bool handleStop();
    bool handleClearFault();
};

}
