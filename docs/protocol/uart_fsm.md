# UART Safety State Machine

## 1. States

### STOPPED
All motors are stopped.

This is the initial state after ESP32 startup.
The rover waits for a valid drive command.

### DRIVING
The ESP32 is executing a valid motor command received from the Raspberry Pi.

Only valid drive commands can refresh the drive-command timeout.

### FAIL_STOPPED
All motors are stopped due to a safety-related event, such as a communication timeout.

While in this state, the ESP32 must reject all drive commands, even if they are valid.

The rover remains in this state until an explicit fault reset command is received.

## 2. State Transitions

| Current State | Event | Next State |
|---|---|---|
| Startup | ESP32 initialization | STOPPED |
| STOPPED | Valid drive command | DRIVING |
| DRIVING | Valid drive command | DRIVING |
| DRIVING | Stop command | STOPPED |
| DRIVING | Drive-command timeout | FAIL_STOPPED |
| STOPPED | Invalid command | STOPPED |
| FAIL_STOPPED | Drive command | FAIL_STOPPED |
| FAIL_STOPPED | Connection restored | FAIL_STOPPED |
| FAIL_STOPPED | Valid clear_fault command | STOPPED |

## 3. Safety Rules

1. The initial state after ESP32 startup must be STOPPED.
2. All motors must remain stopped until a valid drive command is received.
3. Only valid drive commands can refresh the drive-command timeout.
4. Invalid messages must not refresh the timeout.
5. A stop command must immediately stop all motors.
6. If the drive-command timeout expires, the ESP32 must enter FAIL_STOPPED.
7. While in FAIL_STOPPED, all drive commands must be rejected.
8. Restoring the UART connection must not automatically clear the fault.
9. Only an explicit clear_fault command can clear the fault.
10. A clear_fault command must never start the motors.
11. A new drive command is required to resume movement.

## 4. Fault Recovery Procedure

After a communication failure:

1. The ESP32 stops all motors.
2. The ESP32 enters FAIL_STOPPED.
3. The UART connection is restored.
4. The operator presses the recovery button on the website.
5. The Raspberry Pi sends a clear_fault command.
6. The ESP32 validates the command and changes its state to STOPPED.
7. The rover waits for a new drive command.
8. The operator must provide a new movement input to resume driving.

## 5. Important Notes

- The website must not automatically send clear_fault after reconnection.
- The operator must explicitly request fault recovery.
- Old or buffered drive commands must not be executed after fault recovery.
- If the clear_fault command is invalid, the ESP32 must remain in FAIL_STOPPED.
