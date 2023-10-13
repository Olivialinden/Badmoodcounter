# Problem Log 

## 2023-10-06
## 1.To power an STM32 Nucleo board 
To power an STM32 Nucleo board independently of a computer using USB, you can use a USB power supply or an external power source that provides power through a USB connector. Here are the steps:

USB Power Supply or Adapter:
You'll need a USB power supply or adapter. This can be a USB wall adapter, a USB power bank, or any other device that provides a stable 5V output through a USB Type-A or Type-C connector. Make sure the voltage is 5V, which is the standard USB voltage.

USB Cable:
Connect the USB cable from your USB power supply or adapter to the USB connector on your STM32 Nucleo board. The STM32 Nucleo board typically has a micro-USB connector, but some newer models might use a USB-C connector.

Power Source On:
Plug in or turn on your USB power supply or adapter. This will provide power to the STM32 Nucleo board through the USB cable.

Check Power LED:
Most STM32 Nucleo boards have a power LED indicator that will light up when the board is receiving power. Verify that this LED is illuminated, indicating that the board is powered.

Run Your Application:
With the board powered by the USB supply, you can now run your STM32 application as usual.

By following these steps, you can power your STM32 Nucleo board independently of a computer using a USB power supply or adapter. This allows the board to operate as a standalone device without relying on a computer for power. Make sure that the USB power supply or adapter you're using can provide a stable 5V output and has sufficient current capacity for your board and any connected peripherals.
## 2023-10-09

int badMoodCount = 0;
int badMoodRecords[MAX_RECORDS] = {0};
int recordIndex = 0;
enum State currentState = POWER_ON;
SemaphoreHandle_t lcdMutex;
EventGroupHandle_t buttonEventGroup;

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