
// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 2
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
  Exercise 2: The system implements an analog timer (seconds only), using interrupts on timer
  and a motor module to move (Micro Servo in TinkerCad).
  At the same time as the motor moves, the program sends the time to the serial port.
-------------------------------------------------------------------------------------------*/
#include <Servo.h>

// Variable declaration
Servo servo;  
int counter = 0;  // Counter for timer2
int second = 0;   // Second counter
int post = 0;     // Position counter
int forward = 1;  // Boolean for servo motor direction

// Set up function
void setup() {
  servo.attach(10);   //Connect the servo to pin 10
  Serial.begin(9600);
  cli();
    //set timer2 interrupt at 8kHz
    TCCR2A = 0;     // set entire TCCR2A register to 0
    TCCR2B = 0;     // same for TCCR2B
    TCNT2  = 0;     //initialize counter value to 0
    // set compare match register for 8khz increments
    OCR2A = 249;// = (1610^6) / (80008) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
  sei();//allow interrupts
}

// Loop function
void loop() {

}
// Interrupt Service Routine function - Interrupt handler   
ISR(TIMER2_COMPA_vect){
    counter++;            // Counter increase by 1
  // Since timer2 with 8 khz is use when the counter reaches 8000 every second
  if(counter == 8000) {   // If counter 8000 
    timer();              // Timer function call to print the seconds
    move();               // Move funcation call to move the servo
    counter = 0;          // the counter is reset to 0 
  }
} 
// Function to move the servo motor
void move() {
  if(forward){  // If forward direction is true
  	post++;     // Increase position counter
  }else{        // If forward is false
    post--;     // Decrease position counter
  }
  int position = map(post, 0, 60, 0, 180);   // Get servo postion. Convert the input (post) of 0 to 60 range to an output (position) of range 0-180
  servo.write(position);                     // Set servo at position value
}
// Function to track the seconds
void timer() {
  second++;                 // Increase second counter
  
  if (second == 60) {       // If second equals 60 
    Serial.println(second); 
    second = 0;             // Set second counter to 0
    forward = !forward;     // Set forward to opossite opposite boolean value	
    delay(900);             // Set a delay of 900 milisecond, to make sure that the timer is synchronize with the tinkecad timer
  }else{                    // If second does not equal 60 
    Serial.println(second); 
  }
}
