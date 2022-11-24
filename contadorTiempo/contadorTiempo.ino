int pin = 13;
unsigned long sebas;
unsigned long t;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

unsigned long tiempo() {
  if(digitalRead(pin)){
    t = millis()-sebas;
    sebas = millis();
  }
  if(t>50){
    return(t);
  }
}

void loop(){
  Serial.println(tiempo());
  delay(50);
}
