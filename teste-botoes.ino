#define buzzer 8
#define botaoBuzzer 9
#define botaoMensagem 10

#include <SoftwareSerial.h>
int pinstatus;     // declare variable to store the pin status

void setup() {
  pinMode(buzzer,OUTPUT);

  pinMode(botaoBuzzer, INPUT);
  pinMode(botaoMensagem, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() 
{
  if (!(digitalRead(botaoMensagem)))
    {
      Serial.println ("mensgagem");
    }


  if (digitalRead(botaoBuzzer))    // read the status of digital pin and stores the value of pin status
    {                                  //   when we press the button switch values in the pin status becomes HIGH
      digitalWrite(buzzer,HIGH);
    }
    else
    {
      digitalWrite(buzzer,LOW);     // turn off the buzzer
    }
}
