#include <Servo.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13
Servo myservo;  
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

int pos = 0;    

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  
}

void loop() {
    if (maiorValor == 0) {
        maiorValor = ValorPortaoAoSensor();
    }

    distancia = distanciaCm();
    if (distancia < maiorValor + 2) {
        fecharPortao();
        maiorValor = 0;
        while true {
            delay(1000);
            valorAtual = distanciaCm();
            if (valorAtual < distancia + 2) {
                return false
            }
        }
    }

    if (distancia > maiorValor + 2) {
        abirPortao();
        maiorValor = 0;
        while true {
            delay(1000);
            valorAtual = distanciaCm();
            if (valorAtual < distancia + 2) {
                return false
            }
        }
    }
    delay(100);
    
}

void distanciaCm() {
    float cmMsec, inMsec;
    long microsec = ultrasonic.timing();

    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    Serial.print(", CM: ");
    Serial.println(cmMsec);
    delay(100);
    
    return cmMsec;
}

void ValorPortaoAoSensor() {
    float maiorValor;
    maiorValor = calcularDistancia();
    
    return maiorValor;
}

void abirPortao() {
    for (pos = 0; pos <= 120; pos += 1) { 
        myservo.write(pos);              
        delay(15);                       
    }
}
void fecharPortao() {
    for (pos = 120; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        delay(15);                       
    }
}