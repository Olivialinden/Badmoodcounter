#include <stdio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "time.h" // Include time.h for time-related functions

#define LCD_WIDTH 50
#define MAX_RECORDS 7 // Store records for the last 7 days

enum State {
    POWER_ON,
    WELCOME,
    SHOW_BAD_MOOD_COUNT,
    SHOW_RECORDS,
};

int badMoodCount = 0;
int badMoodRecords[MAX_RECORDS] = {0};
int recordIndex = 0;
enum State currentState = POWER_ON;
SemaphoreHandle_t lcdMutex;
EventGroupHandle_t buttonEventGroup;

void displayLCD(const char *message, int count) {
    xSemaphoreTake(lcdMutex, portMAX_DELAY);
    printf(message, count);
    printf("\n");
    xSemaphoreGive(lcdMutex);
}

void resetDailyCount() {
    badMoodCount = 0;
    displayLCD("Daily count reset to 0", badMoodCount);
}

void storeDailyRecord() {
    if (recordIndex < MAX_RECORDS) {
        badMoodRecords[recordIndex] = badMoodCount;
        recordIndex++;
    } else {
        // If you want to wrap around and overwrite old records, you can add that logic here
        // For now, we'll assume you don't want to overwrite old records
    }
}

void vLCDTask(void *pvParameters) {
    displayLCD("Welcome, this is a bad mood counter", badMoodCount);

    while (1) {
        // Implement LCD display functionality here
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay to simulate LCD update
    }
}

void vButtonTask(void *pvParameters) {
    EventBits_t uxBits;
    char button;

    while (1) {
        uxBits = xEventGroupWaitBits(buttonEventGroup, 0x03, pdTRUE, pdFALSE, portMAX_DELAY);

        if ((uxBits & 0x01) != 0) {
            // 'b' button event
            badMoodCount++;
            displayLCD("You have total %d bad mood today", badMoodCount);
        }

        if ((uxBits & 0x02) != 0) {
            // 'w' button event
            if (badMoodCount > 0) {
                badMoodCount--;
                displayLCD("You have total %d bad mood today", badMoodCount);
            }
        }

        if ((uxBits & 0x04) != 0) {
            // 'y' button event
            currentState = SHOW_RECORDS;
            displayLCD("Bad mood records:");
            for (int i = 0; i < MAX_RECORDS; i++) {
                printf("Day %d: %d\n", i + 1, badMoodRecords[i]);
            }
        }

        if ((uxBits & 0x08) != 0) {
            // 'g' button event
            resetDailyCount();
        }
    }
}

void vTimeTask(void *pvParameters) {
    while (1) {
        time_t now;
        struct tm midnight = {0, 1, 0, 0, 0, 0, 0, 0, 0}; // Set to midnight
        time(&now);
        struct tm *tm_now = localtime(&now);

        if (tm_now->tm_hour == midnight.tm_hour && tm_now->tm_min == midnight.tm_min) {
            // It's midnight, reset the daily count and store the record
            resetDailyCount();
            storeDailyRecord();
        }

        vTaskDelay(pdMS_TO_TICKS(60000)); // Check every minute
    }
}

int main() {
    lcdMutex = xSemaphoreCreateMutex();
    buttonEventGroup = xEventGroupCreate();

    // Set up your button interrupt handler here (similar to previous code)

    xTaskCreate(vLCDTask, "LCD Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vButtonTask, "Button Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTimeTask, "Time Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler(); // Start FreeRTOS scheduler

    while (1) {
        // This part of the code should not execute under FreeRTOS scheduler
    }

    return 0;
}
