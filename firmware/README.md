## Firmware Architecture

The firmware is divided into several independent
modules, each responsible for a specific part
of the rover's low-level software.

### Module Responsibilities

#### Communication

Responsible for communication between the Raspberry Pi
and ESP32 over UART.

Responsibilities:
- Receiving UART messages.
- Parsing incoming protocol messages.
- Validating message structure and values.
- Sending acknowledgments (ACK).

#### Safety

Responsible for rover movement authorization
and safety state management.

Responsibilities:
- Managing the rover safety state machine.
- Monitoring drive-command timeout.
- Authorizing or rejecting movement commands.
- Handling stop commands.
- Handling fault recovery.
- Requesting motor stop when a safety fault occurs.

#### Motors

Responsible for controlling the six DC motors.

Responsibilities:
- Controlling motor PWM signals.
- Controlling motor direction.
- Applying motor commands.
- Stopping all motors.

#### Sensors

Responsible for communication with onboard sensors
and collecting sensor data.

Initial sensors:
- MPU6050
- BME280

## Module Interaction

The firmware uses the following command processing flow:

1. Communication receives a complete UART message.
2. The protocol handler parses and validates the message.
3. Validated commands are passed to the Safety module.
4. Safety checks whether the command is allowed
   in the current state.
5. If movement is authorized, Safety passes the
   motor command to the Motors module.
6. Motors applies the requested motor outputs.

The Safety module is the only component authorized
to decide whether motor movement is allowed.

The Motors module does not independently authorize
movement commands. It only applies commands received
from the Safety module.

## Safety Principles

- The ESP32 must independently enforce movement safety.
- Communication loss must result in a safe motor stop.
- Invalid messages must not refresh the drive-command timeout.
- Movement must not automatically resume after a safety fault.
- Fault recovery requires an explicit command.
- A new drive command is required after fault recovery.
