#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

void vTaskBlink(void *pvParameters)
{
    while (1)
    {
        printf("LED Toggled!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    printf("FreeRTOS Demo Start\n");
    xTaskCreate(vTaskBlink, "Blink", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    for (;;);
}
