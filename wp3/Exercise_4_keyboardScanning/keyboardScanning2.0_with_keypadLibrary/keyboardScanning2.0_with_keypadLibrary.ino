 /* WITH keypad.h
 * Reference: https://playground.arduino.cc/Code/Keypad/
*/

#include <Keypad.h>

const byte rows = 4; // number of rows in the keyboard
const byte cols = 4; // number of columns in the keyboard

byte colsPins[cols]={7,6,5,4}; // array of pins for each column
byte rowsPins[rows]={11,10,9,8}; // array of pings for each row

// Two dimentional char array representation of the keyboard
// use for the printing of the keyboard values that have been pressed 
char keyMatrix[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


//Instantiates a Keypad object that uses pins 11, 10, 9, 8 as row pins, and 7, 6, 5, 4 as column pins.
Keypad keypad = Keypad (makeKeymap(keyMatrix), rowsPins, colsPins, rows, cols);

// setup function to establish serial communication
void setup(){
  Serial.begin(9600); // Start the serial communication between two devices, through the USB connection
  // The Baud rate is set to 9600, meaning that the serail port is capable of transferring a maximum of 9600 bits per second.
}


void loop(){
  char key = keypad.getKey(); // Store the key that is pressed in a char called key

  if (key != NO_KEY){ // Condition that check if the key is not the empty
    Serial.println(key); // Print the pressed key
  }
}

