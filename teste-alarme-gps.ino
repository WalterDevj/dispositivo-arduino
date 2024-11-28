#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RX_PIN = 6, TX_PIN = 5;
const uint32_t GPS_BAUD = 9600; //Entrada padrão do NEO-6M é 9600


TinyGPSPlus gps; // The TinyGPS++ object
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);

int buttonpin= 9;   // Declara a variável do botão no pino digital 9
int buzzerpin= 8;  // declara a variável para armazenar o alarme no pino digital 8
int pinstatus;     // declare a variável para o estado do dos pinos
void setup() {
  pinMode(buttonpin, INPUT);
  pinMode(buzzerpin,OUTPUT);

  Serial.begin(9600);
  gpsSerial.begin(GPS_BAUD);

  Serial.println(F("Arduino - GPS module"));
}
void loop() 
{
 pinstatus=digitalRead(buttonpin);     // Lê o estado da entrada digital e armazena o valor da variável dpinstatus
 if (pinstatus==HIGH)                 // Declara condição que verifica o status da entrada, pinstatus HIGH define   
 {                                   //   que quando o botão for apertado o valor do pinstatus vai se tornar HIGH/"ativo"
  digitalWrite(buzzerpin,HIGH);     // Declara que quando estado da entrada for HIGH, então o buzzer/alarme vai ser declarado como HIGH e ele vai ser acionado
  if (gpsSerial.available() > 0) {    // Ativando o Módulo de GPS que verifica com o uso da biblioteca TinyGPS++ latitude, altitude, velocidade e declara data e hora
    if (gps.encode(gpsSerial.read())) {    //Quando o valor for diferente de 0 realiza a leitura das informações dadas pelo GPS
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
        Serial.println(F("INVALID")); //Caso não esteja recebendo a informação aparecerá uma mensagem dando como "inválido" no monitor serial
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

      Serial.println(); //
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

       // Liga o alarme (buzzer)
 }
 else
 {
  digitalWrite(buzzerpin,LOW);     // Desliga o alarme (buzzer)
 }
}
