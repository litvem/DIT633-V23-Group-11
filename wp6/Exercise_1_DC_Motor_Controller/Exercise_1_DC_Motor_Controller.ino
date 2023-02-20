// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 6
// Exercise 1: DC motor controller
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 1: The system presents a position controller for a DC mottor.
 Task 1: The program received speed and direction through a serial (keyboard) input.
         Developed software allows Arduino to control the speed and direction of th DC motor.
 Task 2: The program consists of an interrupt routine that reads two encoder signals 
         (connected to IO ports 2 and 3). It outputs the current position in degrees of the 
         rotor on the serial monitor.
 Task 3: The program receives a desired rotor position in degrees through the serial terminal.
         Based on the current position (when the system switches on, the rotor is at 0 dergees)
         the system calculates an error term between the current and the desired positions.
         Output of the error is distplayed on the serial monitor.
         The error term is used to derive a control signal that is fed into the monitor.
---------------------------------------------------------------------------------------------*/

// Define section
// define the encoder and the motor driver input pins 
#define ENCA 2                  // Encoder A pin attached to pin 2
#define ENCB 3                  // Encoder B pin attached to pin 3
#define PWM1 5                  // Motor driver input 2 attached to pin 5
#define PWM2 6                  // Motor driver input 1 attached to pin 6


int pos = 0;                    // Position in ticks
int deg = 0;                    // Position in degrees

int degtarget = 0;              // Target position in degrees

int speed = 0;                  // Desired motor speed

int kp = 5;                     // Proportional constant for controller (tuning parameter)
int u_out = 0;                  // Output of controller

int e = 0;                      // Error
int a = 0;                      // a-encoder signal
int b = 0;                      // b-encoder signal


void setup() {
  Serial.begin(9600);           // Initialize serial communication
  // Set the pins mode
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);  

  // Pin 2 is used as an external interrupt
  // Interrupt attached on encoder A (PIN 2) when rising
  attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING );
  
  
  // Start the motor, just a tiny little bit because otherwise TinkerCad dies
  analogWrite(PWM2, 10); 
  delay(1000);                // TinkerCad bug
  analogWrite(PWM1, 10);
}

void loop() {
  // Stop the motor, but not to zero because then TinkerCad dies
  analogWrite(PWM1, 10);
  delay(1000);                // TinkerCad bug
  analogWrite(PWM2, 10);
  
  // Check if motor rotated all the way around, and reset counter
    if (pos > 2299)
    {
      deg = deg - 359;
      pos = pos - 2299;
    }
    if (pos < 0)
    {
      deg = 359 + deg;
      pos = 2299 + pos;
    }
  
  // Print current position
  Serial.print("The current position in degrees is: ");
  Serial.print(deg);
  Serial.print("\n");
   
  // Get input 
  degtarget = getInput();
  
  // Calculate initial error
  e = degtarget - deg;
    
  // Loop until error is zero
  while(e)
  {  
    // Map current position into degrees
    deg = map(pos, 0, 2299, 0, 359);
  
    // Calculate current error
    e = degtarget - deg;
    
    // Get necessary speed signal
    speed = getAction(e);
    
    // Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0)
    {
      // Case of motor does not react with too low inputs
      if (speed < 100)
        speed = 100;
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed);
    }
  
    // Rotating counter-clockwise
    else {
      // Case of motor does not react with too low inputs
      if (-speed < 100)
        speed = -100; 
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed); 
    }
  }
}

 // Function that gets the user input for the desired degree
int getInput()
{
  int ready = 0;
  char buf[3];
  int input = - 1;
  
  // Prompt user to insert value
  Serial.print("Please enter the desired position: \n");
  
  while(!ready)
  {
    ready = Serial.readBytes(buf, 3);
    input = atoi(&buf[0]);
  }
  return input;
}  

/* Function that calculates the speed of the motor
* Params: int error - the different between the desired degree and the current degree
*/
int getAction(int error)
{
  u_out = kp * error; // u_out is calculated by 5 (kp) multiplied by the difference between the desired degree and the current degree (error)
  
  if (u_out > 254)
  {
    return 255;
  }
  else if (u_out < -254)
  {
    return -255;
  }  
  else
     return u_out;
}

// Function that gets called when interrupt occurs
// The function reads the signals from the encoders and increases or decreases pos 
void ISR_readEncoder(){
  // Read the encoder signals from ENCA 
  a = digitalRead(ENCA);  
  // Read the encoder signals from ENCB
  b = digitalRead(ENCB);  
  // Case when a is greater than b, motor rotates to the right
  if (a > b)   
   // pos is increased (position in tics increases)
    pos++;    
  // Case when a is not greater that b, motor rotates to the left
  else    
    // post is decreseased (position in tics decreases)    
    pos--;
}
