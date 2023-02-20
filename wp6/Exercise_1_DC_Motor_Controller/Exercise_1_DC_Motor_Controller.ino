// define the encoder and the motor driver input pins 
#define ENCA 2   // ecnoder A pin attched to pin 2
#define ENCB 3  // ecnoder B pin attched to pin 3
#define PWM1 5  // input 2 attched to pin 5
#define PWM2 6  // input 1 attched to pin 6


int pos = 0; // Position in ticks
int deg = 0; // Position in degrees

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

int kp = 5; // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller

int e = 0; // error
int a = 0; // a-encoder signal
int b = 0; // b-encoder signal


void setup() {
 
  // start the serial
  Serial.begin(9600);
  
  // set the pins mode
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);  
  
    /*
  ==> TO DO TO DO TO DO =******** DONE ***********
  ATTACH INTERRUPT HERE.
  */

  // Pin 2 is used as an external interrupt
  // Interrupt attached on encoder A (PIN 2) when rising
  attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING );
  
  
  // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10); 
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
}

void loop() {
  // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(PWM1, 10);
  delay(1000); // TinkerCad...bug
  analogWrite(PWM2, 10);
  
  // Check if motor rotated all the way around, and reset counter
    if (pos > 2299){
      deg = deg - 359;
      pos = pos - 2299;
    }
    if (pos < 0){
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
  while(e){
    
    // Map current position into degrees
    deg = map(pos,0,2299,0,359);
  
    // Calculate current error
    e = degtarget - deg;
    
    // Get necessary speed signal
    speed = getAction(e);
    
    // Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0){
      if (speed < 100) // motor does not react with too low inputs
        speed = 100;
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed);
    }
  
    // Rotating counter-clockwise
    else{
      if (-speed < 100) // motor does not react with too low inputs
        speed = -100; 
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed); 
    }
  }
}


 // Function that gets the user input for the desired degree.
int getInput(){
  
  int ready = 0;
  char buf[3];
  int input = -1;
  
  Serial.print("Please enter the desired position: \n");
  
  while(!ready){
    ready = Serial.readBytes(buf,3);
    input = atoi(&buf[0]);
  }
 
  return input;
}  


/* Function that calculates the speed of the motor
* Params: int error   - the different between the desired degree and the current degree
*/
int getAction(int error){
    /*
  ==> TO DO TO DO TO DO = **** DONE*****
  Calculate u_out as function of the error and the kp (tuning parameter).
  */

  u_out = kp*error; // u_out is calculated by 5 (kp) multiplied by the difference between
                    // between the desired degree and the current degree (error)
  
  if (u_out > 254){
    return 255;
  }
  else if (u_out < -254){
    return -255;
  }  
  else
     return u_out;
}


// Function that gets call when interrupt
// The function reads the signals from the encoders and increases or decreases pos 
void ISR_readEncoder(){
    /*
  ==> TO DO TO DO TO DO  = ***** DONE ********
  READ THE ENCODER SIGNAL HERE.
  Read the encoder signals and increase or decrease pos accordingly.
  */

  a = digitalRead(ENCA);  // read the encoder signals from ENCA 
  b = digitalRead(ENCB);  // read the encoder signals from ENCB
  

  if (a > b)    // if a is bigger than b, the motor rotates to the right
    pos++;      // pos is increased (position in tics increases)
  else          // if a is not bigger than b the motor rotates to the left
    pos--;      // post is decreseased (position in tics decreases)
}
