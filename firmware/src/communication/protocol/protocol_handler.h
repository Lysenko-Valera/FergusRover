#pragma once

#include "protocol_parser.h"
#include "protocol_validator.h"

namespace Protocol {

// Result of processing one incoming JSON message.
struct HandlerResult {
    IncomingMessage message;

    bool parsed = false;
    bool valid = false;
    bool commandReady = false;

    // ACK is required for stop and clear_fault.
    bool ackRequired = false;

    // True only when the ACK result is already known.
    bool ackReady = false;

    AckMessage ack;
};

class ProtocolHandler {
public:
    HandlerResult handle(const String& json);

private:
    ProtocolParser parser;
    ProtocolValidator validator;
};

}
