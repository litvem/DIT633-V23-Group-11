// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 6
// Exercise 2: Parking assistance system
// Submission code: XXXX

/*--------------------------------------------------------------------------------------------
Exercise 2: The new parking assistance system contains an ultrasonic system as sesnsor,
 a multipurpose processing unit, a head-up display with 4 red LEDs, and a speaker.
 The system is able to detect an obstacle behind the vehicle with a maximum distance of
 200 cm and a minimum distance of 25 cm.
 The LEDs indicate how close an obstacle is to the vehicle according to following criteria:
  - 1 LED is on when the obstacle is closer than 200 cm,
  - 4 LEDs are on when the obstacle is closer than 30 cm,
  - 4 LEDs shall blink when the obstacle is closer than 25 cm.
 A tone from the speaker indicates how close the obstacle is. The tone is activated when the
 obstacle is closer than 200 cm. The closer obstacke gets to the vehicle, the louder the tone
 becomes. If the obstacle is closer than 25 cm the tone comes extemelly loud.
 Each feature (ultrasonic distance detector, LED lights, speaker) are controlled through
 individual functions for better maintainability.
---------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------
Sourses:
- Ping Ultrasonic range finder:
  https://docs.arduino.cc/built-in-examples/sensors/Ping
- Piezo skeaker:
  https://www.instructables.com/How-to-use-a-Buzzer-Arduino-Tutorial/
---------------------------------------------------------------------------------------------*/

// Define section
#define LED_1 5                     // Assign pin 5 to first LED
#define LED_2 4                     // Assing pin 4 to second LED
#define LED_3 3                     // Assign pin 3 to third LED
#define LED_4 2                     // Assign pin 2 to fourth LED
#define US_SENSOR 7                 // Assign pin 7 to ultrasonic sensor
#define SPEAKER 9                   // Assign pin 9 to speaker

#define MIN_DISTANCE 25             // Minimum distance for ultrasonic sensor (25 cm)
#define DISTANCE_30 30              // Distance of 30 cm
#define DISTANCE_100 100            // DIstance of 100 cm
#define DISTANCE_150 150            // Distance of 150 cm
#define MAX_DISTANCE 200            // Maximum distance for ultrasonic sensor (200 cm)

// Define different Hz ranges to be used in tone function of speaker
#define HZ_0 0
#define HZ_200 200
#define HZ_400 400
#define HZ_600 600
#define HZ_800 800
#define HZ_1000 1000

long duration;                      // Variable to store duration of the ping
long distance;                      // Variable to store distance from vehicle to the obstacle
int speakerTone;                    // Variable to be used in tone function of speaker (herz)

void setup()
{
    Serial.begin(9600);             // Initialize serial communication
    DDRD = B00111100;               // Set up 4 LEDs to pins 2-5
    pinMode(SPEAKER, OUTPUT);       // Set up speaker to output
    // Ultrasonic sensor is set up in measureDistance function
}

void loop()
{
    // Call function to measure distance from obstacle to the vehicle
    measureDistance();   
    // Call function to lid LEDs according to measured distance
    lidLeds();
    // Call function to change tone of speaker according to measured distance
    changeTone();           
}

// Function that detectes the distance from obstacle to the vehicle
void measureDistance()
{
    // Set ultrasonic sensor to output
    pinMode(US_SENSOR, OUTPUT);
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
    digitalWrite(US_SENSOR, LOW);
    // Wait for 2 milliseconds
    delay(2);
    // Write a one to the output to send a ping
    digitalWrite(US_SENSOR, HIGH);
    // Wait for 10 milliseconds
    delay(10);
    // Write a zero to the output to stop sending the ping
    digitalWrite(US_SENSOR, LOW);
    // Set ultrasonic sensor to iput
    pinMode(US_SENSOR, INPUT);
    // Lisening to echo returned when obstacle is reached (returned time measures in microseconds)
    duration = pulseIn(US_SENSOR, HIGH);
    // Calculate distance to detected obstacle (cm)
    distance = duration / 29 / 2;
}

// Function that lids LED according to the measured distance to the obstacle
void lidLeds()
{
    // Case when detected distance is less than 25 cm
    if (distance < MIN_DISTANCE)
    {
        // All LEDs start to blink
        PORTD = B00111100;              // Turn all 4 LEDs on
        delay(300);                     // Wait for 0,3 second
        PORTD = B00000000;              // Turn all 4 LEDs off
        delay(300);                     // Wait for 0,3 second
    }
    // Case when detected distance is less than 30 cm
    else if (distance < DISTANCE_30)
    {
        // Turn on all 4 LEDs
        PORTD = B00111100;
    }
    // Case when detected distance is bigger than or equals to 30 cm but smaller than 100 cm
    else if (distance >= DISTANCE_30 && distance < DISTANCE_100)
    {
        // Turn on 3 LEDs
        PORTD = B00111000;
    }
    // Case when detected distance is bigger than or equals to 100 cm but smaller than 150 cm
    else if (distance >= 100 && distance < 150)
    {
        // Turn on 2 LEDs
        PORTD = B00110000;
    }
    // Case when detected distance is bigger than or equals to 150 cm but smaller than maximum distance (200 cm)
    else if (distance > 150 && distance <= MAX_DISTANCE)
    {
        // Turn on 1 LED
        PORTD = B00100000;
    }
    // Case when detected distance is bigger than maximum distance (200 cm)
    else 
    {
        // Turn off all LEDs
        PORTD = B00000000;
    }
}

// Function to change intensity of speaker tone depending on detected distance to the obstacle
void changeTone()
{
    // Case whn detected distance is less than minimum distance (25 cm) indicating danger
    if (distance < MIN_DISTANCE)
    {
        // Set speaker tone to 1000 Hz
        speakerTone = HZ_1000;
    }
    // Case when detected distance is less than 30 cm
    else if (distance < DISTANCE_30)
    {
        // Set speaker tone to 800 Hz
        speakerTone = HZ_800;
    }
    // Case when detected distance is bigger than or equals to 30 cm but smaller than 100 cm
    else if (distance >= DISTANCE_30 && distance < DISTANCE_100)
    {
        // Set speaker tone to 600 Hz
        speakerTone = HZ_600;
    }
    // Case when detected distance is bigger than or equals to 100 cm but smaller than 150 cm
    else if (distance >= 100 && distance < 150)
    {
        // Set speaker tone to 400 Hz
        speakerTone = HZ_400;
    }
    // Case when detected distance is bigger than or equals to 150 cm but smaller than maximum distance (200 cm)
    else if (distance > 150 && distance <= MAX_DISTANCE)
    {
        // Set speaker tone to 200 Hz
        speakerTone = HZ_200;
    }
    // Case when detected distance is bigger than maximum distance (200 cm)
    else 
    {
        // Set speaker tone to 0 Hz
        speakerTone = HZ_0;
    }

    // Speaker produces the noise according to detected distance
    tone(SPEAKER, speakerTone); 
}