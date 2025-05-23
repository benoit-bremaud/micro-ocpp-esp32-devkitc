<<<<<<< HEAD
# micro-ocpp-esp32-devkitc
Micro-OCPP ESP32 module for OCPP 1.6J compliance testing with VEV-IQ supervision backend.
=======
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
git clone https://github.com/<your-org>/micro-ocpp-esp32-devkitc.git
cd micro-ocpp-esp32-devkitc
code .
```

### 2. Initialize PlatformIO

In VS Code:

* Open the command palette (⇧⌘P / Ctrl+Shift+P)
* Select `PlatformIO: Initialize Project`
* Board: `DOIT ESP32 DEVKIT V1`
* Framework: `Arduino`
* Ensure it uses the current folder (no nested sub-folder)

### 3. Configure Wi-Fi credentials

Edit `src/main.cpp`:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 4. Build and upload the firmware

Use the PlatformIO toolbar:

* ✅ Build
* ⬆️ Upload
* 🔍 Monitor (to view serial output)

You should see:

```text
✅ Wi-Fi connected
📡 IP address: 192.168.x.x
```

---

## 📁 Project Structure

```text
├── src/               # Main firmware code
├── lib/               # External libraries (e.g., MicroOCPP)
├── include/           # Custom headers (optional)
├── test/              # Unit tests
├── .pio/              # PlatformIO build system
├── platformio.ini     # Project configuration
├── README.md          # This file
├── .gitignore         # Ignored files
```

---

## 🔒 License

**Internal use only.**
This project is part of the VEV Platform Services France R\&D environment and is not intended for public redistribution.

All rights reserved.
>>>>>>> 184c62e (Add initial project structure with configuration and documentation)
