/*
 * Programa receptor..........!!!!!!
Pines para la comunicación del módulo NRF24L01.
Para el correcto funcionamiento del módulo, no alimentar a 3.3 V del 
VCC - 3.3V "Dair no lo conectes a 5 V porque podemos quemar el módulo"
GND - GND
Pines para Arduno Nano, Uno,                      Pines para Arduino Mega (sebastian)
SCK  13  //Obligatorio deberá ser el pin 13       SCK  52  //Obligatorio deberá ser el pin 52
MISO 12  //Obligatorio deberá ser el pin 12       MISO 50  //Obligatorio deberá ser el pin 50
MOSI 11  //Obligatorio deberá ser el pin 11       MOSI 51  //Obligatorio deberá ser el pin 51
CE    9  //Pueden variar previo declaracion       CE    9  //Pueden variar previa declaracion
CSN  10  //Pueden variar previo declaracion       CSN  10  //Pueden variar previa declaracion
*/ 

#include <SPI.h>      //Esta biblioteca le permite comunicarse con dispositivos SPI
#include <nRF24L01.h> //Se incluye libreria 
#include <RF24.h>     //Se incluye libreria

#define LEDrojo A0  //Declaramos que la variable LED1 esté vinculada con el pin A0
#define LEDazul A1  //Declaramos que la variable LED2 esté vinculada con el pin A1
#define LEDconectividad A2  //Declaramos que la variable LED3 esté vinculada con el pin A2

// Pines del Driver L298N
#define MotordelanteroA 5     //in3
#define MotordelanteroB 7    //in4
#define MotordeposteriorA 2   //in1
#define MotordeposteriorB 4   //in2

int enA = 3;
int enB = 6;

int Estado = 0; //Creamos una variable que tendra un valor de 0

int pwm = 200;

RF24 radio(9, 10); // CE, CSN

const byte Direccion[6] = "00002"; // Canal 2

void setup() {
  Serial.begin(9600);                    //Inicializa el monitor serial
  radio.begin();                        //Inicia radio freceuncia
  radio.openReadingPipe(1, Direccion); //Inicializa el objeto de radio previamente configurado "Dirección"
  radio.setPALevel(RF24_PA_MIN);      //Establecemos el nivel del amplificador de potencia, en este caso Minimo
  radio.startListening();            //radio.startListening() que configura el módulo como receptor.
                                    //radio.stopListening() que configura el módulo como transmisor.
                           
  pinMode(LEDrojo, OUTPUT);           // Declaramos como salida
  pinMode(LEDazul, OUTPUT);           // Declaramos como salida
  pinMode(LEDconectividad, OUTPUT);   // Declaramos como salida
  pinMode(MotordeposteriorA,OUTPUT);  // Declaramos como salida
  pinMode(MotordeposteriorB,OUTPUT);  // Declaramos como salida
  pinMode(MotordelanteroA,OUTPUT);    // Declaramos como salida
  pinMode(MotordelanteroB,OUTPUT);    // Declaramos como salida
  

}
void loop() { //Inicia El blucle infinito "Lo que se encuentre en ese bucle se repetira infinitamente"
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  /*if (!radio.available()){ //Si radio no esta disponible 
    digitalWrite(LEDconectividad, LOW); // apagar led
  }
  else{                          //si no
      digitalWrite(LEDconectividad, HIGH); //encender led
  }*/
  Serial.println(radio.available());
  while (radio.available()){   //Si radio esta disponible 
    radio.read(&Estado, sizeof(Estado)); //leer datos y almacenarlos en estado
    Serial.println(Estado); //imprimir en el monitor serial la variable EStado
    switch(Estado){
      case 0: retroceder();
      case 1: avanzar();
      case 2: giroIzquierda();
      case 3: giroDerecha();
    }
    /*if (Estado == 1) {       //Sí, ingresa el número 1
      digitalWrite(LEDrojo, LOW); // se manda un pulso bajo "LOW" "Led Apagado"
      
    }
    
    else  if (Estado == 0) { //Sí, ingresa el número 0
      digitalWrite(LEDrojo, LOW); // se manda un pulso bajo "LOW" "Led Apagado"
      
    }
    
    else if (Estado == 3) { //Sí, ingresa el número 3 
      digitalWrite(LEDazul, LOW); // se manda un pulso bajo "LOW" "Led Apagado"
      digitalWrite(LEDrojo, LOW); // se manda un pulso bajo "LOW" "Led Apagado"
      
    }
    
    else  if (Estado == 2) { //Sí, ingresa el número 2 
      digitalWrite(LEDazul, HIGH); // se manda un pulso alto "HIGH" "Led Encendido"
      digitalWrite(LEDrojo, LOW); // se manda un pulso bajo "LOW" "Led Apagado"
      
      }*/
  }
  detenerse();
  /*
  //Alto
  else if (Estado == 4) {  //Sí, ingresa el número 4 
  digitalWrite(MotordelanteroA,LOW);  // se manda un pulso bajo "LOW" al MotordelanteroA "Apagado"
  }
  //Izquierda
  else  if (Estado == 5) { //Sí, ingresa el número 5 
  digitalWrite(MotordelanteroA,HIGH); // se manda un pulso bajo "LOW" al MotordelanteroA "Encendido"
  digitalWrite(MotordelanteroB,LOW);  // se manda un pulso alto "HIGH" al MotordelanteroB "Apagado"
  }
  //Alto
  else if (Estado == 6) { //Sí, ingresa el número 6 
  digitalWrite(MotordelanteroB,LOW); // se manda un pulso bajo "HIGH" al MotordelanteroB "Apagado"

  }
  //Derecha
  else  if (Estado == 7) { //Sí, ingresa el número 7 
  digitalWrite(MotordelanteroA,LOW);  // se manda un pulso bajo "LOW" al MotordelanteroA "Apagado"
  digitalWrite(MotordelanteroB,HIGH); // se manda un pulso alto "HIGH" al MotordelanteroB "Encendido"
  }
  //Giro de 360° no se si funcione checar
  else  if (Estado == 9) { //Sí, ingresa el número 9 
  digitalWrite(MotordelanteroA,LOW);  // se manda un pulso bajo "LOW" al MotordelanteroA "Apagado"
  digitalWrite(MotordelanteroB,HIGH); // se manda un pulso alto "HIGH" al MotordelanteroB "Encendido"
  digitalWrite(LEDazul, HIGH);        // se manda un pulso alto "HIGH" "Led Encendido"
  digitalWrite(MotordeposteriorA,HIGH); // se manda un pulso alto "HIGH" al MotordeposteriorA "Encendido"
  digitalWrite(MotordeposteriorB,LOW); //se manda un pulso bajo "LOW" al MotordeposteriorB "Apagado"
  delay(5000); 
  }
  */
}

void avanzar(){
  digitalWrite(MotordeposteriorA,HIGH);
  digitalWrite(MotordeposteriorB,LOW);
  digitalWrite(MotordelanteroA,HIGH);
  digitalWrite(MotordelanteroB,LOW);
}

void retroceder(){
  digitalWrite(MotordeposteriorA,HIGH);
  digitalWrite(MotordeposteriorB,LOW);
  digitalWrite(MotordelanteroA,LOW);
  digitalWrite(MotordelanteroB,HIGH);  
}

void giroDerecha(){
  digitalWrite(MotordeposteriorA,LOW);
  digitalWrite(MotordeposteriorB,HIGH);
  digitalWrite(MotordelanteroA,HIGH);
  digitalWrite(MotordelanteroB,LOW);
}

void giroIzquierda(){
  digitalWrite(MotordeposteriorA,LOW);
  digitalWrite(MotordeposteriorB,HIGH);
  digitalWrite(MotordelanteroA,LOW);
  digitalWrite(MotordelanteroB,HIGH);  
}

void detenerse(){
  digitalWrite(MotordeposteriorA,LOW);
  digitalWrite(MotordeposteriorB,LOW);
  digitalWrite(MotordelanteroA,LOW);
  digitalWrite(MotordelanteroB,LOW);
    
}