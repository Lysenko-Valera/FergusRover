# UART Communication Protocol — Version 1

## 1. Overview

The Raspberry Pi communicates with the ESP32 via UART (Universal Asynchronous Receiver-Transmitter).

JSON is used as the message format.

Each message is transmitted as a single line ending with a newline character (`\n`). This allows the receiver to identify where each message ends.

The ESP32 is responsible for controlling the rover's motors and ensuring safe operation.

## 2. Message Structure

Each message contains several fields:

| Field | Description |
|---|---|
| `v` | Protocol version |
| `type` | Message type |
| `seq_num` | Sequence number used to identify a message |

The `seq_num` is a sequential identifier assigned by the sender. It allows the sender and receiver to match commands with their corresponding responses.

## 3. Raspberry Pi → ESP32

The Raspberry Pi sends commands to the ESP32.

### 3.1. Drive Command

The `drive` message controls the six DC motors.

Example:

    {
        "v": 1,
        "type": "drive",
        "seq_num": 5,
        "motors": [80, 80, 75, 80, 80, 80]
    }

Fields:

- `v` — protocol version.
- `type` — message type (`drive`).
- `seq_num` — sequential number of the command.
- `motors` — an array containing the commands for all six motors.

Motor command values:

| Value | Meaning |
|---|---|
| `100` | Maximum command in the forward direction |
| `-100` | Maximum command in the reverse direction |
| `0` | Stop |

Values between -100 and 100 represent intermediate motor commands.

The array contains six elements, one for each motor.

**Note:** The exact mapping between array indices and physical motor positions (M1–M6) must be defined separately.

### 3.2. Stop Command

The `stop` message requests an immediate stop of all six motors.

Example:

    {
        "v": 1,
        "type": "stop",
        "seq_num": 6
    }

The ESP32 must stop all motors when it receives a valid stop command.

## 4. ESP32 → Raspberry Pi

The ESP32 sends responses to the Raspberry Pi.

### 4.1. Acknowledgment (ACK)

An ACK message confirms that a command has been received and accepted for execution.

Example:

    {
        "v": 1,
        "type": "ack",
        "seq_num": 5,
        "status": "accepted"
    }

Fields:

- `type` — message type (`ack`).
- `seq_num` — sequence number of the original command.
- `status` — result of command processing.

Possible status values:

- `accepted` — command passed validation and was accepted.
- `rejected` — command was rejected.

The ESP32 must use the same `seq_num` as the corresponding incoming command.

An ACK confirms command acceptance, not necessarily physical motor movement.

## 5. Safety Requirements

The ESP32 must be able to stop the motors independently of the Raspberry Pi, Backend, or Frontend.

The following safety rules apply:

1. The Raspberry Pi periodically sends drive commands while the operator holds a movement key.
2. When the operator releases the key, the Raspberry Pi sends a stop command.
3. The ESP32 monitors the time since the last valid drive command.
4. If no valid drive command is received within a configured timeout, the ESP32 must stop all motors.
5. Invalid messages and commands must never cause unintended motor movement.
6. The ESP32 must validate motor command values before executing them.

A heartbeat message must not extend the drive-command timeout.

## 6. Protocol Parameters — To Be Defined

The following parameters have not yet been finalized:

- UART baud rate.
- Drive command transmission interval.
- Drive-command timeout.
- Maximum message length.
- ACK transmission policy.
- Motor index mapping (M1–M6).

These parameters will be determined during implementation and testing.

## 7. Future Extensions

Future protocol versions may include:

- Servo steering commands.
- Sensor telemetry (MPU6050 and BME280).
- ESP32 status information.
- Battery voltage and current measurements.
- Camera and computer vision status.

These features are outside the scope of Version 1.
