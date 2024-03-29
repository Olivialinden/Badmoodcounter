# Welcome to Badmoodcounter
*Author: Olivia Linden*

*Email: chen_dinni@hotmail.com*

*Github Page: https://github.com/Olivialinden/Badmoodcounter/tree/main*

## Introduction
The Badmoodcounter is a device inspired by the self-help book on depression, *Feel Good: The New Mood Therapy* it discusses a technique called "Mental Biofeedback" for managing negative thoughts. It involves using a wrist counter that looks like a wristwatch to track and count negative self-critical thoughts throughout the day. The process includes clicking the button on the counter each time a negative thought arises and recording the daily total in a log book. Initially, the count may increase, but after a period of about three weeks, it tends to decrease. This method can help individuals become more aware of and eventually reduce their self-critical thinking, leading to improved mental well-being.

## Badmoodcounter will contain below components  
* 1pc Waveshare 2.4inch LCD TFT Display Module
* 1pc Stm32F446RE development board
* 4pcs buttons,blue,green,white, yellow
* 10pcs wires

## How to use
* 1. Upon powering on the Badmoodcounter, the LCD screen will display the following welcome message “Welcome to the Badmoodcounter, date 2023-XX-XX”.
* 2. Counting Bad Moods:
The Badmoodcounter has four buttons: blue, yellow, white, and green. To track and count negative self-critical thoughts, follow these steps:
When the operator presses the green button, the LCD will display the current count of bad moods “You have total x bad mood today ”. Here, "x" represents the current count, which starts at zero and accumulates each time the operator presses the blue button.
In case of an accidental button press, the operator can press the white button to return to the previous count.
* 3. Viewing Weekly Records:
To view a record of bad moods from the last seven days, the operator should press the yellow button. The LCD will display a list of counts for each of the seven days.

## LCD presentation

  ![image](LCDpresentation1.PNG)
  ![image](LCDpresentation2.PNG)

## Schametic:

   ![image](badmood_schametic.png)


## How to build

Run this command:

    ./run.sh compile_only badmoodcounter NO

## How to flash

You need to install OpenOCD and GDB in your system. Then:

    ./run.sh flash

## How to monitor

You need to install "picocom" in your system. Then:

    ./run.sh monitor

## Requirements

* CMake (for linux users : sudo apt install cmake)
* Make 
* gcc-arm-none-eabi
* openOCD
* GDB


 ## Installation

 To install the project, follow these steps:

  1. Clone the repository
  2. Open the project in your preferred IDE
  3. Compile and upload the code to the NUCLEO_F446RE microcontroller


## Images & gif

  ![image](badmoodcounter1.PNG)
  ![image](badmoodcounter2.PNG)


  
