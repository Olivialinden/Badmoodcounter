#ifndef BADMOODCOUNTER_H
#define BADMOODCOUNTER_H

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdbool.h>
// Global variables
uint8_t badMoodCount = 0;


int badMoodCount = 0;
int badMoodRecords[MAX_RECORDS] = {0};
int recordIndex = 0;
enum State currentState = POWER_ON;
SemaphoreHandle_t lcdMutex;
EventGroupHandle_t buttonEventGroup;

void displayLCD(const char *message) {
    xSemaphoreTake(lcdMutex, portMAX_DELAY);
    printf("%s\n", message);
    xSemaphoreGive(lcdMutex);
}

void resetDailyCount() {
    badMoodCount = 0;
    displayLCD("Daily count reset to 0");
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

// your declarations (and certain types of definitions) here

static void LCD_WelcomeMassage(void) {

    ClearLCDScreen(); // Clear the screen

    // Display the welcome message
    DisplayTextOnLCD("Welcome to the Badmoodcounter, date 2023-XX-XX");
}

void UpdateLCD(uint8_t badMoodCount) {
    // Clear the LCD screen
    ClearLCDScreen();

    // Display the bad mood count
    char message[20];
    snprintf(message, sizeof(message), "You have total %d bad mood today", badMoodCount);
    DisplayTextOnLCD(message);
}


void DisplayWeeklyRecords(uint8_t records[7]) {
    // Clear the LCD screen
    ClearLCDScreen();

    // Display the records for the last 7 days
    char message[100];
    snprintf(message, sizeof(message), "Bad Mood Records (Last 7 Days):\n");
    for (int i = 0; i < 7; i++) {
        char record[20];
        snprintf(record, sizeof(record), "Day %d: %d\n", i + 1, records[i]);
        strcat(message, record);
    }
    DisplayTextOnLCD(message);
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
#endif
