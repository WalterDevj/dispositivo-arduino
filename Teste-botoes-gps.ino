#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define buzzer 5
#define botaoBuzzer 8
#define botaoMensagem 7
//Definindo Buzzer na porta digital 8, o botão do buzzer na 9 e o botão de mensagem na porta 10

int pinstatus;     // declarando variável pinstatus
const int RX_PIN = 10, TX_PIN = 11; //Definindo as entradas de RX e TX do Módulo Neo-6M
const uint32_t GPS_BAUD = 9600; //Entrada padrão do NEO-6M é 9600

TinyGPSPlus gps; // Objeto da biblioteca TinyGPS++
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);

void setup() {
  pinMode(buzzer,OUTPUT);

  pinMode(botaoBuzzer, INPUT);
  pinMode(botaoMensagem, INPUT_PULLUP);
  Serial.begin(9600);
  //Define a entrada do buzzer como OUTPUT, enquanto o botão do buzzer é definido como input
  //e o botão da mensagem é definido como input (mas esse é acionado enquanto for pressionado).
  //Define a "frequência" de entrada como 9600 do monitor serial.

  gpsSerial.begin(GPS_BAUD);

  Serial.println(F("Arduino - GPS module"));
  //Definindo entrada do GPS e enviando mensagem no monitorserial

}
void loop() 
{
  if (!(digitalRead(botaoMensagem)))
    {
      digitalWrite(buzzer,HIGH);
      //Função se aonde é feita a leitura do botão do buzzer se está sendo apertado ou não 
    }
    else
    {
      digitalWrite(buzzer,LOW);
      //Caso o botão não esteja sendo apertado o buzzer ficará desligado     
    }
  //Função se, aonde enquanto o botão de mensagem for pressionado, a mensagem será enviada para o monitor seria.
  //! faz com que a mensagem seja enviada apenas quando o 


  if (digitalRead(botaoBuzzer))  {  
  
  if (gpsSerial.available() > 0) {
        // Ativando o Módulo de GPS que verifica com o uso da biblioteca TinyGPS++ latitude, altitude, velocidade e declara data e hora    
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

        Serial.println(); //
      }
}
    }
}