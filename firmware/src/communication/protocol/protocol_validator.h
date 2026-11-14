#pragma once

#include "protocol_types.h"

namespace Protocol {

    // Checks whether a parsed message follows the protocol rules.
    class ProtocolValidator {
    public:
        bool validate(
            const IncomingMessage& message,
            RejectionReason& reason
        ) const;
    };

}
