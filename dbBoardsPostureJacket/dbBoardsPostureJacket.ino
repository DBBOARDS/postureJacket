/*-----------------------------------------------------------------------------------------------------------
  dbBoardsPostureJacket.ino

  Summary:
    This program reads and stores the adxl345 sensor data for the z axis. If the axis is tilted too far from
    horizontal an alarm sounds using a vibe motor, an LED, and a buzzer.
  
  Utilizing:
    Sparkfun's ADXL345 Library https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library
   
  Programmer:
    Duncan Brandt @ DB Boards, LLC
    Created: Jan 14, 2018
  
  Development Environment Specifics:
    Arduino 1.6.11
  
  Hardware Specifications:
    DB Boards SPI ADXL345, DB3000
    DB Boards DigitalOut, DB2001
    Arduino Drawing Board (UNO) DB1000

  Beerware License:
    This program is free, open source, and public domain. The program is distributed as is and is not
    guaranteed. However, if you like the code and find it useful I would happily take a beer should you 
    ever catch me at the local.
*///---------------------------------------------------------------------------------------------------------

#include <SparkFun_ADXL345.h>  // https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library
ADXL345 adxl = ADXL345(10);    // USE FOR SPI COMMUNICATION, ADXL345(chipSelectPin);
int x,y,z;                     // Variable used to store accelerometer data
const int buzz = 6, vibe = 3, led = 5;       // Buzzer pinD6, vibeMotor pinD3, led pinD5
int duration = 800;            // How long(ms) the buzzer sounds before a half second pause

void setup(){                  // The setup Program runs one time at power up or after reset
  Serial.begin(9600);          // Start the serial terminal with a baudRate of 9600
  adxl.powerOn();              // Power on the ADXL345
  adxl.setRangeSetting(4);     // Range settings 2g(highest sensetivity), 4g, 8g or 16g(lowest sensetivity)
  adxl.setSpiBit(0);           // Configure the device to be in 4 wire SPI mode
  pinMode(buzz, OUTPUT);       // Setup the buzzer pin as an output
  pinMode(vibe, OUTPUT);       // Setup the vibration motor pin as an ouput
  pinMode(led, OUTPUT);        // Setup the LED pin as an output
}
void loop(){                   // The loop program follows the setup program and repeats forever
  adxl.readAccel(&x, &y, &z);  // Read the accelerometer values and store them in x, y, and z
  if(z < -50) soundAlarm();    // If the jacket leans too far forward, sound the alarm
}

void soundAlarm(){             // This function sounds the alarm with an LED a buzzer and a vibe motor
  digitalWrite(led, HIGH);     // Turn the LED on
  digitalWrite(vibe, HIGH);    // Turn the vibration motor on
  tone(buzz, 262, duration);   // Play a C note out of the buzzer
  delay(duration);             // Wait for tone to finish
  digitalWrite(led, LOW);      // Turn the LED off
  digitalWrite(vibe, LOW);     // Turn the vibe motor off
  delay(500);                  // Pause for half a second
}
