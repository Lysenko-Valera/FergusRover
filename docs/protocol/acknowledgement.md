# UART Acknowledgment Rules

## 1. Purpose

Acknowledgments (ACK) are used by the ESP32 to inform
the Raspberry Pi that a received command has been processed.

An ACK confirms command processing, but does not necessarily
confirm the physical result of the command.

## 2. ACK Message Structure

Example:

{
  "v": 1,
  "type": "ack",
  "seq_num": 15,
  "status": "accepted"
}

Parameters:

- `v` — protocol version.
- `type` — message type (`ack`).
- `seq_num` — sequence number of the original command.
- `status` — command processing result.
- `reason` — optional rejection reason.

## 3. ACK Statuses

### accepted

The command passed validation and was accepted
by the ESP32.

### rejected

The command was rejected by the ESP32.

A rejection reason must be provided when possible.

## 4. Rejection Reasons

| Reason | Description |
|---|---|
| `unsupported_version` | Unsupported protocol version |
| `invalid_value` | Invalid command parameter |
| `invalid_state` | Command is not allowed in the current state |
| `stale_sequence` | Outdated sequence number |

If a message cannot be parsed or its sequence number
cannot be extracted, the ESP32 may ignore it without sending an ACK.

## 5. ACK Policy

| Command | ACK Required |
|---|---|
| `drive` | No |
| `stop` | Yes |
| `clear_fault` | Yes |

### Drive

Drive commands are transmitted periodically while the
operator holds a movement control.

ACK messages are not required for drive commands.

### Stop

The Raspberry Pi sends a stop command when the operator
releases a movement control.

The ESP32 sends one ACK for the received stop command.

The Raspberry Pi must not repeatedly send stop commands
while the rover is already in the STOPPED state.

### Clear Fault

The Raspberry Pi sends a clear_fault command when the
operator explicitly requests fault recovery.

The ESP32 must send an ACK indicating whether the
fault reset command was accepted or rejected.

## 6. Sequence Numbers

The Raspberry Pi assigns a sequence number to every
outgoing message, including drive, stop and clear_fault.

The ESP32 copies the original command's sequence number
into the corresponding ACK.

This allows the Raspberry Pi to match an ACK with
the command that generated it.

## 7. Important Notes

1. ACK confirms command processing, not physical execution.
2. A successful stop ACK does not guarantee that the
   rover is physically motionless.
3. The ESP32 must independently handle drive-command timeouts.
4. Safety mechanisms must not depend on receiving an ACK.
5. Missing ACK does not necessarily mean that a command
   was not processed.
