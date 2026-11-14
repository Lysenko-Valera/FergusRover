#pragma once

#include <Arduino.h>

#include "protocol_types.h"

namespace Protocol {

    // Converts JSON strings into protocol message structures.
    class ProtocolParser {
    public:
        bool parse(const String& json, IncomingMessage& message);
    };

}
