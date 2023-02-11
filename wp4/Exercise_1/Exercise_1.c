// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 1: Interrupts on timer
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 1: The program turns on certain number of LEDs depending on measured temperature
  (e.g., 1 LED is on when the temperature is 0-10 degrees Celsius, 2 LEDs are on when the
  temperature is 11-20 degrees Celsius, etc. up to 5 LEDs).
  Definitions of temperature range provided as variables.
  The temperature gets checked periodically using interrupts. The period is defined in code.
-------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------TIMER LIBRARY----------------------------------------------*/
/* Interrupt and PWM utilities for 16 bit Timer1 on ATmega168/328
Original code by Jesse Tane for http://labs.ideo.com August 2008
Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
Modified June 2011 by Lex Talionis to add a function to read the timer
Modified June 2011 by Lex Talionis to add a function to read the timer
  - Add (long) assignments and casts to TimerOne::read() to ensure calculations involving tmp, ICR1 and TCNT1 aren't truncated
  - Ensure 16 bit registers accesses are atomic - run with interrupts disabled when accessing
  - Remove global enable of interrupts (sei())- could be running within an interrupt routine)
  - Disable interrupts whilst TCTN1 == 0.  Datasheet vague on this, but experiment shows that overflow interrupt
  flag gets set whilst TCNT1 == 0, resulting in a phantom interrupt.  Could just set to 1, but gets inaccurate
  at very short durations
  - startBottom() added to start counter at 0 and handle all interrupt enabling
  - start() amended to enable interrupts
  - restart() amended to point at startBottom()
Modiied 7:26 PM Sunday, October 09, 2011 by Lex Talionis
  - renamed start() to resume() to reflect its actual role
  - renamed startBottom() to start(). This breaks some old code that expects start to continue counting where it left off


This is free software. You can redistribute it and/or modify it under
the terms of Creative Commons Attribution 3.0 United States License. 
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 */

#ifndef TIMERONE_h
#define TIMERONE_h
#define RESOLUTION 65536                    // Timer1 is 16 bit

#include <avr/io.h>
#include <avr/interrupt.h>

class TimerOne
{
  public:

    // Properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;
    char oldSREG;                               // Variable to hold status Register while ints disabled

    // Methods
    void initialize(long microseconds=1000000);
    void start();
    void stop();
    void restart();
    void resume();
    unsigned long read();
    void pwm(char pin, int duty, long microseconds=-1);
    void disablePwm(char pin);
    void attachInterrupt(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
    void setPeriod(long microseconds);
    void setPwmDuty(char pin, int duty);
    void (*isrCallback)();
};

extern TimerOne Timer1;
#endif

#ifndef TIMERONE_cpp
#define TIMERONE_cpp

TimerOne Timer1;                                // Preinstatiate

// Interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER1_OVF_vect)                            
{
  Timer1.isrCallback();
}

void TimerOne::initialize(long microseconds)
{
  TCCR1A = 0;                                   // Clear control register A 
  TCCR1B = _BV(WGM13);                          // Set mode as phase and frequency correct pwm, stop the timer
  setPeriod(microseconds);
}

void TimerOne::setPeriod(long microseconds)
{
  long cycles = (F_CPU * microseconds) / 2000000;                                // The counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if(cycles < RESOLUTION)              clockSelectBits = _BV(CS10);              // No prescale, full xtal
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11);              // Prescale by /8
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11) | _BV(CS10);  // Prescale by /64
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12);              // Prescale by /256
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12) | _BV(CS10);  // Prescale by /1024
  else        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10);  // Request was out of bounds, set as maximum
  oldSREG = SREG;
  cli();                                                                         // Disable interrupts fo 16-bit register access   
  ICR1 = pwmPeriod = cycles;                                                     // ICR1 is TOP in p & f correct pwm mode
  SREG = oldSREG;
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));                                // Reset clock select register
  TCCR1B |= clockSelectBits;                     
}

void TimerOne::setPwmDuty(char pin, int duty)
{
  unsigned long dutyCycle = pwmPeriod;
  dutyCycle *= duty;
  dutyCycle >>= 10;
  oldSREG = SREG;
  cli();
  if(pin == 1 || pin == 9)       OCR1A = dutyCycle;
  else if(pin == 2 || pin == 10) OCR1B = dutyCycle;
  SREG = oldSREG;
}

void TimerOne::pwm(char pin, int duty, long microseconds)  // Expects duty cycle to be 10 bit (1024)
{
  if(microseconds > 0) setPeriod(microseconds);
  if(pin == 1 || pin == 9) {
    DDRB |= _BV(PORTB1);                                   // Sets data direction register for pwm output pin
    TCCR1A |= _BV(COM1A1);                                 // Activates the output pin
  }
  else if(pin == 2 || pin == 10) {
    DDRB |= _BV(PORTB2);
    TCCR1A |= _BV(COM1B1);
  }
  setPwmDuty(pin, duty);
  resume();                                                 /* Make sure the clock is running. We don't want to restart the count
                                                               in case if we're starting the second WGM and the first one is still
                                                               in the middle of a cycle */
}

void TimerOne::disablePwm(char pin)
{
  if(pin == 1 || pin == 9)       TCCR1A &= ~_BV(COM1A1);   // Clear the bit that enables pwm on PB1
  else if(pin == 2 || pin == 10) TCCR1A &= ~_BV(COM1B1);   // Clear the bit that enables pwm on PB2
}

void TimerOne::attachInterrupt(void (*isr)(), long microseconds)
{
  if(microseconds > 0) setPeriod(microseconds);
  isrCallback = isr;                                       // Register the user's callback with the real ISR
  TIMSK1 = _BV(TOIE1);                                     // Sets the timer overflow interrupt enable bit
  resume();
}

void TimerOne::detachInterrupt()
{
  TIMSK1 &= ~_BV(TOIE1);                                   // Clears the timer overflow interrupt enable bit 
}

void TimerOne::resume()
{
  TCCR1B |= clockSelectBits;
}

void TimerOne::stop()
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));          // Clears all clock selects bits
}

void TimerOne::restart()
{
  start();
}

void TimerOne::start()	        // AR addition, renamed by Lex to reflect its actual role
{
  unsigned int tcnt1;
  TIMSK1 &= ~_BV(TOIE1);        // AR added
  GTCCR |= _BV(PSRSYNC);   		// AR added - reset prescaler (NB: shared with all 16 bit timers)
  oldSREG = SREG;				// AR - save status register
  cli();						// AR - Disable interrupts
  TCNT1 = 0;                	
  SREG = oldSREG;          		// AR - Restore status register
  resume();
  do {	// Nothing -- wait until timer moved on from zero - otherwise get a phantom interrupt
	oldSREG = SREG;
	cli();
	tcnt1 = TCNT1;
	SREG = oldSREG;
  } while (tcnt1 == 0);
}

 unsigned long TimerOne::read()      // Returns the value of the timer in microseconds
 {                                   // Rember! phase and freq correct mode counts up to then down again
    unsigned long tmp;               // AR amended to hold more than 65536
    unsigned int tcnt1;				 // AR added
	oldSREG = SREG;
  	cli();							
  	tmp = TCNT1;    					
	SREG = oldSREG;
	char scale = 0;
    switch (clockSelectBits)
    {
    case 1: // No prescalse
        scale = 0;
        break;
    case 2: // x8 prescale
        scale = 3;
        break;
    case 3: // x64
        scale = 6;
        break;
    case 4: // x256
        scale = 8;
        break;
    case 5: // x1024
        scale = 10;
        break;
    }

    do {	// Nothing -- max delay here is ~1023 cycles
		oldSREG = SREG;
		cli();
		tcnt1 = TCNT1;
		SREG = oldSREG;
	} while (tcnt1==tmp); // Case if the timer has not ticked yet
	// If we are counting down add the top value to how far we have counted down
	tmp = ((tcnt1 > tmp) ? (tmp) : (long) (ICR1 - tcnt1) + (long) ICR1  );   // AR amended to add casts and reuse previous TCNT1
	return ((tmp * 1000L) / (F_CPU / 1000L)) << scale;
 }
 #endif
/*---------------------------------------------------------------------------------------------------------*/

// Constant variables for elements pins
const int LED_BLUE = 12;            // Assign blue LED to pin 12
const int LED_GREEN = 11;           // Assign green LED to pin 11
const int LED_YELLOW = 10;          // Assign yellow LED to pin 10
const int LED_ORANGE = 9;           // Assign orange LED to pin 9
const int LED_RED = 8;              // Assign red LED to pin 8
const int TEMP_SENSOR = A5;         // Assign temperature sensor to analog pin 5
const int DELAY_TIME = 500000;      // Delay period for the timer (decided to be 0.5 second)

// Constant variables for degrees Celsius
const int DEGREE_0 = 0;
const int DEGREE_10 = 10;
const int DEGREE_20 = 20;
const int DEGREE_30 = 30;
const int DEGREE_40 = 40;
const int DEGREE_50 = 50;

int convertedTemp = 0;               // Variable to store temperature converted to degrees Celsius

// Function that executes only once each time it is reset or turned on
void setup()
{
    Serial.begin(9600);             // Establish serial communication between Arduino board and other components with baud rate
    pinMode(TEMP_SENSOR, INPUT);    // Set temperature sensor as INPUT
    pinMode(LED_BLUE, OUTPUT);      // Set blue LED as output
    pinMode(LED_GREEN, OUTPUT);     // Set green LED as output
    pinMode(LED_YELLOW, OUTPUT);    // Set yellow LED as output
    pinMode(LED_ORANGE, OUTPUT);    // Set orange LED as output
    pinMode(LED_RED, OUTPUT);       // Set red LED as output
    Timer1.initialize(DELAY_TIME);  // Initialize timer with chosen delay period
    Timer1.attachInterrupt(ledsOn); // Call interrupt function
}

// Function that runs the code repeteadly
void loop()
{
    // Using inperrupts doesn't require loop() function
}

// Definition of function to turn on LEDs according to temperature sensor readings
void ledsOn()
{
    // Read temperature from sensor and use function to convert to degrees Celsius 
   convertedTemp = convertToCelsius(analogRead(TEMP_SENSOR));

   // Keep all the LED off if measured temperature is lower that 0 or higher than 50 degrees Celsius
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_ORANGE, LOW);
    digitalWrite(LED_RED, LOW);   

    // Turn on LED according to converted readings from temperature sensor
    // Case if temperature is higher tha 0 and lower or equal to 10 degrees Celsius
    if (convertedTemp >= DEGREE_0 && convertedTemp <= DEGREE_10)   
    {
        digitalWrite(LED_BLUE, HIGH);   // Turn on blue LED
        digitalWrite(LED_GREEN, LOW);   // Keep green LED off
        digitalWrite(LED_YELLOW, LOW);  // Keep yellow LED off
        digitalWrite(LED_ORANGE, LOW);  // Keep orange LED off
        digitalWrite(LED_RED, LOW);     // Keep red LED off
    }
    // Case if temperature is higher than 10 but lower or equal to 20 degrees Celsius
    else if (convertedTemp > DEGREE_10 && convertedTemp <= DEGREE_20)
    {
        digitalWrite(LED_BLUE, HIGH);   // Turn on blue LED
        digitalWrite(LED_GREEN, HIGH);  // Turn on green LED
        digitalWrite(LED_YELLOW, LOW);  // Keep yellow LED off
        digitalWrite(LED_ORANGE, LOW);  // Keep orange LED off
        digitalWrite(LED_RED, LOW);     // Keep red LED off
    }
    // Case if temperature is higher than 20 but lower or equal to 30 degrees Celsius
    else if (convertedTemp > DEGREE_20 && convertedTemp <= DEGREE_30)
    {
        digitalWrite(LED_BLUE, HIGH);   // Turn on blue LED
        digitalWrite(LED_GREEN, HIGH);  // Turn on green LED
        digitalWrite(LED_YELLOW, HIGH); // Turn on yellow LED
        digitalWrite(LED_ORANGE, LOW);  // Keep orange LED off
        digitalWrite(LED_RED, LOW);     // Keep red LED off
    }
    // Case if temperature is higher than 30 but lower or equal to 40 degrees Celsius
    else if (convertedTemp > DEGREE_30 && convertedTemp <= DEGREE_40)
    {
        digitalWrite(LED_BLUE, HIGH);   // Turn on blue LED
        digitalWrite(LED_GREEN, HIGH);  // Turn on green LED
        digitalWrite(LED_YELLOW, HIGH); // Turn on yellow LED
        digitalWrite(LED_ORANGE, HIGH); // Turn on orange LED
        digitalWrite(LED_RED, LOW);     // Keep red LED off
    }
    // Case if temperature is higher than 40 but lower or equal to 50 degrees Celsius
    else if (convertedTemp > DEGREE_40 && convertedTemp <= DEGREE_50)
    {
        digitalWrite(LED_BLUE, HIGH);   // Turn on blue LED
        digitalWrite(LED_GREEN, HIGH);  // Turn on green LED
        digitalWrite(LED_YELLOW, HIGH); // Turn on yellow LED
        digitalWrite(LED_ORANGE, HIGH); // Turn on orange LED
        digitalWrite(LED_RED, HIGH);    // Turn on red LED
    }
}

// Helper function to convert temperature sensor readings to degrees Celsius
double convertToCelsius(double sensorReadings)
{
    // Calculate temperature in degrees Celsius equivalent to measured voltage
    double convertedToCelsius = sensorReadings * 500 / 1023 - 50;
    return convertedToCelsius;
}