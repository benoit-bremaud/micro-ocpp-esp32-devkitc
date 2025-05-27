# PROJECT PLAN – Micro-OCPP ESP32 DevKitC

> Project: VEV-Gateway External Interface Module
> Target Platform: ESP32-WROOM-32D (DOIT DevKitC)
> Maintainer: VEV Platform Services France – R\&D Team

---

## 🎯 Objective

This document outlines the development plan and GitHub Project structure for the **Micro-OCPP ESP32 DevKitC** firmware. It ensures clarity and traceability across contributors and project phases, in alignment with the VEV-Gateway initiative.

The goal is to deliver a fully functional, standards-compliant Micro-OCPP firmware (OCPP 1.6J) on ESP32, designed to bridge non-OCPP EV chargers with VEV-IQ backend.

---

## 🧱 Directory Structure

```text
├── src/               → Main firmware logic (main.cpp)
├── lib/               → External libraries (MicroOCPP)
├── include/           → Configuration headers
├── test/              → Unit and integration tests
├── .gitignore         → Git exclusion rules
├── .editorconfig      → Code style unification
├── platformio.ini     → PlatformIO board config
├── README.md          → Project overview
├── PROJECT_PLAN.md    → You are here 👈
```

---

## 📦 GitHub Project Layout

* **Board name**: `micro-ocpp-esp32 · Project Plan`
* **View**: Kanban
* **Columns**:

  * `📌 Backlog`
  * `🚧 In Progress`
  * `✅ Done`

### 🔖 Labels Used

| Label          | Purpose                      |
| -------------- | ---------------------------- |
| `type:feat`    | New functionality            |
| `type:fix`     | Bug fix                      |
| `type:chore`   | Maintenance tasks            |
| `type:docs`    | Documentation                |
| `scope:repo`   | Repository-level maintenance |
| `scope:ci`     | Continuous Integration setup |
| `scope:readme` | README.md documentation      |
| `scope:plan`   | Roadmap and planning         |

---

## 🗂️ Milestones Overview

| Milestone ID | Title                        | Description                                      |
| ------------ | ---------------------------- | ------------------------------------------------ |
| `M0`         | Repository Setup             | Initial file structure, README, .gitignore, plan |
| `M1`         | Hardware Interface           | GPIO setup, board selection, env config          |
| `M2`         | Wi-Fi + WebSocket Layer      | Network connection and OCPP bootstrap            |
| `M3`         | Core OCPP Message Flow       | BootNotification, Authorize, Tx start/stop       |
| `M4`         | MeterValues and Heartbeat    | Real-time values and basic monitoring            |
| `M5`         | Simulation & Testing         | CSMS emulation, scenario testing                 |
| `M6`         | Security Layer               | TLS, certificates, flash protection              |
| `M7`         | Documentation and Compliance | Final cleanup, Notion sync, OCTT validation      |

---

## 🧾 Issue & Branch Naming Conventions

### ✅ Issues (Angular Convention)

```text
<type>(<scope>): <short description>
```

Examples:

* `chore(repo): create and configure repository`
* `docs(readme): finalize initial project overview`

### 🌿 Branches

```text
<type>/<short-description>
```

Examples:

* `feat/bootnotification-handler`
* `docs/project-plan`

---

## 🔗 Integration in README

The `PROJECT_PLAN.md` file is referenced in the `README.md` under a new section:

```md
## 📌 Project Plan
See [PROJECT_PLAN.md](./PROJECT_PLAN.md) for the complete roadmap, milestones, and issue conventions.
```

---

## ✅ Next Step

Track progress using the GitHub Project board and ensure each milestone is linked to the appropriate issue and pull request.

For questions, contact the project maintainer.
