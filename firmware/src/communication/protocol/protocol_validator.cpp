#include "protocol_validator.h"

namespace Protocol {

// Validate a parsed message against the protocol rules.
bool ProtocolValidator::validate(
    const IncomingMessage& message,
    RejectionReason& reason
) const {

    // Reset the rejection reason before validation.
    reason = RejectionReason::None;


    // Check whether all common fields are present.
    if (!message.hasVersion ||
        !message.hasType ||
        !message.hasSeqNum) {

        reason = RejectionReason::InvalidValue;
        return false;
    }


    // Check whether the protocol version is supported.
    if (message.version != 1) {
        reason = RejectionReason::UnsupportedVersion;
        return false;
    }


    // Reject unknown message types.
    if (message.type == MessageType::Unknown) {
        reason = RejectionReason::InvalidValue;
        return false;
    }


    // Validate motor commands in drive messages.
    if (message.type == MessageType::Drive) {

        // Check whether the motor array exists and is valid.
        if (!message.hasMotors ||
            !message.motorsValid ||
            message.motorCount != MOTOR_COUNT) {

            reason = RejectionReason::InvalidValue;
            return false;
        }

        // Check the allowed range of every motor command.
        for (uint8_t i = 0; i < MOTOR_COUNT; i++) {
            if (message.motors[i] < -100 ||
                message.motors[i] > 100) {

                reason = RejectionReason::InvalidValue;
                return false;
            }
        }
    }


    // The message passed all validation checks.
    return true;
}

}
