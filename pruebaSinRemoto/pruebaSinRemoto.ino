#define boton1 A0     //Declaramos que la variable botón esté vinculada con el pin A0
#define boton2 A1     //Declaramos que la variable botón esté vinculada con el pin A1
#define boton3 A2     //Declaramos que la variable botón esté vinculada con el pin A4
#define boton4 A3     //Declaramos que la variable botón esté vinculada con el pin A5

#define MotorFrontalDerechoA 2
#define MotorFrontalDerechoB 3
#define MotorFrontalIzquierdoA 4
#define MotorFrontalIzquierdoB 5
#define MotorTraseroDerechoA 6
#define MotorTraseroDerechoB 7
#define MotorTraseroIzquierdoA 8
#define MotorTraseroIzquierdoB 9

int enFD = 10;
int enFI = 11;
int enTD = 12;
int enTI = 13;

int pwm = 200;

void setup(){
  Serial.begin(9600);
  pinMode(boton1,INPUT_PULLUP);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton2,INPUT_PULLUP);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton3,INPUT_PULLUP);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(boton4,INPUT_PULLUP);//Declaramos el botón como entrada añadiendo una resistencia interna en Pull Up
  pinMode(enFD, OUTPUT);
  pinMode(enFI, OUTPUT);
  pinMode(enTD, OUTPUT);
  pinMode(enTI, OUTPUT);
    
}

void loop(){
  analogWrite(enFD, pwm);
  analogWrite(enFI, pwm);
  analogWrite(enTD, pwm);
  analogWrite(enTI, pwm);
  switch(botonPresionado()){
    case 0: detenerse();
    case 1: avanzar();
    case 2: retroceder();
    case 3: derecha();
    case 4: izquierda();
  }
}

int botonPresionado(){

  if(digitalRead(boton1) == HIGH){
    return 1;
  }
  else if(digitalRead(boton2) == HIGH){
    return 2;
  }
  else if(digitalRead(boton3) == HIGH){
    return 3;
  }
  else if(digitalRead(boton4) == HIGH){
    return 4;
  }

//El siguiente else se queda comentado mientras se realiza la prueba sin remoto, 
//con el fin de evitar que se detenga si no se presiona ningún botón
  /*  
  else{
    return 0;
  }
  */
}

void avanzar(){
  digitalWrite(MotorFrontalDerechoA, HIGH);
  digitalWrite(MotorFrontalDerechoB, LOW);
  digitalWrite(MotorFrontalIzquierdoA,HIGH);
  digitalWrite(MotorFrontalIzquierdoB,LOW);
  digitalWrite(MotorTraseroDerechoA, HIGH);
  digitalWrite(MotorTraseroDerechoB, LOW);
  digitalWrite(MotorTraseroIzquierdoA, HIGH);
  digitalWrite(MotorTraseroIzquierdoB, LOW);

}

void retroceder(){
  digitalWrite(MotorFrontalDerechoA, LOW);
  digitalWrite(MotorFrontalDerechoB, HIGH);
  digitalWrite(MotorFrontalIzquierdoA, LOW);
  digitalWrite(MotorFrontalIzquierdoB,HIGH);
  digitalWrite(MotorTraseroDerechoA, LOW);
  digitalWrite(MotorTraseroDerechoB, HIGH);
  digitalWrite(MotorTraseroIzquierdoA, LOW);
  digitalWrite(MotorTraseroIzquierdoB, HIGH);
}

void derecha(){
  digitalWrite(MotorFrontalDerechoA, LOW);
  digitalWrite(MotorFrontalDerechoB, HIGH);
  digitalWrite(MotorFrontalIzquierdoA, HIGH);
  digitalWrite(MotorFrontalIzquierdoB, LOW);
  digitalWrite(MotorTraseroDerechoA, HIGH);
  digitalWrite(MotorTraseroDerechoB, LOW);
  digitalWrite(MotorTraseroIzquierdoA, LOW);
  digitalWrite(MotorTraseroIzquierdoB,HIGH);
}

void izquierda(){
  digitalWrite(MotorFrontalDerechoA, HIGH);
  digitalWrite(MotorFrontalDerechoB, LOW);
  digitalWrite(MotorFrontalIzquierdoA, LOW);
  digitalWrite(MotorFrontalIzquierdoB, HIGH);
  digitalWrite(MotorTraseroDerechoA, LOW);
  digitalWrite(MotorTraseroDerechoB, HIGH);
  digitalWrite(MotorTraseroIzquierdoA, HIGH);
  digitalWrite(MotorTraseroIzquierdoB, LOW);
}

void detenerse(){
  digitalWrite(MotorFrontalDerechoA, LOW);
  digitalWrite(MotorFrontalDerechoB, LOW);
  digitalWrite(MotorFrontalIzquierdoA, LOW);
  digitalWrite(MotorFrontalIzquierdoB, LOW);
  digitalWrite(MotorTraseroDerechoA, LOW);
  digitalWrite(MotorTraseroDerechoB, LOW);
  digitalWrite(MotorTraseroIzquierdoA, LOW);
  digitalWrite(MotorTraseroIzquierdoB, LOW);    
}