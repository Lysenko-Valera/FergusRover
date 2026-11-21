
# Rover_WEB API Design

## 1. Purpose

This document defines the initial API contract for Rover_WEB.

The API provides a communication interface between the web frontend and the backend. It abstracts hardware communication and internal backend implementation from the frontend.

## 2. API Conventions

- REST API is used for standard HTTP requests.
- WebSocket is used for real-time communication.
- REST endpoints use the `/api/v1` prefix.
- JSON is the default data format.
- `/health` is reserved for basic backend health checks.
- API requests must not bypass backend validation or device-side safety mechanisms.

## 3. REST Endpoints

### Health

| Method | Endpoint | Description |
|---|---|---|
| GET | `/health` | Basic backend health check |

### System

| Method | Endpoint | Description |
|---|---|---|
| GET | `/api/v1/system/status` | Retrieve system component status |

### Control

| Method | Endpoint | Description |
|---|---|---|
| POST | `/api/v1/control/command` | Submit a control command |
| POST | `/api/v1/control/stop` | Request a stop |
| GET | `/api/v1/control/state` | Retrieve control state |

### Telemetry

| Method | Endpoint | Description |
|---|---|---|
| GET | `/api/v1/telemetry` | Retrieve current telemetry |

### Settings

| Method | Endpoint | Description |
|---|---|---|
| GET | `/api/v1/settings` | Retrieve settings |
| PATCH | `/api/v1/settings` | Update selected settings |

### Diagnostics

| Method | Endpoint | Description |
|---|---|---|
| GET | `/api/v1/diagnostics` | Retrieve diagnostic information |

## 4. WebSocket

| Endpoint | Description |
|---|---|
| `/ws/telemetry` | Real-time telemetry and system updates |

Initial message types:

- `telemetry`
- `system_status`
- `connection_status`
- `event`

## 5. Safety and Validation

- Control requests must be validated by the backend.
- Device communication status must be considered before accepting control requests.
- Device-side safety mechanisms must remain independent of the web application.
- Communication failures must not be interpreted as permission to continue operation.
- The backend must not report a device as connected without a verified connection state.

## 6. Implementation Status

This document describes the planned API contract.

The endpoints listed here are not all implemented yet. They will be implemented incrementally in subsequent development stages.
