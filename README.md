# Micro-OCPP ESP32 DevKitC

> Internal VEV project — OCPP 1.6J integration on ESP32 for EV charger gateway simulation.

This repository contains a PlatformIO-based firmware project for an ESP32-WROOM-32D module.
It runs [Micro-OCPP](https://github.com/matth-x/MicroOcpp) and simulates an EVSE speaking OCPP 1.6J, designed to interact with the VEV-IQ backend.

---

## 📦 Features

* ESP32-WROOM-32D (DOIT DevKitC)
* Wi-Fi connection and WebSocket client
* OCPP 1.6J message support (BootNotification, Authorize, TxStart/Stop, etc.)
* TLS-ready configuration (optional)
* Modular design for testing relays, RFID, LEDs, etc.
* Fully integrated into the VEV-Gateway project architecture

---

## 🧰 Requirements

| Component   | Version / Note                |
| ----------- | ----------------------------- |
| ESP32 board | DOIT ESP32 DEVKIT V1          |
| Framework   | PlatformIO + Arduino          |
| Toolchain   | VS Code + PlatformIO IDE      |
| Backend     | VEV-IQ (OCPP 1.6J compatible) |

---

## 🚀 Quick Start

### 1. Clone the repository

```bash
git clone git@github.com:benoit-bremaud/micro-ocpp-esp32-devkitc.git
cd micro-ocpp-esp32-devkitc
code .
```plaintext

### 2. Initialize PlatformIO project (if not already done)

* Open the VS Code command palette (`⇧⌘P` or `Ctrl+Shift+P`)
* Run `PlatformIO: Initialize Project`
* Select `DOIT ESP32 DEVKIT V1` board and `Arduino` framework
* Make sure the project initializes in the root directory

### 3. Create your local configuration file

```bash
cp include/env.example.h include/env.h
```

Then edit `include/env.h` with your credentials:

```cpp
#define WIFI_SSID        "YourSSID"
#define WIFI_PASSWORD    "YourPassword"
#define OCPP_ENDPOINT    "wss://your-csms-url.com/ocpp"
#define CHARGE_BOX_ID    "your-charge-box-id"
```

### 4. Build, Upload and Monitor

Use the PlatformIO toolbar or commands:

* ✅ Build
* ⬆️ Upload
* 🔍 Monitor (to view serial output)

Expected serial output:

```text
[BOOT] Connecting to Wi-Fi...
✅ Wi-Fi connected
📡 IP Address: 192.168.x.x
```

---

## 📁 Project Structure

```text
├── src/                 # Main firmware code (main.cpp)
├── lib/                 # External libraries (e.g., MicroOCPP)
├── include/             # Custom headers (env.h, config.h)
│   ├── env.h            # Local (not versioned)
│   └── config.h         # Shared definitions
├── test/                # Unit tests
├── .pio/                # PlatformIO build system
├── platformio.ini       # Project configuration
├── .gitignore           # Ignored files and folders
├── README.md            # This file
```

---

## 🔐 Configuration Management

This project uses external configuration files to separate secrets:

* `include/env.h` → **NOT versioned**, contains Wi-Fi, OCPP credentials
* `include/env.example.h` → **versioned**, template for credentials
* `include/config.h` → Versioned, shared build-time configuration

📌 Copy `include/env.example.h` to `include/env.h` and fill in your parameters before flashing.

---

## 🔒 License

**Internal use only.**
This project is part of the VEV Platform Services France R\&D environment and is not intended for public redistribution.

All rights reserved.
