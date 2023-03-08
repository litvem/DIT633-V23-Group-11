// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 5
// Exercise 1: Setup
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 1: Simple system on Arduino Uno, which uses one LED blink periodically (e.g., 
 once a second).
 Second LED is on when button is pressed, and it's of when the button is not pressed.
-------------------------------------------------------------------------------------------*/

// Define section
#define blink_led 13                  // LED that blinks is connected to pin 13
#define button_led 12                 // LED that is on when the button is pressed is connected to pin 12
#define button 2                      // Button is connected to pin 2

int blinkingInterval = 1000;          // Time delay for blinking LED (1 second in our case) 
int buttonState = 0;                  // Initial state of the button (0 indicaes that the button is not pressed)

// Setup function executes only once each time it is reset or turned on
void setup()
{
   pinMode(blink_led, OUTPUT);        // Set pin for blinking LED to output
   pinMode(button_led, OUTPUT);       // Set pin for LED actived by pressing the button to output
   pinMode(button, INPUT);            // Set pin for the button to input
}

// Function that runs infinitely to run the code
void loop()
{
   digitalWrite(blink_led, HIGH);     // Turn on pin for blinking LED
   delay(blinkingInterval);           // Pause for 1 second
   digitalWrite(blink_led, LOW);      // Turn off pin for blinking LED
   delay(blinkingInterval);           // Pause for 1 second

   // Read the state of button
   buttonState = digitalRead(button);
   // Check if button is pressed 
   // If it is, buttonState is HIGH
   if (buttonState == 1)
   { 
      // Turn the LED on
      digitalWrite(button_led, HIGH); 
    } // If it not pressed
    else                              
    {
      // Nothing happens
      digitalWrite(button_led, LOW);
    }
}
