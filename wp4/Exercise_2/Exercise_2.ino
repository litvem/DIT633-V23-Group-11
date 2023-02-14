
// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 2
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
  Exercise 2: The system implements an analog timer (seconds only), using interrupts on timer
  and a motor module to move (Micro Servo in TinkerCad).
  At the same time as the motor moves, the program sends the time to the serial port.
-------------------------------------------------------------------------------------------*/

// Define section
#define MOTOR 10                      // Assign motor to pin 10

// Variable declarations
int counter = 0;						          // Counter for seconds
int forward = 0;						          // Boolean for servo motor direction 

// Setup function executes only once each time it is reset or turned on
void setup()
{
  Serial.begin(9600);                   // Establish serial communication beetween Arduino board and other components with baud rate
  pinMode(MOTOR, OUTPUT);					      // Set motor pin to output
  cli();								                // Stop interrupts

  // Set timer1 interrupt at 1Hz
  TCCR1A = 0;							              // Set entire TCCR1A register to 0
  TCCR1B = 0;							              // Same for TCCR1B
  TCNT1  = 0;							              // Initialize counter value to 0

  // Set compare match register for 1hz increments
  OCR1A = 15624;						            // = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12);				        // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set CS12 and CS10 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);		 		      // Enable timer compare interrupt

  sei();								                // Allow interrupts
}

ISR(TIMER1_COMPA_vect){
  timer();								              // Method called every second
}

// Function that runs the code repeatedly
void loop()
{
  // Case if forward equals true, turn clockwise
  if(forward)
  {
    // Turn on servo motor
  	digitalWrite(MOTOR, HIGH); 	  
    // Turn off servo motor
    digitalWrite(MOTOR, LOW);		  
   	// This combination creates a pulse making the servo motor turn clockwise
  }

  // Case if foward is false, turn counterclockwise
  if(!forward)
  {					  
    // Turn off servo motor
   	digitalWrite(MOTOR, LOW);		
    // Turn on servo motor
    digitalWrite(MOTOR, HIGH);		
    // This combination creates a pulse making the servo motor turn counterclockwise
  }
  // Print second counter
  Serial.println(counter);		
  // Delay for a second
  delay(1000);				      	
}

// Function called by the interrupt every second
void timer()
{
  // Second counter increase
	counter++;	
  // Case if second equals a minute			      	
  if(counter == 60)
  {
    // Reset second counter
    counter = 0;				  
    // Set forward to opossite opposite boolean value	
    forward = !forward;					
  }
}