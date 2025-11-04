This assumes you have no existing setup.
We’ll go from zero → successfully running your first FreeRTOS multitasking example.
---

## 🧠 FreeRTOS Setup Guide (Windows + VS Code + MinGW64)

### 🧩 Overview

This guide explains how to set up, build, and run FreeRTOS on **Windows** using the **FreeRTOS Windows Simulator**, **MSYS2/MinGW64**, and **VS Code**.

---

### ⚙️ 1. Install Required Tools

| Tool        | Purpose                   | Download                                                       |
| ----------- | ------------------------- | -------------------------------------------------------------- |
| **VS Code** | Editor & terminal         | [https://code.visualstudio.com](https://code.visualstudio.com) |
| **MSYS2**   | GCC compiler + make tools | [https://www.msys2.org/](https://www.msys2.org/)               |
| **Git**     | Version control           | [https://git-scm.com/downloads](https://git-scm.com/downloads) |

---

### 🪟 2. Setup MSYS2 & MinGW64 Environment

1. Install MSYS2 (`msys2-x86_64-xxxx.exe`)
    Choose default location:
    C:\msys64

2. Open the **MSYS2 terminal (MINGW64)** and run updates:

   ```bash
   pacman -Syu
   ```

   (Restart MSYS2 if it asks you to.)
    When prompted, close the terminal and reopen it.

3. Update remaining packages:
    ```bash
    pacman -Su
    ```

3. Install GCC, Make, and Git:

   ```bash
   pacman -S --needed base-devel mingw-w64-x86_64-gcc git
   ```
<!-- 
4. **Close MSYS2** and **open MinGW64** from Start Menu:
   👉 `Start → MSYS2 → MinGW64` -->

4. Verify installations:

   ```bash
   gcc --version
   make --version
   git --version
   ```

   Each should display version info without error.

---

### 📂 3. Set Up Project Directory Structure

Navigate to your working directory:

```bash
cd /c/Users/<YourName>/GitHub\ Projects/
```

Create folders:

```bash
mkdir -p FreeRTOS_practice/Day00
```

Clone FreeRTOS kernel (recommended over ZIP):

```bash
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
```

Directory layout:

```
C:/Users/<YourName>/GitHub Projects/
│
├── FreeRTOS-Kernel/          ← cloned FreeRTOS source
│
└── FreeRTOS_practice/
     └── Day00/
          ├── main.c
          ├── FreeRTOSConfig.h
          └── Makefile
```

---

### 🧱 4. Sample Makefile (for Day00)

```makefile
CC = gcc
CFLAGS = -I../../FreeRTOS-Kernel/include \
         -I../../FreeRTOS-Kernel/portable/MSVC-MingW \
         -I. -Wall

SRC = main.c \
      ../../FreeRTOS-Kernel/tasks.c \
      ../../FreeRTOS-Kernel/queue.c \
      ../../FreeRTOS-Kernel/list.c \
      ../../FreeRTOS-Kernel/timers.c \
      ../../FreeRTOS-Kernel/event_groups.c \
      ../../FreeRTOS-Kernel/portable/MemMang/heap_4.c \
      ../../FreeRTOS-Kernel/portable/MSVC-MingW/port.c

TARGET = freertos_demo

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET).exe -lwinmm

run: all
	./$(TARGET).exe

clean:
	rm -f $(TARGET).exe
```

---

### 💡 5. Sample `main.c`

```c
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTask1(void *pvParameters)
{
    while (1)
    {
        printf("Task 1 running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    printf("FreeRTOS Demo Start\n");
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    for (;;);
}
```

---

### ⚙️ 6. Sample `FreeRTOSConfig.h`

A minimal config file (for Windows simulator):

```c
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 1000000 )
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 130 )
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 75 * 1024 ) )
#define configMAX_TASK_NAME_LEN         10
#define configUSE_TRACE_FACILITY        0
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1

#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_vTaskResume             1

#endif
```

---

### 🚀 7. Build and Run

Run these **in MinGW64 terminal** inside your `Day00/` folder:

1. Build using make:
    ```bash
    make run
    ```

    Expected output:

    ```
    FreeRTOS Demo Start
    Task 1 running
    Task 1 running
    ...
    ```

2. Run the executable:
    ```bash
    ./freertos_demo.exe
    ```

3. Clean build: Delete previous build file(.exe)
    ```bash
    make clean
    ```
---

### 🧰 8. Common Issues

| Problem                                 | Cause                       | Solution                       |
| --------------------------------------- | --------------------------- | ------------------------------ |
| `make: command not found`               | MinGW64 tools not installed | Run `pacman -S make`           |
| `gcc: command not found`                | Wrong terminal              | Use **MinGW64**, not MSYS      |
| `fatal error: FreeRTOS.h: No such file` | Incorrect `-I` include path | Fix `CFLAGS` paths in Makefile |
| `No rule to make target 'run'`          | Missing target in Makefile  | Ensure `run:` section exists   |

---

### 🧩 9. Recommended VS Code Settings

Add this to your VS Code `.vscode/settings.json`:

```json
{
  "terminal.integrated.profiles.windows": {
    "MinGW64": {
      "path": "C:\\msys64\\mingw64.exe"
    }
  },
  "terminal.integrated.defaultProfile.windows": "MinGW64"
}
```

---

### ✅ 10. Summary

| Step | Action                                           |
| ---- | ------------------------------------------------ |
| 1    | Install MSYS2 & VS Code                          |
| 2    | Open **MinGW64** terminal                        |
| 3    | Clone FreeRTOS kernel                            |
| 4    | Create practice folder (`Day00`)                 |
| 5    | Add `main.c`, `FreeRTOSConfig.h`, and `Makefile` |
| 6    | Run `make run` to execute FreeRTOS demo          |

---