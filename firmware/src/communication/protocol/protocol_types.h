#pragma once

#include <stdint.h>

namespace Protocol {

    // Number of DC motors controlled by the rover.
    constexpr uint8_t MOTOR_COUNT = 6;


    // Types of commands received from Raspberry Pi.
    enum class MessageType {
        Unknown,
        Drive,
        Stop,
        ClearFault
    };


    // Possible command processing results.
    enum class AckStatus {
        Accepted,
        Rejected
    };


    // Reasons why a command can be rejected.
    enum class RejectionReason {
        None,
        UnsupportedVersion,
        InvalidValue,
        InvalidState,
        StaleSequence
    };


    // Data extracted from an incoming JSON message.
    struct IncomingMessage {
        uint32_t version = 0;
        MessageType type = MessageType::Unknown;
        uint32_t seqNum = 0;

        int32_t motors[MOTOR_COUNT] = {};
        uint8_t motorCount = 0;

        bool hasVersion = false;
        bool hasType = false;
        bool hasSeqNum = false;
        bool hasMotors = false;
        bool motorsValid = false;
    };


    // Acknowledgment sent from ESP32 to Raspberry Pi.
    struct AckMessage {
        uint32_t version = 1;
        uint32_t seqNum = 0;

        AckStatus status = AckStatus::Rejected;
        RejectionReason reason = RejectionReason::None;
    };
}
