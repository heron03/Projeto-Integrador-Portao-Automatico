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
        abirPortao();
        abirPortao();
        Serial.println("Botão Precionado");
        while (true) {
            Serial.println("While para quando o portão abrir e ver se o carro entrou na garagem");   
            float valorDinamico = valorDinamicoDoportao();
            if (valorDinamico - 2 < valorEstatico - 5) {
                delay(5000);
                while (true) {
                    Serial.println("While para ver se varia para abrir ou fechar");
                    float valorDinamico = valorDinamicoDoportao();
                    if (valorDinamico - 2 > valorEstatico) {
                        fecharPortao();
                    }
                    if (valorDinamico - 2 > ultimoValor) {        
                        abirPortao();
                        while (true) {
                        if (valorDinamico - 2 > valorEstatico) {
                            fecharPortao();
                            ultimoValor = valorEstatico;
                            valorDinamico = valorDinamicoDoportao();
                            
                            break;
                        }
                        valorDinamico = valorDinamicoDoportao();
                        delay(5000);
                        }
                        Serial.println("OPAA");
                        Serial.print(valorEstatico);
                        ultimoValor = valorEstatico;
                    }  
                    ultimoValor = valorDinamico;
                    if(estadoBotao == 1){
                        fecharPortao();
                        
                        return false;
                    }
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