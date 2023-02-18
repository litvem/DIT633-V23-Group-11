// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 5
// Exercise 2: Temperature meter
// Submission code: XXXX

/*----------------------------------------------------------------------------------------------
Exercise 2: The system based on Arduino Uno that measures the temperature and lids LEDs.
 5 LEDs are used to indicate measured temperature and get turned on based on following criteria:
 measured temperature is 0-10 degrees Celsius -> 1 LED turns on,
 measured temperature is 11-20 degrees Celsius -> 2 LEDs turn on,
 measured temperature is 21-30 degrees Celsius -> 3 LEDs turn on,
 measured temperature is 31-40 degrees Celsius -> 4 LEDs turn on,
 measured temperature is 41-50 degrees Celsius -> 5 LEDs turn on.
 Temperature ranges are defined as variables.
-----------------------------------------------------------------------------------------------*/

// Include section
#include "DHT.h"

// Define section
#define DHTPIN 2                        // Pin 2 connected to DHT sensor
#define DHTTYPE DHT11                   // DHT 11

const int WAIT_TIME = 2000;             // Delay between sensors reads (decided to be 2 seconds)

// Constants for temperature ranges
const int TEMP_0 = 0;
const int TEMP_10 = 10;
const int TEMP_20 = 20;
const int TEMP_30 = 30;
const int TEMP_40 = 40;
const int TEMP_50 = 50;

DHT dht(DHTPIN, DHTTYPE);               // Initialize DHT sensor

// Function that runs the code only once
void setup() 
{
  Serial.begin(9600);                   // Establish serial communication between Arduino board and other components with baud rate
  dht.begin();                          // Start DHT sensor
  DDRB = B00111110;                     // Set up 5 LEDs to pins 9-13
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

  // Case if measured temperature is in the range 0-10 degrees Celsius
  if (temp >= TEMP_0 && temp <= TEMP_10)
  {
    // Turn 1 LED on
    PORTB = B00100000;
  }
  // Case if measured temperature is in the range 11-20 degrees Celsius
  else if (temp > 10 && temp <= 20)
  {
    // Turn 2 LEDs on
    PORTB = B00110000;
  }
  // Case if measured temperature is in the range 21-30 degrees Celsius
  else if (temp > 20 && temp <= 30)
  {
    // Turn 3 LEDs on
    PORTB = B00111000;
  }
  // Case if measured temperature is in the range 31-40 degrees Celsius
  else if (temp > 30 && temp <= 40)
  {
    // Turn 4 LEDs on
    PORTB = B00111100;
  }
  // Case if measured temperature is in the range 41-50 degrees Celsius
  else if (temp > 40 && temp <= 50)
  {
    // Turn 5 LEDs on
    PORTB = B00111110;
  }
  // Case when measured temperature is less that 0 or higher than 50 degrees Celcius
  else
  {
    // Turn all LEDs off
    PORTB = B00000000;
  }
  // Wait for selected interval
  delay(WAIT_TIME);
}
