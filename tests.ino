#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RX_PIN = 6, TX_PIN = 5;
const uint32_t GPS_BAUD = 9600; //Default baud of NEO-6M is 9600


TinyGPSPlus gps; // The TinyGPS++ object
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);

int buttonpin= 9;   // declare the variable for the store button pin
int buzzerpin= 8;  // declare variable for the store buzzer pin 
int pinstatus;     // declare variable to store the pin status
void setup() {
  pinMode(buttonpin, INPUT);
  pinMode(buzzerpin,OUTPUT);

  Serial.begin(9600);
  gpsSerial.begin(GPS_BAUD);

  Serial.println(F("Arduino - GPS module"));
}
void loop() 
{
 pinstatus=digitalRead(buttonpin);    // read the status of digital pin and stores the value of pin status
 if (pinstatus==HIGH)                 // condition statement which checks the pin status, pinstatus high means       
 {                                  //   when we press the button switch values in the pin status becomes HIGH
  digitalWrite(buzzerpin,HIGH);
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

       // turn on the buzzer
 }
 else
 {
  digitalWrite(buzzerpin,LOW);     // turn off the buzzer
 }
}
