# Logging System – README

## Overview

This directory contains the unified logging system for the VEV-Gateway ESP32 external OCPP interface module.

The logger provides a consistent, configurable, and lightweight way to trace and debug all system activities.
It supports log levels, contextual information, and is designed for future extensions (persistent storage, web viewing, memory monitoring).

---

## Features

* **Log levels:** DEBUG, INFO, WARNING, ERROR (settable at runtime or compile-time)
* **Macros:** Easy-to-use macros for logging: `LOG_DEBUG`, `LOG_INFO`, `LOG_WARN`, `LOG_ERROR`
* **Automatic context:** Each log entry includes timestamp, file, function, and line number
* **Output:** Serial console (default), ready for SPIFFS or web in future versions
* **Minimal footprint:** Optimized for embedded constraints
* **Extensible:** Buffering, rotation, and remote streaming planned

---

## Getting Started

### 1. Include the Logger

In any file where you need logging, add:

```cpp
#include "log_macros.h"
```

### 2. Set log level (usually in `setup()`)

```cpp
Logger::getInstance().setLevel(LOG_LEVEL_INFO);  // or LOG_LEVEL_DEBUG
```

### 3. Add log statements

```cpp
LOG_DEBUG("Debug value: %d", value);
LOG_INFO("System started");
LOG_WARN("Possible issue detected");
LOG_ERROR("Fatal error: %s", msg);
```

Context (file, function, line) and timestamp are automatic.

### 4. Output format

Serial output example:

```
[0000-00-00T01:23:45Z] [1] main.cpp:34 (setup): System started
```

* `[timestamp] [log level] file:line (function): message`

---

## File Structure

```
features/
  └── infra/
       └── logging/
           ├── Logger.h
           ├── log_macros.h
src/
  ├── main.cpp
  ├── Logger.cpp
```

* All `.cpp` files **must be in `/src/`** to be built by PlatformIO
* Headers can be organized freely, as long as include paths are set in `platformio.ini`

---

## Advanced Usage

* **Change timestamp to real UTC:** If WiFi/NTP/RTC is available, update `getTimestampISO8601()` for real time
* **Buffering & SPIFFS:** Circular buffer and file logging coming soon
* **Web viewer:** HTTP log endpoint planned for embedded diagnostics

---

## Troubleshooting

* If you get linker errors: ensure `Logger.cpp` is present in `/src/`
* If logs do not appear: verify log level and serial speed (`115200`)
* Compilation errors: check include paths in `platformio.ini` and header locations

---

## References

* VEV-Gateway Project Canvas
* OCPP 1.6/2.0.1 Specification – Logging/Diagnostics
* ESP32 / PlatformIO documentation

---

*For questions, open an issue or refer to the documentation in `/docs/`.*
