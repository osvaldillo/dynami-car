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

#define boton1 4     //Declaramos que la variable botón esté vinculada con el pin A0
#define boton2 5     //Declaramos que la variable botón esté vinculada con el pin A1
#define boton3 6     //Declaramos que la variable botón esté vinculada con el pin A4
#define boton4 7     //Declaramos que la variable botón esté vinculada con el pin A5
#define boton5 8     //Declaramos que la variable botón esté vinculada con el pin A3

int Estado[0];
int Estado1 = 0;      //Creamos una variable que tendra un valor de 0
int Estado2 = 0;      //Creamos una variable que tendrá un valor de 0
int Estado3 = 0;      //Creamos una variable que tendrá un valor de 0
int Estado4 = 0;      //Creamos una variable que tendrá un valor de 0
int Estado5 = 0;      //Creamos una variable que tendrá un valor de 0

bool ok;

RF24 radio(9, 10);    // CE, CSN

const byte Direccion[6] = "00002"; // Canal 2 si no sirve cambiar combinación de 5# ó #No

void setup() {
  
  Serial.begin(9600);  //Inicializa el monitor serial
  radio.begin();       //Inicializa el NRF24L01
  radio.openWritingPipe(Direccion); ////Abrimos un canal de escritura
  radio.setPALevel(RF24_PA_MIN);    //Establecemos el nivel del amplificador de potencia, en este caso Minimo
  radio.stopListening();            //radio.stopListening() que configura el módulo como transmisor
                                    //radio.startListening() que configura el módulo como receptor

  
  pinMode(boton1,INPUT);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton2,INPUT);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton3,INPUT);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton4,INPUT);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton5,INPUT);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up

}
void loop() { //Inicia El blucle infinito "Lo que se encuentre en ese blucle se repetira infinitamente"

  Estado1 = digitalRead(boton1); //Indicamos que la variable "Estado1"Sea igual a la lectura del "boton1"
  Estado2 = digitalRead(boton2); //Indicamos que la variable "Estado2"Sea igual a la lectura del "boton2"
  Estado3 = digitalRead(boton3); //Indicamos que la variable "Estado3"Sea igual a la lectura del "boton3"
  Estado4 = digitalRead(boton4); //Indicamos que la variable "Estado4"Sea igual a la lectura del "boton4"
  Estado5 = digitalRead(boton5); //Indicamos que la variable "Estado5"Sea igual a la lectura del "boton5"
  
  if (Estado1 == HIGH){       //Si el pulso es alto "HIGH" o 1 se envía
    Estado[0] = 1;              //un 1
  }

  else if (Estado2 == HIGH){       //Si el pulso es alto "HIGH" o 1 se envía
    Estado[0] = 0;              //un 3
  }
  
  else if (Estado3 == HIGH){       //Si el pulso es alto "HIGH" o 1 se envía
    Estado[0] = 2;              //un 4
  } 
  
  else if (Estado4 == HIGH){     //Si el pulso es alto "HIGH" o 1 se envía
    Estado[0] = 3;              //un 6
  }
  else{
    Estado[0] = 99;
    
  }
  ok = radio.write(Estado, sizeof(Estado));
  Serial.print(ok);
  Serial.print("\t");
  Serial.println(Estado[0]);
  delay(250);
}