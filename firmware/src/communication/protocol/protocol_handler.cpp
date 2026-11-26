#include "protocol_handler.h"

namespace Protocol {

HandlerResult ProtocolHandler::handle(const String& json) {
    HandlerResult result;

    // Step 1: Parse incoming JSON.
    result.parsed = parser.parse(json, result.message);

    if (!result.parsed) {
        return result;
    }

    // Step 2: Determine whether an ACK is required.
    result.ackRequired =
        result.message.type == MessageType::Stop ||
        result.message.type == MessageType::ClearFault;

    // Step 3: Validate the incoming message.
    RejectionReason reason = RejectionReason::None;

    result.valid = validator.validate(result.message, reason);

    if (!result.valid) {
        if (result.ackRequired && result.message.hasSeqNum) {
            result.ack.version = 1;
            result.ack.seqNum = result.message.seqNum;
            result.ack.status = AckStatus::Rejected;
            result.ack.reason = reason;

            result.ackReady = true;
        }

        return result;
    }

    // Step 4: Dispatch the validated command.
    result.commandReady = dispatcher.dispatch(result.message);

    // Step 5: Build ACK after command processing.
    if (result.ackRequired && result.message.hasSeqNum) {
        result.ack.version = 1;
        result.ack.seqNum = result.message.seqNum;

        if (result.commandReady) {
            result.ack.status = AckStatus::Accepted;
            result.ack.reason = RejectionReason::None;
        } else {
            result.ack.status = AckStatus::Rejected;
            result.ack.reason = RejectionReason::InvalidState;
        }

        result.ackReady = true;
    }

    return result;
}

void ProtocolHandler::update() {
    // Update the Safety Layer.
    dispatcher.update();
}

}
