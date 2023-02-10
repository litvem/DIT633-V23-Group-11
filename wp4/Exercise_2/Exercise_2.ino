
// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 2
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
  Exercise 2: The system implements an analog timer (seconds only), using interrupts on timer
  and a motor module to move (Micro Servo in TinkerCad).
  At the same time as the motor moves, the program sends the time to the serial port.
-------------------------------------------------------------------------------------------*/
// Variable declaration
int counter = 0;						    // Counter for seconds
int forward = 0;						    // Boolean for servo motor direction 

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);					// Set pin 10 to output mode
  cli();								        // Stop interrupts

  // Set timer1 interrupt at 1Hz
  TCCR1A = 0;							      // Set entire TCCR1A register to 0
  TCCR1B = 0;							      // Same for TCCR1B
  TCNT1  = 0;							      // Initialize counter value to 0
  
  // Set compare match register for 1hz increments
  OCR1A = 15624;						            // = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12);				        // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set CS12 and CS10 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);		 		      // Enable timer compare interrupt
  
  sei();								        //Allow interruptsbackward
}

ISR(TIMER1_COMPA_vect){
  timer();								      // Method called every second
}

// Loop function
void loop()
{
  if(forward){				      	// If forward equals true, turn clockwise
  	digitalWrite(10, HIGH); 	// Turn on servo motor
    digitalWrite(10,LOW);		  // Turn off servo motor
   	// This combination creates a pulse making the servo motor turn clockwise
  }
  
  if(!forward){					      // If foward is false, turn counterclockwise
   	digitalWrite(10, LOW);		// Turn off servo motor
    digitalWrite(10,HIGH);		// Turn on servo motor
    // This combination creates a pulse making the servo motor turn counterclockwise
  }
  Serial.println(counter);		// Print the second counter
  delay(1000);				      	// Delay for a second
  
}

// Method called by the interrupt every second
void timer(){
	counter ++;				      	// Second counter increase
  if(counter == 60){			  // If second equals a minute
    counter = 0;				    // Reset second counter
    forward = !forward;			// Set forward to opossite opposite boolean value			
  }
  	
}