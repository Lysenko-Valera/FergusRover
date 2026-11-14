#include "protocol_handler.h"

namespace Protocol {

HandlerResult ProtocolHandler::handle(const String& json) {
    HandlerResult result;

    // Step 1: Parse incoming JSON.
    result.parsed = parser.parse(json, result.message);

    if (!result.parsed) {
        return result;
    }

    // Step 2: Determine whether this message requires an ACK.
    result.ackRequired =
        result.message.type == MessageType::Stop ||
        result.message.type == MessageType::ClearFault;

    // Step 3: Validate the parsed message.
    RejectionReason reason = RejectionReason::None;

    result.valid = validator.validate(result.message, reason);

    if (!result.valid) {
        // Send a rejection ACK only if the sequence number is available.
        if (result.ackRequired && result.message.hasSeqNum) {
            result.ack.version = 1;
            result.ack.seqNum = result.message.seqNum;
            result.ack.status = AckStatus::Rejected;
            result.ack.reason = reason;

            result.ackReady = true;
        }

        return result;
    }

    // Step 4: Mark the command as ready for the next layer.
    result.commandReady = true;

    // A final ACK for stop/clear_fault will be prepared
    // after the Control Layer processes the command.

    return result;
}

}
