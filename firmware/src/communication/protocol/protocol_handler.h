#pragma once

#include "protocol_parser.h"
#include "protocol_validator.h"
#include "control/command/command_dispatcher.h"

namespace Protocol {

struct HandlerResult {
    IncomingMessage message;

    bool parsed = false;
    bool valid = false;
    bool commandReady = false;

    bool ackRequired = false;
    bool ackReady = false;

    AckMessage ack;
};

class ProtocolHandler {
public:
    HandlerResult handle(const String& json);

    // Run periodic control and safety checks.
    void update();

private:
    ProtocolParser parser;
    ProtocolValidator validator;

    Control::CommandDispatcher dispatcher;
};

}

