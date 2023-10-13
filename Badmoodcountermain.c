#include"Badmoodcounter.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>

// Define the LCD display and button pins
#define LCD_CS_PIN      GPIO_PIN_4
#define LCD_DC_PIN      GPIO_PIN_5
#define LCD_RST_PIN     GPIO_PIN_6
#define BUTTON_BLUE_PIN GPIO_PIN_0
#define BUTTON_GREEN_PIN GPIO_PIN_1
#define BUTTON_WHITE_PIN GPIO_PIN_2
#define BUTTON_YELLOW_PIN GPIO_PIN_3

// Function prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void LCD_Init(void);

// Global variables
uint8_t badMoodCount = 0;

// FreeRTOS tasks
void LCD_Display_Task(void *pvParameters) {

    while (1) {
        UpdateLCD(badMoodCount);// Update LCD with bad mood count
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
}

void Button_Press_Task(void *pvParameters) {

    while (1) {
        // Button press handling
        if (HAL_GPIO_ReadPin(GPIOA, BUTTON_BLUE_PIN) == GPIO_PIN_RESET) {
            // Blue button pressed, increment bad mood count
            badMoodCount++;
            HAL_Delay(100); // Debounce delay
            UpdateLCD(badMoodCount);
        } else if (HAL_GPIO_ReadPin(GPIOA, BUTTON_WHITE_PIN) == GPIO_PIN_RESET) {
            // White button pressed, decrement bad mood count (if not already zero)
            if (badMoodCount > 0) {
                badMoodCount--;
                HAL_Delay(100); // Debounce delay
                UpdateLCD(badMoodCount);
            }
        } else if (HAL_GPIO_ReadPin(GPIOA, BUTTON_YELLOW_PIN) == GPIO_PIN_RESET) {
            DisplayWeeklyRecords();// Yellow button pressed, display weekly records (implement this)
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); // Delay for 50 ms
    }
}

int main(void) {
    // SPI init?????????
    
    // HAL initialization
    HAL_Init();
    // Initialize button GPIO pins
    MX_GPIO_Init();
   // Configure the system clock
    SystemClock_Config();
    // Initialize LCD display
    LCD_Init();
    if (HAL_GPIO_ReadPin(GPIOA, BUTTON_GREEN_PIN) == GPIO_PIN_RESET) {
            // Green button pressed,display welcome message
        LCD_WelcomeMassage();
    }
    // Create FreeRTOS tasks
    xTaskCreate(LCD_Display_Task, "LCD_Display", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(Button_Press_Task, "Button_Press", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // We should never get here
    while (1) {
    }
}

// Implement the LCD_Init() function to initialize the LCD display
static void LCD_Init(void) {
    // ...
}

// Implement the GPIO initialization function (MX_GPIO_Init) to configure button pins, LCD pins, etc.
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO peripheral clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure button pins as input with pull-up
    GPIO_InitStruct.Pin = BUTTON_BLUE_PIN | BUTTON_WHITE_PIN | BUTTON_YELLOW_PIN| BUTTON_GREEN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // ...
}

// Implement the SystemClock_Config() function for system clock configuration
void SystemClock_Config(void) {
    // ...
}

// Implement LCD update function
// ...
