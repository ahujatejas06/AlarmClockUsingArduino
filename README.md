# Alarm Clock Using Arduino
This repo contains Arduino code and schematics for wiring and setting up an alarm clock with Arduino. Further, a basic documentation is provided here.

## Requirements
* Arduino Uno
* 1 x Buzzer
* 1 x 330 ohms resistor
* 1 x 16X2 LCD Display
* 1 x 1307 RTC
* Program from this repo (File named Program.ino)
* Arduino IDE (Latest version can be downloaded here https://www.arduino.cc/en/main/software)
* Time Library for arduino (https://github.com/PaulStoffregen/Time)
* DS1307 Library for arduino (https://github.com/PaulStoffregen/DS1307RTC)
* LiquidCrystalLCD library (should be preinstalled in the IDE)
* Schematics from this repo
* Jumper Cables
* USB type A to type B cable for arduino 

## How to set up?
Follow the schematic diagram.

## How to set time on the RTC?
Open the example code named SetTime from the DS1307 library that you installed earlier.

## What to do next?
Compile and upload the Program.ino file and you are ready to rock with your new alarm clock.

## How to configure buttons?
* Here are the pin numbers with buttons
	* setb ---> A2 (Default)
		* Used for toggling the settings for alarm timings.
		* Used for shifting to the next menu in the alarm setting menu.

	* button ---> 8 (Default)
		* Used for toggling alarm 1 and 3.
		* Used for incrementing the hour, minutes, seconds by 1 in the alarm setting mode.
		* Used for toggling alarm 2 when pressed simultaneously with brightnessbutton.

	* brightnessbutton ---> 7 (Default)
		* Used for toggling night mode.
		* Used for decrementing the hour, minutes, seconds by 1 in the alarm setting mode.

## How do I open the alarm setting menu?
You can do so by pressing the setb button when the Alarm number with a the state of alarm(On or Off) is displayed


