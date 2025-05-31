# Logging System – README

## Overview

This directory contains the unified logging system for the VEV-Gateway ESP32 external OCPP interface module.

The logger provides a consistent, configurable, and lightweight way to trace and debug all system activities.
It supports log levels, contextual information, and persistent output to SPIFFS and WebServer.

---

## Features

* **Log levels:** `DEBUG`, `INFO`, `WARNING`, `ERROR`, `NONE` – settable dynamically or statically
* **Macros:** Easy-to-use macros for logging: `LOG_DEBUG`, `LOG_INFO`, `LOG_WARN`, `LOG_ERROR`
* **Automatic context:** Timestamp, file, function, and line number included in each entry
* **Output targets:**

  * Serial console (default)
  * SPIFFS with file rotation
  * HTTP Web log viewer (`/log` endpoint)
* **Circular buffer:** In-memory log history (configurable size, FIFO behavior)
* **Minimal footprint:** Designed for ESP32 constraints, minimal allocations
* **Modular design:** Based on feature-oriented structure for scalability

---

## Getting Started

### 1. Include the Logger

In any `.cpp` file:

```cpp
#include "log_macros.h"
```

### 2. Initialize logger (in `setup()`)

```cpp
Logger::getInstance().begin(true);  // true enables SPIFFS file logging
```

### 3. Set log level

```cpp
Logger::getInstance().setLevel(LOG_LEVEL_INFO);  // or LOG_LEVEL_DEBUG
```

### 4. Use logging macros

```cpp
LOG_DEBUG("Debug value: %d", value);
LOG_INFO("System initialized");
LOG_WARN("Low memory warning");
LOG_ERROR("Critical error: %s", msg);
```

Each message automatically includes file/function/line info and ISO 8601 uptime timestamp.

### 5. View logs

* **Serial output**: logs are printed in structured format.
* **SPIFFS files**: logs are written in `/log_0.txt`, `/log_1.txt`, etc. with automatic rotation.
* **Web viewer**: start WebServer and access `http://<ESP32-IP>/log` to view log history.

---

## File Structure

```
features/
  └── infra/
       ├── logging/
       │   ├── Logger.h
       │   ├── log_macros.h
       │   ├── file_logger.h
       └── web/
           └── web_log_viewer.h
src/
  ├── Logger.cpp
  ├── FileLogger.cpp
  ├── WebLogViewer.cpp
  └── main.cpp
```

> Note: All `.cpp` files **must** be placed under `/src/` for PlatformIO to compile them.

---

## Configuration

### `platformio.ini`

Ensure these flags and include paths are defined:

```ini
build_flags =
    -I include
    -I features
    -I features/infra
    -I features/infra/logging
    -I features/infra/web
    -I src
    -D PROJECT_VERSION=\"2.0.0\"
    -D OCPP_VERSION=\"1.6\"
```

---

## Web Viewer Endpoint

The embedded log viewer is available at `/log` (GET).
It displays recent log entries from the in-memory circular buffer in plain text.
Useful for diagnostics via browser or REST client (e.g., `curl http://<ip>/log`).

Make sure WebServer is initialized in `setup()`:

```cpp
WebLogViewer::getInstance().begin(server);  // 'server' is your WebServer instance
```

---

## Troubleshooting

* **Linker errors**: Ensure all `.cpp` are in `/src/` and headers are correctly included
* **Missing logs**: Check `Logger::setLevel()` and ensure `begin()` is called
* **SPIFFS issues**: Verify SPIFFS mount is successful (`SPIFFS.begin()`)
* **Web log viewer fails**: Confirm `WebServer` is running and IP is accessible

---

## References

* VEV-Gateway Project Canvas
* OCPP 1.6J – Diagnostics section
* ESP32 / PlatformIO documentation
* Arduino WebServer library reference

---

*For feedback or contributions, open an issue in the repository or refer to `/docs/`.*
