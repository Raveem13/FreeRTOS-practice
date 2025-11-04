#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTask1(void *pvParameters)
{
    while (1)
    {
        printf("Task 1 running\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int main(void)
{
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    for(;;);
}