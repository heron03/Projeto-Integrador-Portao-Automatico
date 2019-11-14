#define TRIGGER_PIN  12
#define ECHO_PIN     13

#include <Ultrasonic.h>
#include <Servo.h>
Servo myservo;  
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

int estadoBotao = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(7, INPUT);
}

void loop() {  
    float valorEstatico = valorEstaticoPortao();
    float ultimoValor = valorDinamicoDoportao();
    estadoBotao = digitalRead(7);
    if(estadoBotao != 0) {
        abrirPortao();
        fecharPortao();
        abrirPortao();
        Serial.println("Botão Precionado");
         int opa = true;
        while (opa) {
            Serial.println("While para quando o portão abrir e ver se o carro entrou na garagem");   
            float valorDinamico = valorDinamicoDoportao();
            if (valorDinamico - 2 < valorEstatico - 5) {
                delay(5000);
                fecharPortao();
                ultimoValor = valorEstatico;
                while (opa) {
                    Serial.println("While para ver se varia para abrir ou fechar");
                    float valorDinamico = valorDinamicoDoportao();
                    if (valorDinamico - 2 > ultimoValor) { 
                    Serial.println("BLA BLa");       
                        abrirPortao();
                        while (opa) {
                        if (valorDinamico - 2 > valorEstatico) {
                            fecharPortao();
                            ultimoValor = valorEstatico;
                            valorDinamico = valorDinamicoDoportao();
                            
                            opa = false;
                        }
                        valorDinamico = valorDinamicoDoportao();
                        delay(5000);
                        }
                        Serial.println("OPAA");
                        Serial.print(valorEstatico);
                        ultimoValor = valorEstatico;
                    }  
                    ultimoValor = valorDinamico;
                    delay(3000);
                }
            }
        }
    }
    delay(10);
}

float valorEstaticoPortao() {
    float valorEstaticoPortao = distanciaCm();
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

void abrirPortao() {
        myservo.write(140);      
        delay(1000);   
        
    Serial.print("Abrir O PORTÃO");
}
void fecharPortao() { 
        myservo.write(10);
        delay(1000);   
    Serial.print("FECHAR O PORTÃO");
}
