# FreeRTOS-practice
Hands-on experience with FreeRTOS.
I’m documenting my journey from **FreeRTOS basics** to **intermediate embedded concepts** using a Windows environment, GCC (MSYS2), and Visual Studio Code.

This repo contains clean, working FreeRTOS examples that build and run on the **FreeRTOS Windows Simulator** — ideal for learners and engineers preparing for embedded or RTOS-based projects.

---

## 🗂️ Repository Structure


> ⚠️ The official FreeRTOS source (`/Source`) is **not included** in this repo to keep it lightweight.  
> Add it locally for compilation if needed.

---

## 🧩 Topics Covered (7-Day Plan)

| Day | Topic | Concepts |
|-----|--------|-----------|
| **Day 1** | FreeRTOS Setup + First Task | Installing MSYS2, FreeRTOS Windows Simulator, Creating and running your first task |
| **Day 2** | Multi-tasking | Task creation, switching, priorities, scheduling |
| **Day 3** | Queues | Inter-task communication, message passing |
| **Day 4** | Semaphores & Mutex | Synchronization, resource sharing, avoiding race conditions |
| **Day 5** | Event Groups | Task coordination, synchronization mechanisms |
| **Day 6** | Software Timers | Periodic execution, callback mechanisms |
| **Day 7** | Mini Project | Combine concepts into a cohesive FreeRTOS demo |

---

## 🧰 Tools Used

| Tool | Purpose | Link |
|------|----------|------|
| **VS Code** | Code editor | [https://code.visualstudio.com/](https://code.visualstudio.com/) |
| **MSYS2** | GCC + Make environment | [https://www.msys2.org/](https://www.msys2.org/) |
| **FreeRTOS** | Real-Time Operating System | [https://www.freertos.org/](https://www.freertos.org/) |

---

## ⚙️ How to Build & Run

1. Clone this repository:
   ```bash
   git clone https://github.com/Raveem13/FreeRTOS-practice.git
   cd FreeRTOS-practice/Day01
