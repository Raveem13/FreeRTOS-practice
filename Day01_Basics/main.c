#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTaskA(void *pvParameters)
{
    for(;;)
    {
        printf("Task A running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));   // 1 second delay
    }
}

void vTaskB(void *pvParameters)
{
    for(;;)
    {
        printf("Task B running\n");
        vTaskDelay(pdMS_TO_TICKS(500));    // 0.5 second delay
    }
}

int main(void)
{
    printf("=== FreeRTOS Day 1 Demo ===\n");

    xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();   // Never returns
    for(;;);
}

