#include "protocol_parser.h"

#include <ArduinoJson.h>
#include <cstring>

namespace Protocol {

// Parse a JSON string into an IncomingMessage structure.
bool ProtocolParser::parse(const String& json, IncomingMessage& message) {

    // Reset the output structure before parsing.
    message = IncomingMessage{};

    JsonDocument doc;

    // Deserialize the JSON string.
    DeserializationError error = deserializeJson(doc, json);

    // Reject malformed JSON.
    if (error) {
        return false;
    }

    // Only JSON objects are supported.
    if (!doc.is<JsonObject>()) {
        return false;
    }

    JsonObjectConst object = doc.as<JsonObjectConst>();


    // Parse protocol version.
    JsonVariantConst versionField = object["v"];

    if (versionField.is<uint32_t>()) {
        message.version = versionField.as<uint32_t>();
        message.hasVersion = true;
    }


    // Parse message type.
    JsonVariantConst typeField = object["type"];

    if (typeField.is<const char*>()) {
        const char* type = typeField.as<const char*>();

        message.hasType = true;

        if (strcmp(type, "drive") == 0) {
            message.type = MessageType::Drive;
        }
        else if (strcmp(type, "stop") == 0) {
            message.type = MessageType::Stop;
        }
        else if (strcmp(type, "clear_fault") == 0) {
            message.type = MessageType::ClearFault;
        }
        else {
            message.type = MessageType::Unknown;
        }
    }


    // Parse sequence number.
    JsonVariantConst seqField = object["seq_num"];

    if (seqField.is<uint32_t>()) {
        message.seqNum = seqField.as<uint32_t>();
        message.hasSeqNum = true;
    }


    // Parse motor commands.
    JsonVariantConst motorsField = object["motors"];

    if (!motorsField.isUnbound()) {
        message.hasMotors = true;

        if (motorsField.is<JsonArrayConst>()) {

            JsonArrayConst motors = motorsField.as<JsonArrayConst>();

            message.motorCount = static_cast<uint8_t>(motors.size());

            bool allValuesValid = true;

            // Read only as many elements as the structure can hold.
            for (size_t i = 0; i < motors.size() && i < MOTOR_COUNT; i++) {

                JsonVariantConst motorValue = motors[i];

                if (!motorValue.is<int32_t>()) {
                    allValuesValid = false;
                    continue;
                }

                message.motors[i] = motorValue.as<int32_t>();
            }

            // The array must contain exactly six valid integers.
            message.motorsValid =
                motors.size() == MOTOR_COUNT && allValuesValid;
        }
    }

    // JSON was parsed successfully.
    return true;
}

}