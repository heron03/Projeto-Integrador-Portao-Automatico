# Projeto Integrador Portão Automatico

Funcionamento
Sensores

		Sensor ultrassônico HC-SR04 - O sensor ultrassônico possui quatro conectores : VCC,Trigger,ECHO e GND , o VCC deve ser conectado a um pino de 5V , Trigger a um pino digital configurado como saída(output), ECHO a um pino digital configurado como entrada(input) e GND deve ser conectado ao pino GND do arduino.Esse sensor mede a distância através da medição do tempo que uma onda que sai do Trigger até ela colidir com um obstáculo e ser refletido e detectado pelo ECHO, mais detalhadamente o Trigger recebe 5V e fará com que o sensor envie pulsos ultrassônicos na velocidade do som no ar  de 340,29 m/s , logo em seguida o  ECHO também recebe 5V  e inicia a espera pelas ondas refletidas, imediatamente após uma onda refletida ser detectada pelo ECHO , ele é alterado para 0V e o período que ele ficou em 5V é igual ao tempo que a onda emitida demora pra ir até o obstáculo e voltar.

  Push Button -  Também conhecido como chave táctil , esse sensor  é um tipo de interruptor pulsador , ou seja só conduz corrente quando está sendo pressionado, também possui 4 conectores sem polaridades,porém deve ser conectado na diagonal para o circuito se fechar ,nesse cenário ele funciona como pull down resistor , a corrente fluirá pela menor resistência , então quando não estiver sendo pressionado o único caminho disponível será o GND para a porta digital e caso esteja sendo pressionado o circuito se fecha e irá direto para a porta digital que será o caminho com menor resistência.

Atuadores

		Servomotor- Simplificadamente, um servo motor é um motor que nos permite controlar sua posição angular através de um sinal PWM(Modulação por largura de pulso), para posicionar e manter um objeto em determinado ângulo esse atuador conta com um circuito que verifica o sinal de entrada e compara com a posição atual do eixo,existem alguns servomotores adaptados que conseguem girar indefinidamente, mas normalmente gira até 180°. Esse atuador possui 3 conectores(pinos): alimentação(5V),GND e um para pino digital(input e output). 
Arquitetura

Relatório
Introdução

Pesquisa qualitativa realizada para atender, dentre outras, a lacuna do mercado de uma população cuja expectativa de vida está aumentando, e assim, consequentemente, as futuras gerações serão cada vez mais formadas por indivíduos idosos. Estas pessoas possuem necessidades específicas em virtude de enfermidades que podem vir a ocorrer com o avançar da idade, tais quais problemas de memória. Levando em consideração o cenário de uma garagem, foi desenvolvido um protótipo de portão automático que é acionado via botão Push Button e, ao mensurar o tamanho da garagem com relação à movimentação do veículo, via sensor Ultrasonico, aciona o portão novamente para a saída do mesmo. Conforme Izabella Dutra de Abreu et.Al 1, a doença de Alzheimer (DA) é de cunho degenerativo e torna o paciente deficitário em executar até mesmo atividades básicas, necessitando do auxílio de um cuidador devido à perda de sua autonomia; em virtude disto, tendo como objetivo oferecer maior qualidade de vida e conforto à essa e outras parcelas da população, que poderão se beneficiar deste projeto.

Objetivo Geral
Auxiliar no gerenciamento de uma garagem de forma automatizada e mais segura.
Objetivo  Específico
Tornar-se uma opção viável em relação ao que já existe no mercado.
Inovar o mercado dessa área.
Adaptar-se a era digital através do uso de IoT.



Desenvolvimento
Materiais e Métodos
			Por meio da base de dados da Scielo, foi realizada um estudo da correlação entre indivíduos portadores de doenças vinculadas à degeneração memória e a perda de autonomia em virtude disto. O levantamento bibliográfico reúne a documentação do Arduíno para utilização de seus componentes, bem como um compêndio de artigos da área da saúde. Utilizando de metodologia científica com uma abordagem de cunho estatístico e de pesquisa qualitativa.
Componentes e Equipamentos 
Sensor Ultrassônico -
Servo  Motor - 
Cabos - 
Arduino - 
Caixa de papelão - 
PushButton
  

Fluxograma
Programação

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


Conclusão
Resultados
Mediante o cenário em que a pesquisa se desenvolveu, considerando a necessidade de verificar o estado do portão e controlá-lo remotamente, este projeto atendeu, em pequena escala, ao objetivo proposto 
Discussão
Os resultados encontrados no presente estudo sugerem uma melhoria para seu local de moradia , além de ajudar indivíduos com problemas de memória gera mais segurança a todos presentes no local, evitando possíveis furtos ou roubos em decorrência do ato de deixar o portão aberto.


		
Referências

https://www.vidadesilicio.com.br/arduino
https://www.revistas.usp.br/acp/article/view/16324/18036

https://www.goconqr.com/pt-BR/flowcharts/20117222/edit
https://github.com/filipeflop/Ultrasonic
https://www.arduino.cc/en/reference/servo


