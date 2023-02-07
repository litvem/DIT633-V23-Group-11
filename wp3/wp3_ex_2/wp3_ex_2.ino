// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 3
// Exercise 2 (Custom-made sensors readings conversion without <DHT.h> library)
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 2: The system that measures the light intensity and temperature at the same time.
  The system motitor the dependency between these two measurements and warns about deviations.
  The system periodically read the temperature and light intensity (periodicy (in seconds)
  provided as a variable in the program).
  The system uses three LEDs to indicate the normal dependency (GREEN), deviation when the 
  temperature is higher that it should be given the light intensity (RED), and when the 
  temperature is lower that it should be (BLUE).
---------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------
  Sources:
  - Conversion of voltage to temperature in Celsius:
    https://docs.onion.io/omega2-arduino-dock-starter-kit/arduino-kit-reading-a-temp-sensor.html
  - More about conversion of voltage to temperature in Celsius and offset:
    https://lastminuteengineers.com/tmp36-temperature-sensor-arduino-tutorial/
  - How to map readings from light intensity sensor to persentage ratings:
    https://www.instructables.com/Light-Sensor-Photoresistor-Arduino-Tinkercad/
----------------------------------------------------------------------------------------------*/

// Constants will not change
const int GREEN_LED = 13;                       // Pin 13 connected to green LED
const int RED_LED = 12;                         // Pin 12 connected to LED
const int BLUE_LED = 11;                        // Pin 11 connected to LED
const int LIGHT_SENSOR = A0;                    // Pin A0 connected to light sensor
const int TEMP_SENSOR = A1;                     // Pin A1 connected to temperature sensor

int delayInterval = 500;                       	// Delay between sensors reads (decided to be 0.5 second)

// Function that runs the code only once
void setup() 
{
  Serial.begin(9600);                            // Establish serial communication between Arduino board and other components with baud rate
  pinMode(TEMP_SENSOR, INPUT);                   // Set temperature sensor as INPUT
  pinMode(LIGHT_SENSOR, INPUT);                  // Set light sensor as INPUT
  pinMode(GREEN_LED, OUTPUT);                    // Set green LED as output
  pinMode(RED_LED, OUTPUT);                      // Set red LED as output
  pinMode(BLUE_LED, OUTPUT);                     // Set blue LED as output
}

// Function that runs the code repeteadly
void loop() 
{
  // Get voltage reading from temperature sensor
  int measuredTemp = analogRead(TEMP_SENSOR);
  // Convert analog reading to voltage
  float voltage = (float) measuredTemp * 5.0;
  voltage /= 1024.0;
  // Print out voltage
  Serial.print("Current voltage: "); Serial.print(voltage); Serial.println(" volts");
  // Convert voltage to degrees in Celsius including the 500mV offset adjustment (to read negative temperatures)
  float convertedTemp = (voltage - 0.5) * 100;
  // Print out converted temperature
  Serial.print("Current temperature: "); Serial.print(convertedTemp); Serial.println(" degrees C");

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
    if (convertedTemp < -12)
    { 
      // Turn on green LED indicating normal dependency
      blink(GREEN_LED);
    }
    // Case if temperature is higher than -12 degrees  
    else 
    { 
      // Turn on red LED indicating that temperature is higher than it should be
      blink(RED_LED);
    }
  }
  // Case if light intensity is between 1% and 20%
  else if (convertedLight >= 1 && convertedLight <= 20)
  {
    // Case if temperature is between -12 and 0 degrees
    if (convertedTemp >= -12 && convertedTemp <= 0)
    {
      // Turn on green LED indicating normal dependency
      blink(GREEN_LED);
    }
    // Case if temperature if lower that -12 degrees 
    else if (convertedTemp < -12)
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      blink(BLUE_LED);
    }
    // Case if temperature is higher that 0
    else
    {
      // Turn on red LED indicating that temperature is higher than it should be
      blink(RED_LED);
    }
  }
  // Case if light intensity is between 21% and 60%
  else if (convertedLight >= 21 && convertedLight <= 60)
  {
    // Case if temperature is between 0 and 20 degrees
    if (convertedTemp >= 0 && convertedTemp <= 20)
    {
      // Turn on green LED indicating normal dependency
      blink(GREEN_LED);
    }
          // Case if temperature is lower that 0
    else if (convertedTemp < 0)
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      blink(BLUE_LED);
    }
    // Case if temperature is higher that 20 degrees
    else
    {
      // Turn on red LED indicating that temperature is higher than it should be
      blink(RED_LED);
    } 
  }
  // Case if light intensity is more than 61%
  else
  {
    // Case if temperature is higher that 21 degree
    if (convertedTemp >= 21)
    {
      // Turn on green LED indicating normal dependency
      blink(GREEN_LED);
    }
    // Case if temperature is lower that 21 degree
    else
    {
      // Turn on blue LED indicating that temperature is lower than it should be
      blink(BLUE_LED);
    } 
  }
  // Wait for selected interval
  delay(500);                             
}

// Helper function to turn on LED
void blink (int led)
{
  // Turn on LED
  digitalWrite(led, HIGH);
  // Wait for selected interval
  delay(delayInterval);
  // Turn off LED
  digitalWrite(led, LOW);
}