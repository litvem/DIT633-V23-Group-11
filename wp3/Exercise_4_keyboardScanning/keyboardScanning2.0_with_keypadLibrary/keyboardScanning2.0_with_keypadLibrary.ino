// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 3
// Exercise 4
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 4: The program reads the keyboard input and prints out the key number in the serial 
  monitor if a key is pressed. If no key is pressed, nothing is printed out.
  The solutions is created using Keypad.h library.
---------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------
  Sources:
  - Keypad.h library documentation:
    https://playground.arduino.cc/Code/Keypad/
----------------------------------------------------------------------------------------------*/

// Include section
#include <Keypad.h>

// Define section
const byte rows = 4;                            // Number of rows in the keyboard
const byte cols = 4;                            // Number of columns in the keyboard

byte colsPins[cols] = {7, 6, 5, 4};             // Array of pins for each column
byte rowsPins[rows] = {11, 10, 9, 8};           // Array of pins for each row

/* Two dimentional char array representation of the keyboard used for printing of the keyboard values that have been pressed. 
   The ASCII values used for numbers. */
char keyMatrix[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


// Instantiate a Keypad object that uses pins 11, 10, 9, 8 as row pins, and 7, 6, 5, 4 as column pins
Keypad keypad = Keypad (makeKeymap(keyMatrix), rowsPins, colsPins, rows, cols);

// Function that will run the code only once
void setup() 
{
  Serial.begin(9600);                           // Start serial communication between two devices, through the USB connection
                                                // The Baud rate is set to 9600, meaning that the serial port is capable of transferring a maximum of 9600 bits per second.
}

// Function that runs the code repeatedly
void loop()
{
  // Store the key that is pressed in a variable key
  char key = keypad.getKey(); 

  // Condition that check if the key is not the empty
  if (key != NO_KEY)
  { 
    // Print the pressed key
    Serial.println(key); 
  }
}