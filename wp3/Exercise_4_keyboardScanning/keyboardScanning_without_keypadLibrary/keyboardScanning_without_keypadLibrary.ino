// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 3
// Exercise 3
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 3: The program reads the keyboard input and prints out the key number in the serial 
  monitor if a key is pressed. If no key is pressed, nothing is printed out.

  Two solutions are presented:
  1. using pinMode(),
  2. using digitalWrite().
---------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------
  Sources:
  - Alternative solution using bits:
    https://www.youtube.com/watch?v=ycV1cP_anvI
  - Arduino pin configuration documentation:
    https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)  
  - My TinkerCad sketch:
    https://www.tinkercad.com/things/aGwsjBBZzrz?sharecode=qyrUYI9xzcoOuT34ELfh3gIJCnXzNnfORbNOZoVgtII
----------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------
	SOLUTION WITHOUT LIBRARY - USING PINMODE();
----------------------------------------------------------------------------------------------*/

// Define section
#define cols 4                                // Number of columns
#define rows 4                                // Number of rows

const int colsPin[cols] = {7, 6, 5, 4};       // Set pins 4, 5, 6, 7 for keyboard output
const int rowsPin[rows] = {11, 10, 9, 8};     // Set pins 8, 9, 10, 11 for keyboard input

/* Two dimentional char array representation of the keyboard used for printing of the keyboard values that have been pressed. 
   The ASCII values used for numbers. */
char keyMatrix[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Function that will run the code only once
void setup() 
{
  Serial.begin(9600);                           // Start serial communication between two devices, through the USB connection
                                                // The Baud rate is set to 9600, meaning that the serial port is capable of transferring a maximum of 9600 bits per second.
}

// Function that runs the code repeatedly
void loop() 
{
  // Call the function that prints the char pressed in the keyboard
  readKey();
}

// Definition of function to read the pressed key
void readKey()
{
// Loop through all rows 
  for(int r = 0; r < rows; r++) 
  {
    // Function that configures a specific pin to behave either as an input or output
    pinMode(rowsPin[r], OUTPUT);                // Set the current row as OUTPUT

    // Loop through all colums
    for(int c = 0; c < cols; c++)
    {
      // digitalRead() reads the value of a pin as either LOW or HIGH
      if (digitalRead(colsPin[c]) == LOW)      // Case if the pin is LOW (i.e., button has been pressed)
      {    
        // Print pressed key maped to character in the current row (r) and column (c) from the keyboard matrix
        Serial.println(keyMatrix[r][c]); 
        
        // Delay by a second
        delay(1000);
      }
    }
    // Reset the row to INPUT mode 
    pinMode(rowsPin[r], INPUT);
  }
}

/*--------------------------------------------------------------------------------------------
	SOLUTION WITHOUT LIBRARY - USING DIGITALWRITTE();
----------------------------------------------------------------------------------------------*/

// UNCOMMENENT NEXT LINE AND LINE AT THE END TO RUN ALTERNATIVE VERSION OF THE PROGRAM
/*
// Define section
#define cols 4                                // Number of columns
#define rows 4                                // Number of rows


const int colsPin[cols] = {7, 6, 5, 4};       // Set pins 4, 5, 6, 7 for keyboard output
const int rowsPin[rows] = {11, 10, 9, 8};     // Set pins 8, 9, 10, 11 for keyboard input

// Two dimentional char array representation of the keyboard used for printing of the keyboard values that have been pressed. 
// The ASCII values used for numbers.
char keyMatrix[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Function that will run the code only once
void setup() 
{
  Serial.begin(9600);                           // Start serial communication between two devices, through the USB connection
                                                // The Baud rate is set to 9600, meaning that the serial port is capable of transferring a maximum of 9600 bits per second.
  // Loop through all rows
  for (int r = 0; r < rows; r++) 
  {
    // Set the current row as OUTPUT
  	pinMode(rowsPin[r], OUTPUT);
  }
}

// Function that runs the code repeatedly
void loop() 
{
	// Call the function that prints the char pressed in the keyboard
  readKey();
}

// Definition of function to read the pressed key
void readKey(){
// Loop through all rows 
  for(int r = 0; r  <rows; r++) 
  {
  // Send a signal through row at index r 
	digitalWrite(rowsPin[r], LOW);
    
    // Loop through all colums
    for(int c = 0; c < cols; c++)
    {
      // digitalRead() reads the value of a pin as either LOW or HIGH
      if(digitalRead(colsPin[c]) == LOW)              // Case if the pin is LOW (i.e., button has been pressed)
      { 
        // Print pressed key maped to character in the current row (r) and column (c) from the keyboard matrix
        Serial.println(keyMatrix[r][c]); 
        // Delay by a second
        delay(1000);
      }
    }
    //  Reset the row to INPUT mode 
    digitalWrite(rowsPin[r],HIGH); // reset row at index r
  }
}
*/