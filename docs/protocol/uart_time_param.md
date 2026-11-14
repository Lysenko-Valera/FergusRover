# UART Timing Parameters

## 1. Overview

This document defines the initial timing and communication
parameters for the UART connection between the Raspberry Pi
and the ESP32.

These values are initial configuration parameters and may
be adjusted during hardware testing.

## 2. Communication Parameters

| Parameter | Value |
|---|---|
| Baud rate | 115200 |
| Drive command interval | 50 ms |
| Drive command frequency | 20 Hz |
| Drive command timeout | 250 ms |
| Maximum message length | 128 bytes |

## 3. Baud Rate

The UART communication speed is set to:

115200 baud

Both the Raspberry Pi and ESP32 must use the same baud rate
and UART configuration.

## 4. Drive Command Interval

The Raspberry Pi periodically sends drive commands
while the operator holds a movement control.

Initial interval:

50 ms (20 Hz)

Drive commands must not be sent periodically while
the rover is in the STOPPED state.

## 5. Drive Command Timeout

The ESP32 monitors the time elapsed since the last
valid drive command.

Initial timeout:

250 ms

If no valid drive command is received within this period,
the ESP32 must:

1. Stop all motors.
2. Enter the FAIL_STOPPED state.
3. Reject subsequent drive commands until fault recovery.

Only a fully received and validated drive command
can refresh this timeout.

Invalid messages, incomplete messages and heartbeat
messages must not refresh the drive-command timeout.

The timeout is relevant while the ESP32 is in the DRIVING state.

## 6. Maximum Message Length

The maximum UART message length is:

128 bytes, including the newline character.

Messages exceeding this limit must be rejected.

An oversized or malformed message must never cause
unintended motor movement.

## 7. Notes

1. These parameters are initial values for UART v1.
2. Both devices must use matching UART settings.
3. Timing values may be adjusted after hardware testing.
4. The ESP32 must handle drive-command timeouts independently of the Raspberry Pi.
