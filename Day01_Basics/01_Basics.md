
# 🧩 **Day 1 — FreeRTOS Basics & Task Scheduling**

---

## 🎯 **Learning Goals**

By the end of Day 1, you’ll understand:

1. What an RTOS does and why it’s needed
2. What a *task* is and how scheduling works
3. How `vTaskDelay()` and system *ticks* control timing
4. How to create, run, and observe multiple tasks in action

---

## 🧠 **1️⃣ What is FreeRTOS?**

### 💡 Definition

**FreeRTOS** (Real-Time Operating System) is a lightweight kernel that manages:

* **Tasks (threads)** — concurrent units of work
* **Scheduling** — decides *which* task runs *when*
* **Communication & Sync** — Queues, Semaphores, etc.
* **Timing** — uses hardware timer “tick” interrupts for delays & timeouts

Unlike a normal program where only `main()` runs,
in FreeRTOS, **multiple functions (tasks)** run seemingly at once.

---

## ⚙️ **2️⃣ Basic Concepts**

### 🧱 Task

A *task* = a function with an infinite loop.
Each has its **stack**, **priority**, and **state**.

```c
void MyTask(void *pvParameters)
{
    for(;;)
    {
        // do something repeatedly
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```

---

### 📅 Scheduler

The **Scheduler** decides which task runs next.
It uses:

* **Preemption** — higher-priority tasks can interrupt lower ones
* **Time slicing** — same-priority tasks share CPU time equally

Scheduler runs continuously after:

```c
vTaskStartScheduler();
```

---

### ⏱️ Tick Interrupt

* Generated periodically by a hardware timer (e.g., every 1 ms)
* Used to manage `vTaskDelay()` and timeouts
* Each tick = one scheduling decision opportunity

---

### 🧩 **States of a Task**

| State         | Description                            |
| ------------- | -------------------------------------- |
| **Running**   | Currently executing                    |
| **Ready**     | Ready to run when CPU available        |
| **Blocked**   | Waiting for delay/time/queue/semaphore |
| **Suspended** | Inactive until resumed                 |

---

## 💻 **3️⃣ Hands-On Code: Your First Two Tasks**

**main.c**

```c
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTaskA(void *pvParameters)
{
    for(;;)
    {
        printf("Task A running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));   // 1 second
    }
}

void vTaskB(void *pvParameters)
{
    for(;;)
    {
        printf("Task B running\n");
        vTaskDelay(pdMS_TO_TICKS(500));    // 0.5 second
    }
}

int main(void)
{
    printf("=== FreeRTOS Day 1 Demo ===\n");

    xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();   // Start multitasking
    for(;;); // never reached
}
```

---

## 🧰 **4️⃣ Build and Run**

```bash
make clean
make run
```

✅ Expected Output:

```
=== FreeRTOS Day 1 Demo ===
Task B running
Task A running
Task B running
Task B running
Task A running
...
```

---

## 🔍 **5️⃣ What’s Happening Internally**

1. `xTaskCreate()`

   * Allocates stack
   * Initializes Task Control Block (TCB)
   * Adds it to Ready list

2. `vTaskStartScheduler()`

   * Starts SysTick timer interrupt
   * Begins context switching between tasks

3. `vTaskDelay()`

   * Moves current task to *Blocked* state
   * After the specified ticks, it moves back to *Ready*

4. **Round-Robin Scheduling**
   Since both tasks have the same priority (1),
   they share CPU time equally.

---

## 🧩 **6️⃣ Modify & Explore**

### 🧠 Challenge 1 — Change Timings

Try:

```c
Task A → 2000 ms delay  
Task B → 400 ms delay
```

🧩 Observe Task B prints more often — it’s *more responsive*.

---

### 🧠 Challenge 2 — Add Task C

```c
void vTaskC(void *pvParameters)
{
    for(;;)
    {
        printf("Task C running\n");
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
```

Add to main:

```c
xTaskCreate(vTaskC, "TaskC", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
```

🧩 Now you’ll see all three interleaving — pure cooperative multitasking!

---

### 🧠 Challenge 3 — Observe Tick Period

In `FreeRTOSConfig.h`, find or define:

```c
#define configTICK_RATE_HZ 1000
```

This means 1 tick = 1 ms.
Try changing it to `500` → your delays will appear *twice as long*.

---

## 🧩 **7️⃣ Visualization**

```
Time (ms): 0---500---1000---1500---2000---2500---
Task B:    |run|run|run|run|run|run|...
Task A:          |run|          |run| ...
```

FreeRTOS time-slices at each tick (every 1 ms).
`vTaskDelay()` uses the tick count to wake up tasks at the right time.

---

## ✅ **8️⃣ Summary**

| Concept         | You Learned                                  |
| --------------- | -------------------------------------------- |
| Task Creation   | `xTaskCreate()`                              |
| Task Delay      | `vTaskDelay()` and `pdMS_TO_TICKS()`         |
| Scheduler Start | `vTaskStartScheduler()`                      |
| Task States     | Ready ↔ Blocked transitions                  |
| Tick Timing     | `configTICK_RATE_HZ` defines delay precision |

---

## 🚀 **Next: Day 2 – Task Priorities & Preemption**

You’ll learn:

* How priority affects CPU time
* What happens when a high-priority task becomes Ready
* Preemption vs. time-slicing behavior
* Practical demo with priority inversion example

---