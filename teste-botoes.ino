#define buzzer 8 
#define botaoBuzzer 9
#define botaoMensagem 10
//Definindo Buzzer na porta digital 8, o botão do buzzer na 9 e o botão de mensagem na porta 10

#include <SoftwareSerial.h>
int pinstatus;     // declarando variável pinstatus

void setup() {
  pinMode(buzzer,OUTPUT);

  pinMode(botaoBuzzer, INPUT);
  pinMode(botaoMensagem, INPUT_PULLUP);
  Serial.begin(9600);

  //Define a entrada do buzzer como OUTPUT, enquanto o botão do buzzer é definido como input
  //e o botão da mensagem é definido como input (mas esse é acionado enquanto for pressionado).
  //Define a "frequência" de entrada como 9600 do monitor serial.
}
void loop() 
{
  if (!(digitalRead(botaoMensagem)))
    {
      Serial.println ("mensgagem");
    }
  //Função se, aonde enquanto o botão de mensagem for pressionado, a mensagem será enviada para o monitor seria.
  //! faz com que a mensagem seja enviada apenas quando o 


  if (digitalRead(botaoBuzzer))    
    {                                 
      digitalWrite(buzzer,HIGH);
    }
    //Função se aonde é feita a leitura do botão do buzzer se está sendo apertado ou não
    else
    {
      digitalWrite(buzzer,LOW);     
    }
  //Caso o botão não esteja sendo apertado o buzzer ficará desligado
}
