# Micro-OCPP ESP32 DevKitC

> Internal R\&D Project – VEV Platform Services France
> OCPP 1.6J integration on ESP32 for EVSE gateway simulation

This repository contains a firmware project based on PlatformIO for the ESP32-WROOM-32D module. It integrates the [Micro-OCPP](https://github.com/matth-x/MicroOcpp) library to emulate a basic OCPP 1.6J EVSE, capable of connecting to an OCPP backend such as **VEV-IQ**.

---

## 📦 Features

* ESP32-WROOM-32D (DOIT DevKitC)
* Wi-Fi connection with WebSocket client
* OCPP 1.6J message support:

  * `BootNotification`
  * `Authorize`
  * `StartTransaction`
  * `StopTransaction`
  * `MeterValues`
  * (optional) `Heartbeat`, `DiagnosticsStatusNotification`, `FirmwareStatusNotification`
* TLS-ready configuration (optional)
* Modular hardware abstraction for relays, RFID, LEDs, etc.
* Fully integrated with the **VEV-Gateway** project stack

---

## 🧰 Requirements

| Component   | Details                       |
| ----------- | ----------------------------- |
| ESP32 Board | DOIT ESP32 DEVKIT V1          |
| Framework   | PlatformIO + Arduino          |
| Toolchain   | Visual Studio Code + PIO IDE  |
| Backend     | VEV-IQ (OCPP 1.6J compatible) |

---

## 🚀 Quick Start

### 1. Clone the Repository

```bash
git clone git@github.com:benoit-bremaud/micro-ocpp-esp32-devkitc.git
cd micro-ocpp-esp32-devkitc
code .
```

### 2. Initialize PlatformIO Project (if needed)

* Open VS Code Command Palette (`⇧⌘P` or `Ctrl+Shift+P`)
* Run `PlatformIO: Initialize Project`
* Select `DOIT ESP32 DEVKIT V1` and Arduino framework

### 3. Configure Your Local Environment

```bash
cp include/env.example.h include/env.h
```

Edit `include/env.h`:

```cpp
#define WIFI_SSID        "YourSSID"
#define WIFI_PASSWORD    "YourPassword"
#define OCPP_ENDPOINT    "wss://your-csms-url/ocpp"
#define CHARGE_BOX_ID    "your-charge-box-id"
```

### 4. Build, Upload, Monitor

Use the PlatformIO interface or CLI:

* ✅ Build
* ⬆️ Upload
* 🔍 Monitor (serial log output)

Expected output:

```text
[BOOT] Connecting to Wi-Fi...
✅ Wi-Fi connected
📡 IP Address: 192.168.X.X
```

---

## 📁 Project Structure

```text
├── src/                 # Main application code
├── lib/                 # External libraries (e.g., MicroOCPP)
├── include/             # Custom headers and configuration
│   ├── env.h            # Local secrets (excluded from Git)
│   ├── env.example.h    # Template for `env.h`
│   └── config.h         # Shared definitions
├── test/                # Unit test files
├── platformio.ini       # PlatformIO configuration
├── .gitignore           # Git ignore rules
├── README.md            # Project overview (this file)
```

---

## 🔐 Configuration Management

This project uses structured configuration layering:

* `include/env.h`: Not committed – contains sensitive credentials
* `include/env.example.h`: Versioned template – for sharing default structure
* `include/config.h`: Shared and versioned configuration for internal logic

---

## ⚠️ License

**Internal Use Only – VEV Platform Services France**
This project is intended solely for development within the VEV-Gateway initiative. Redistribution or public deployment is not permitted without explicit authorization.

All rights reserved.
