check /*
 * ALternative solution using bits
 * https://www.youtube.com/watch?v=ycV1cP_anvI
 * 
 * My tinkercad: https://www.tinkercad.com/things/aGwsjBBZzrz?sharecode=qyrUYI9xzcoOuT34ELfh3gIJCnXzNnfORbNOZoVgtII
 */

#define cols 4
#define rows 4 

const int colsPin[cols]={7,6,5,4};
const int rowsPin[rows]={11,10,9,8};

// Two dimentional char array representation of the keyboard
// use for the printing of the keyboard values that have been pressed 
char keyMatrix[rows][cols]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// setup function to establish serial communication
void setup(){
  Serial.begin(9600); // Start the serial communication between two devices, through the USB connection
  // The Baud rate is set to 9600, meaning that the serail port is capable of transferring a maximum of 9600 bits per second.
}

// loop function
void loop() {
	// loops the readKey function which prints the char pressed in the keyboard
  readKey();
}

void readKey(){
// Loop through all rows 
  for (int r=0; r<rows; r++) {
  /*
    pinMode function configure a specific pin to behave either as an input or output, in this case is set to output
    (documnetation: https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/) 
   */
    pinMode(rowsPin[r], OUTPUT); // set the current row as OUTPUT

    // Loop through all colums
    for(int c=0; c<cols; c++){
      
      //digitalRead() reads the value of a pin as either LOW or HIGH.
      if (digitalRead(colsPin[c]) == LOW) { // Check if the pin is LOW, which means that it has been pressed.
        
        // Prints the pressed key which is the character in the current row (r) and column (c) from the keyboard matrix.
        Serial.println(keyMatrix[r][c]); 
        
        // delay by a second
        delay(1000);
      }
    }
    // Reset the row as INPUT mode 
    pinMode(rowsPin[r], INPUT);
  }
}
