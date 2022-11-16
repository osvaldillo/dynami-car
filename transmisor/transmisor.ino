#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>
 
#define joyVert    A0 
#define joyHorz    A1
 
//Posicion media
int joyposVert = 512;
int joyposHorz = 512;
 
// Definir direcciones para canales de radio adrees 1 y 2 son de la libreria radiohead
#define CLIENT_ADDRESS 1   
#define SERVER_ADDRESS 2
 
// Crear una instancia del controlador de radio
RH_NRF24 RadioDriver;
 
// Establece el controlador de radio en NRF24 y la dirección del cliente en 1
RHReliableDatagram RadioManager(RadioDriver, CLIENT_ADDRESS);
 
// Declarar matriz de control de motor de 8 bits sin firmar
// 2 bytes para velocidades de motor más 1 byte para control de dirección
uint8_t motorcontrol[3]; 
 
// Definir el búfer de mensajes
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
 
void setup()
{
  
  Serial.begin(9600);
 
  // Inicialice RadioManager con los valores predeterminados: 2,402 GHz (canal 2), 2Mbps, 0dBm
  if (!RadioManager.init())
    Serial.println("init failed");
  
  // puse la dirección inicial del motor como hacia adelante
  motorcontrol[2] = 0; //[matriz]
 
}
 
void loop()
{
  // Imprimir a monitor serial como Osvaldo ver si manda mensaje
  Serial.println("Lectura de valores de control del motor ");
  
  // Lee las posiciones del Joystick X & Y
  joyposVert = analogRead(joyVert); 
  joyposHorz = analogRead(joyHorz);
 
  // INTENTAMOS Determinar si se trata de un movimiento hacia adelante o hacia atrás repito intentamos 
// leyendo el valor vertical 
// Aplique los resultados a MotorSpeed y a Direction
 
  if (joyposVert < 460)
  {
    // Esto es al revés
     // Establecer motores hacia atrás
    motorcontrol[2] = 1;
 
    //Determinar las velocidades del motor
     // Como vamos hacia atrás, necesitamos revertir las lecturas
    motorcontrol[0] = map(joyposVert, 460, 0, 0, 255);
    motorcontrol[1] = map(joyposVert, 460, 0, 0, 255);
 
  }
  else if (joyposVert > 564)
  {
    // Esto es Adelante
     // Poner Motores adelante
    motorcontrol[2] = 0;
 
    //AQUI DEBEMOS Determinar las velocidades del motor
    motorcontrol[0] = map(joyposVert, 564, 1023, 0, 255);
    motorcontrol[1] = map(joyposVert, 564, 1023, 0, 255); 
 
  }
  else
  {
    //PARADO (DETENIDO)
    motorcontrol[0] = 0;
    motorcontrol[1] = 0;
    motorcontrol[2] = 0; 
 
  }
  
  //la dirección
   // La posición Horizontal "pesará" la velocidad del motor
   // Valores para cada motor
 
  if (joyposHorz < 460)
  {
    // Mover hacia la izquierda
     // Como vamos hacia la izquierda, necesitamos invertir las lecturas
     // Asigne el número a un valor de 255 como máximo
    joyposHorz = map(joyposHorz, 460, 0, 0, 255);
 
    motorcontrol[0] = motorcontrol[0] - joyposHorz;
    motorcontrol[1] = motorcontrol[1] + joyposHorz;
 
    // No pasarnos del rango de 0-255 para las velocidades de motor
    if (motorcontrol[0] < 0)motorcontrol[0] = 0;
    if (motorcontrol[1] > 255)motorcontrol[1] = 255;
 
  }
  else if (joyposHorz > 564)
  {
    // Mover a la derecha
     // Asigne el número a un valor de 255 como máximo
    joyposHorz = map(joyposHorz, 564, 1023, 0, 255);
  
    motorcontrol[0] = motorcontrol[0] + joyposHorz;
    motorcontrol[1] = motorcontrol[1] - joyposHorz;
 
    // No exceda el rango de 0-255 para velocidades de motor
    if (motorcontrol[0] > 255)motorcontrol[0] = 255;
    if (motorcontrol[1] < 0)motorcontrol[1] = 0;      
 
  }
 
  // Ajuste para evitar "buzzing" a muy baja velocidad 
  if (motorcontrol[0] < 8)motorcontrol[0] = 0;
  if (motorcontrol[1] < 8)motorcontrol[1] = 0;
 
  //Mostrar los valores de control del motor en el monitor serie (No estoy seguro si es como le hizo osvaldo para ver si mandaba señal si esta mal la corrigen por favor 🙂
  Serial.print("Motor A: ");
  Serial.print(motorcontrol[0]);
  Serial.print(" - Motor B: ");
  Serial.print(motorcontrol[1]);
  Serial.print(" - Dirección: ");
  Serial.println(motorcontrol[2]);
  
  //Enviar un mensaje que contenga datos de control del motor a manager_server
  if (RadioManager.sendtoWait(motorcontrol, sizeof(motorcontrol), SERVER_ADDRESS))
  {
    // si sale bien esperamos una señal (respuesta)
    uint8_t len = sizeof(buf); //sizeof = Para reservar memoria se debe saber exactamente el número de bytes que ocupa cualquier estructura de datos
    uint8_t from;
    if (RadioManager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      Serial.print("obtuve respuesta de : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("No hay respuesta, ¿se está ejecutando nrf24_reliable_datagram_server?");
    }
  }
  else
    Serial.println("enviar a esperar falló");
 
  delay(100);  
}