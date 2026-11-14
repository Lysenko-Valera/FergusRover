# Communication Architecture

**Project:** Rover  
**Module:** ESP32 Firmware

## 1. Overview

The Communication Layer handles data exchange between Raspberry Pi and ESP32.

It consists of four components:

- **UartTransport** — handles low-level UART communication, message reception, transmission and framing.
- **ProtocolParser** — converts incoming JSON messages into structured C++ data.
- **ProtocolValidator** — checks messages against protocol rules and validates their fields and values.
- **ProtocolHandler** — coordinates command processing, communicates with control modules and prepares ACK responses.

## 2. Data Flow

### Incoming Messages

1. `UartTransport` receives a complete message from Raspberry Pi.
2. `ProtocolParser` converts JSON into an `IncomingMessage`.
3. `ProtocolValidator` checks the message.
4. `ProtocolHandler` coordinates the processing of valid commands.
5. The appropriate Control Layer module handles the requested operation.

### Outgoing Messages

1. `ProtocolHandler` prepares an ACK when required.
2. The application layer passes the response to `UartTransport`.
3. `UartTransport` sends the message to Raspberry Pi.

## 3. Module Boundaries

- `UartTransport` does not parse JSON or interpret commands.
- `ProtocolParser` does not validate command execution or control hardware.
- `ProtocolValidator` does not execute commands or manage UART communication.
- `ProtocolHandler` does not directly control motors or implement the safety state machine.
- The Control Layer is responsible for command execution and rover control.

## 4. Related Documentation

- `uart_protocol.md` — message formats and protocol rules.
- `uart_time_param.md` — UART and timing parameters.
- `acknowledgement.md` — ACK rules.
- `uart_fst.md` — safety state machine.