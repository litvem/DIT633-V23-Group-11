// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 5
// Exercise 3: Temperature and light meter
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 3: The system based on Arduino Uno that measures the light intensity and temperature 
 at the same time.
 The system motitors the dependency between these two measurements and warns about deviations.
 The system periodically reads the temperature and light intensity (periodicy (in seconds)
 provided as a variable in the program).
 The system uses three LEDs to indicate the normal dependency (GREEN), deviation when the 
 temperature is higher that it should be given the light intensity (RED), and when the 
 temperature is lower that it should be (BLUE).
---------------------------------------------------------------------------------------------*/

// Include section
#include "DHT.h"

// Define section
#define LIGHT_SENSOR A5                         // Analog pin A5 connected to light sensor
#define DHTPIN 2                                // Pin 2 connected to DHT sensor
#define DHTTYPE DHT11                           // DHT 11

int delayInterval = 1000;                       // Delay between sensors reads (decided to be 1 second)

DHT dht(DHTPIN, DHTTYPE);                       // Initialize DHT sensor

// Function that runs the code only once
void setup() 
{
  Serial.begin(9600);                           // Establish serial communication between Arduino board and other components with baud rate
  //pinMode(TEMP_SENSOR, INPUT);                // Set temperature sensor as input
  pinMode(LIGHT_SENSOR, INPUT);                 // Set light sensor as input
  dht.begin();                                  // Start DHT sensor
  DDRB = B00111000;                             // Set pins 11-13 to 3 LEDs (pin 11 to blue LED, pin 12 to red LED, pin 13 to green LED)
}

// Function that runs the code repeteadly
void loop() 
{
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();
  // Check if any reads failed and exit early (to try again)
  if (isnan(temp)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Print out measured temperature
  Serial.print("Current temperature: "); Serial.print(temp); Serial.println(" degrees C");

  // Get light reading from light sensor
  int measuredLight = analogRead(LIGHT_SENSOR);
  // Map readings from light sensor to persentage ratings
  int convertedLight = map(measuredLight, 6, 679, 0, 100);
  // Print converted light rate
  Serial.print("Light intensity: "); Serial.print(convertedLight); Serial.println("%"); Serial.println();

  // Check sensors readings and turn on LEDs according to specifications
  // Case if light intensity is 0%
  if (convertedLight == 0)
  {
    // Case if temperature lower that -12 degrees
    if (temp < -12)
    { // Turn on green LED indicating normal dependency
      PORTB = B00100000;
    }
    // Case if temperature is higher than -12 degrees  
    else 
    { 
      // Turn on red LED indicating that temperature is higher than it should be
      PORTB = B00010000;
    }
  }
  // Case if light intensity is between 1% and 20%
  else if (convertedLight >= 1 && convertedLight <= 20)
  {
    // Case if temperature is between -12 and 0 degrees
    if (temp >= -12 && temp <= 0)
    {
      // Turn on green LED indicating normal dependency
      PORTB = B00100000;
    }
    // Case if temperature if lower that -12 degrees 
    else if (temp < -12)
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      PORTB = B00001000;
    }
    // Case if temperature is higher that 0
    else
    {
      // Turn on red LED indicating that temperature is higher than it should be
      PORTB = B00010000;
    }
  }
  // Case if light intensity is between 21% and 60%
  else if (convertedLight >= 21 && convertedLight <= 60)
  {
    // Case if temperature is between 0 and 20 degrees
    if (temp >= 0 && temp <= 20)
    {
      // Turn on green LED indicating normal dependency
      PORTB = B00100000;
    }
    // Case if temperature is lower that 0
    else if (temp < 0)
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      PORTB = B00001000;
    }
    // Case if temperature is higher that 20 degrees
    else
    {
      // Turn on red LED indicating that temperature is higher than it should be
      PORTB = B00010000;
    } 
  }
  // Case if light intensity is more than 61%
  else
  {
    // Case if temperature is higher that 21 degree
    if (temp >= 21)
    {
      // Turn on green LED indicating normal dependency
      PORTB = B00100000;
    }
    // Case if temperature is lower that 21 degree
    else
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      PORTB = B00001000;
    } 
  }
  // Wait for selected interval
  delay(delayInterval);                             
}
