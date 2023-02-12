// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 3: Addressable LEDs
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 3: The program periodically measures light intensity using light sensor.
  NeoPixel ring (addressable LEDs) is used to display the temperature based on the sensor.
  Red LED gets turned on and speaker makes noise to indicate when the limit of LEDs is reached.
-------------------------------------------------------------------------------------------*/

// Include section
#include <Adafruit_NeoPixel.h>                      // NeoPixel ring library

// Constants for pins
const int RING_PIN = 13;                            // Assign NeoPixel ring to pin 13
const int RED_LED = 12;                             // Assign red LED to pin 12 to be used as indicator when limit of ring is reached
const int SPEAKER = 11;                             // Assign speaker to pin 11
const int LIGHT_SENSOR = A5;                        // Assign light sensor to analog pin A5

const int LED_NUMBER = 24;                          // Constant indicating number of LED in MeoPixel ring
const int DELAY_TIME = 100;                         // Delay period (decided to be 0.1 second)

// Creating NeoPixel object with number of LEDs and used pin
Adafruit_NeoPixel ring = Adafruit_NeoPixel(LED_NUMBER, RING_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t GREEN = ring.Color(144, 238, 144);   // RGB value of colour green

// Variable declarations
int convertedLight;                                 // Variable to store light measurements
int leds_on;                                        // Variable to store number of LED that should be turned on in NeoPixel ring

// Function that executes only once each time it is reset or turned on
void setup()
{
    Serial.begin(9600);                             // Establish serial communication between Arduino board and other components with baud rate
    pinMode(LIGHT_SENSOR, INPUT);                   // Set light sensor as input
    pinMode(RED_LED, OUTPUT);                       // Set red LED as output
    pinMode(SPEAKER, OUTPUT);                       // Set speaker as output

    ring.begin();                                   // Set NeoPixel ring as output
    ring.show();                                    // Initialize NeoPixel ring
}

// Function that runs the code repeteadly
void loop()
{
    // Read light intensity and update convertedLight variable
    convertedLight = measureLight();
    // Use map function to decide how many LEDs should be turned on according to light intensity
    leds_on = map(convertedLight, 0, 90, 1, LED_NUMBER);
    // Call function display() to turn on LEDs on NeoPixel ring, red LED or speaker according to measured light intensity
    display(leds_on);
    // Turn off all LEDs on NeoPixel ring
    ring.clear();
    // Wait for selected time interval
    delay(DELAY_TIME);
}

// Helper function to convert light sensor readings
int measureLight()
{
    // Get light reading from light sensor
    int lightRead = analogRead(LIGHT_SENSOR);
    // Map readings from light sensor to persentage ratings
    convertedLight = map(lightRead, 6, 500, 0, 75);
    // Print light intensity
    Serial.print("Light intensity: "); Serial.print(convertedLight); Serial.println("%");
    return convertedLight;
}

// Helper finction to turn on LEDs on NeoPixel ring or turn on red LED and speaker depending on light intensity
void display(int leds_on)
{
    // Case if limit of NeoPixel ring (24 LEDs) is exceeded
    if (leds_on > LED_NUMBER)
    {
        // No LEDs are on
        ring.fill(GREEN, 0, LED_NUMBER);
        ring.show();
        // Turn on red LED indicating that light intensity is outside of range to be display by LEDs of NeoPixel ring
        digitalWrite(RED_LED, HIGH);
        // Turn on speaker ndicating that light intensity is outside of range to be display by LEDs of NeoPixel ring
        digitalWrite(SPEAKER, HIGH);
    }
    // Case if limit of NeoPixel ring (24 LEDs) is not reached
    else
    {
        // Turn on LEDs from index 0 to leds_on with color blue
        ring.fill(GREEN, 0, leds_on);
        ring.show();
        // Turn off red LED indicating that light intensity is within range to be display by LEDs of NeoPixel ring
        digitalWrite(RED_LED, LOW);
        // Turn off speaker indicating that light intensity is within range to be display by LEDs of NeoPixel ring
        digitalWrite(SPEAKER, LOW);
    }
}