#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C LCD(0x27,16,2);

//Define las variables globales
byte DT=3;
byte CLK=2;
byte modo = 7;
byte tara = 6;
int peso_conocido[4] = {662,1000,3000,5000};  //Aqui ponemos los pesos que queremos es para calibrar la pesa es una matriz para escojer
long escala;

//pines pwm's motores 
int pwm1 = 10;
int pwm2 = 11;
int pwm3 = 12;
int pwm4 = 13;

//balanza
HX711 balanza; 

//Variables de caracteres especiales
int porcentaje = 0;
byte stand[] = {B11011, B10001, B10001, B00100, B00100, B10001, B10001, B11011};
byte front[] = {B00100, B01010, B10001, B00100, B00100, B00000, B00000, B00000};
byte left[] = {B00000, B00100, B01000, B10100, B10100, B01000, B00100, B00000};
byte right[] = {B00000, B00100, B00010, B00101, B00101, B00010, B00100, B00000};
byte back[] = {B00000, B00000, B00000, B00100, B00100, B10001, B01010, B00100};
byte turnL[] = {B00100, B01000, B11111, B01001, B00101, B00001, B01111, B00000};
byte turnR[] = {B00100, B00010, B11111, B10010, B10100, B10000, B11110, B00000};
byte porcent[]= {B00000, B00000, B11111, B11111, B11111, B11111, B00000, B00000};

char Lectura;

//velocidad de motores
int PWM = 255;

//pines motores 
//F-frontal, T-trasero
//D-derecho, I-izquierdo
//A-avance, R-retroceso
int MFDA = 24;
int MFDR = 26;
int MFIA = 28;
int MFIR = 30;
int MTDA = 32;
int MTDR = 34;
int MTIA = 36;
int MTIR = 38;

//funcion para inicializar balanza
void setupBalanza() {
  //Pregunta si se desea entrar en calibración
  if(digitalRead(modo) && digitalRead(tara))
    calibration();
  
  //Mensaje inicial en el LCD
  LCD.setCursor(1, 0);
  LCD.print("Retire el Peso");
  LCD.setCursor(1, 1);
  LCD.print(" Espere");
  delay(2000);
  balanza.set_scale(escala); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("Listo....");  
  delay(1000);
  LCD.clear();
}

void setup() {
  //inicializar variables, objetos y monitor serial
  balanza.begin(DT, CLK);
  pinMode(modo, INPUT);
  pinMode(tara, INPUT);
  Serial.begin(9600);
  for (int pin = 24; pin <= 38; pin = pin+2){
    pinMode(pin,OUTPUT);
  }
  EEPROM.get(0, escala);
  
  //secuencia de inicio
  LCD.init();
  LCD.backlight();
  LCD.createChar(0, stand);
  LCD.createChar(1, front);
  LCD.createChar(2, left);
  LCD.createChar(3, right);
  LCD.createChar(4, back);  
  LCD.createChar(5, turnL);
  LCD.createChar(6, turnR);
  LCD.createChar(7, porcent);  
  LCD.setCursor(3,0);
  LCD.print("DINAMI-CAR");
  delay(1000);
  LCD.clear();
  LCD.setCursor(1,0);
  LCD.print("Starting");
  for (int i = 3; i <= 12; i++){
    porcentaje = porcentaje + 10;
    LCD.setCursor(11, 0);
    LCD.print(porcentaje);
    LCD.setCursor(14, 0);
    LCD.print("%");
    LCD.setCursor(i,1);
    LCD.write(7);  
    delay(500);
  }
  LCD.clear();
  delay(500);

  //Secuencia de calibración de balanza
  setupBalanza();
}

void loop() {
  float peso;
  //Mide el peso de la balanza
  peso = balanza.get_units(10);
  //Muestra el resultado
  LCD.setCursor(1, 0);
  LCD.print("Peso: ");
  LCD.print(peso,0);
  LCD.println(" Gr        "); //checar 
  delay(5);
  //Botón de Tara
    if(digitalRead(tara)){  
      anti_debounce(tara);
      balanza.tare(10);  //El peso actual es considerado Tara.
    }

  if(Serial.available())
  {
    Lectura = Serial.read();
    Serial.println(Lectura);
  }
  //algoritmo dirección
  analogWrite(pwm1,PWM);
  analogWrite(pwm2,PWM);
  analogWrite(pwm3,PWM);
  analogWrite(pwm4,PWM);
  switch(Lectura){
    case 'F': avanzar();
    case 'G': retroceder();
    case 'L': izquierda();
    case 'R': derecha();
    case 'S': detenerse();
  }
  delay(10);
}


//Función de calibración y ajuste
void calibration(){
  int i = 0,cal=1;
  long adc_lecture;
  
  // Escribimos el Mensaje en el LCD
  LCD.setCursor(2, 0);
  LCD.print("Calibracion de");
  LCD.setCursor(4, 1);
  LCD.print("Balanza");
  delay(1500);
  balanza.read();
  balanza.set_scale(); //La escala por defecto es 1
  balanza.tare(20);  //El peso actual es considerado aqui
  LCD.clear();
  //Inicia el proceso de ajuste y calibración
  while(cal == 1){
    LCD.setCursor(1, 0);
    LCD.print("Peso Conocido:");
    LCD.setCursor(1, 1);
    LCD.print(peso_conocido[i]);
    LCD.print(" Gr        ");
    //Busca el peso conocido con el botón tara
    if(digitalRead(tara)){  
      anti_debounce(tara);
      i =(i>2) ? 0:i+1; //if-else en una linea
    }
    //Selecciona el peso conocido con el boton modo
    if(digitalRead(modo)){
      LCD.clear();
      LCD.setCursor(1, 0);
      LCD.print("Ponga el Peso");
      LCD.setCursor(1, 1);
      LCD.print(" Espere ...");
      delay(2000);
      //Lee el valor del HX711
      adc_lecture = balanza.get_value(100);
      //Calcula la escala con el valor leido dividido el peso conocido
      escala = adc_lecture / peso_conocido[i];
      //Guarda la escala en la EEPROM
      EEPROM.put( 0, escala );
      delay(100);
      cal = 0; //Cambia la bandera para salir del while
      LCD.clear();
    }
  }
}

//funciones para direccion
void general(int FDA; int FIA; int TDA; int TIA; int FDR; int FIR; int TDR; int TIR; int pos){
    LCD.setCursor(15,0);
    LCD.write(pos);
    digitalWrite(MFDA,FDA);
    digitalWrite(MFIA,FIA);
    digitalWrite(MTDA,TDA);
    digitalWrite(MTIA,TIA);
    digitalWrite(MFDR,FDR);
    digitalWrite(MFIR,FIR);
    digitalWrite(MTDR,TDR);
    digitalWrite(MTIR,TIR);
}
void avanzar(){general(HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, 1);}
void retroceder(){general(LOW, LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, 4);}
void izquierda(){general(HIGH, LOW, LOW, HIGH, LOW, HIGH, HIGH, LOW, 2);}
void derecha(){general(LOW, HIGH, HIGH, LOW, HIGH, LOW, LOW, HIGH, 3);}
void detenerse(){general(LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, 0);}