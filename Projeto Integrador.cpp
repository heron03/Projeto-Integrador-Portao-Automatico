#define TRIGGER_PIN  12
#define ECHO_PIN     13

#include <Ultrasonic.h>
#include <Servo.h>
Servo myservo;  
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);


void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {  
    float valorEstatico = valorEstaticoPortao();
    float ultimoValor = valorDinamicoDoportao();
    while (true) {
        float valorDinamico = valorDinamicoDoportao();
        Serial.print("CM: ");
        Serial.println(valorDinamico);
        Serial.print("Ultimo valor inicio ");
        Serial.println(ultimoValor);
        if (valorDinamico - 2 > valorEstatico) {
            Serial.print(" Valor Dinamico: ");
            Serial.print(valorDinamico);
            Serial.print(" Valor Estatico: ");
            Serial.print(valorEstatico);
            Serial.println("Fechar Portão");
            fecharPortao();
        }
        if (valorDinamico - 2 > ultimoValor) {
          Serial.print("AAAAAAAAAAAA ");
          Serial.println(ultimoValor);
        
            abirPortao();
            Serial.print(" Valor Dinamico: ");
            Serial.print(valorDinamico);
            Serial.print(" Ultimo Valor: ");
            Serial.print(ultimoValor);
            Serial.println("Abrir Portão");
            while (true) {
              if (valorDinamico - 2 > valorEstatico) {
                Serial.println("Fechar Portão");
                fecharPortao();
                ultimoValor = valorEstatico;
                valorDinamico = valorDinamicoDoportao();
                
                return false;
              }
              valorDinamico = valorDinamicoDoportao();
              Serial.println(valorDinamico);
              delay(5000);
            }
            Serial.println("OPAA");
            Serial.print(valorEstatico);
            ultimoValor = valorEstatico;
        } else {
          ultimoValor = valorDinamico;
          Serial.print("ultimoValor Fim: ");
          Serial.println(ultimoValor);
        }
        
        delay(3000);
    }
    
}

float valorEstaticoPortao() {
    float valorEstaticoPortao = distanciaCm();   
     Serial.print("valor Estatico   ");
     Serial.println(valorEstaticoPortao);

     return valorEstaticoPortao;
}

float valorDinamicoDoportao() {
    float valorDinamico = distanciaCm(); 

    return valorDinamico;       
}

float distanciaCm() {
    float cmMsec, inMsec;
    long microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
        
    return cmMsec;
}

void abirPortao() {
        myservo.write(140);      
        delay(1000);   
        
    Serial.print("Abrir O PORTÃO");
}
void fecharPortao() { 
        myservo.write(10);
        delay(1000);   
    Serial.print("FECHAR O PORTÃO");
}