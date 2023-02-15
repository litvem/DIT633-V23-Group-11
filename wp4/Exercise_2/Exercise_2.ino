// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 2
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
  Exercise 2: The system implements an analog timer (seconds only), using interrupts on timer
  and a motor module to move (Micro Servo in TinkerCad).
  At the same time as the motor moves, the program sends the time to the serial port.
-------------------------------------------------------------------------------------------*/

// Include section
#include <Servo.h>

// Variable declaration
Servo servo;  
int counter = 0;                      // Counter for timer2
int second = 0;                       // Second counter
int post = 0;                         // Position counter
int forward = 1;                      // Boolean for servo motor direction

// Function that executes only once each time it is reset or turned on
void setup() {
  servo.attach(10);                   // Connect the servo to pin 10
  Serial.begin(9600);                 // Establish serial communication between Arduino board and other components with baud rate
  cli();
    // Set timer2 interrupt at 8kHz
    TCCR2A = 0;                       // Set entire TCCR2A register to 0
    TCCR2B = 0;                       // Same for TCCR2B
    TCNT2  = 0;                       // Initialize counter value to 0
    // Set compare match register for 8khz increments
    OCR2A = 249;                      // = (1610^6) / (8000*8) - 1 (must be <256)
    // Turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);
    // Enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
  // Allow interrupts
  sei();      
}

// Function that runs the code repeteadly
void loop() {
  // Using inperrupts doesn't require loop() function
}

// Interrupt Service Routine function - Interrupt handler   
ISR(TIMER2_COMPA_vect)
{
  // Counter increase by 1
  counter++;            
  // Since timer2 at 8 khz is used, the counter reaches 8000 every second
  // Case if counter 8000 
  if(counter == 8000) 
  {
    // Call timer function call to print the seconds
    timer();     
    // Call funcation call to move the servo         
    move();    
    // Reset counter to 0          
    counter = 0;          
  }
} 
// Function to move the servo motor
void move() 
{
  // Case if forward direction is true
  if(forward)
  { 
    // Increase position counter
  	post++;    
  }
  // Case if forward if false
  else
  {    
    // Decrease position counter   
    post--;     
  }
  // Get servo postion. Convert the input (post) of 0 to 60 range to an output (position) of range 0-180
  int position = map(post, 0, 60, 0, 180);   
  // Set servo at position value
  servo.write(position);                     
}

// Function to track the seconds
void timer() 
{
  // Increase second counter
  second++;                 
  // Case if amount of seconds equals to 60
  if (second == 60) 
  {    
    // Print seconds count in serial motitor console   
    Serial.println(second); 
    // Set second counter to 0
    second = 0;      
    // Set forward to opossite opposite boolean value	       
    forward = !forward; 
    // Set a delay of 900 milisecond, to make sure that the timer is synchronize with the tinkecad timer    
    delay(900);             
  }
  // Case if amount of seconds doesn't equal to 60
  else
  {    
    // Print seconds count in serial motitor console                 
    Serial.println(second); 
  }
}
