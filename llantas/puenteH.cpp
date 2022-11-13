#include "puenteH.h"
  puenteH::puenteH(int mot1d, int mot1i, int mot2d, int mot2i, int mot3d, int mot3i, int mot4d, int mot4i, float mt1, float mt2, float mt3, float mt4){
    this-> mot1d = mot1d;
    this-> mot1i = mot1i;
    this-> mot2d = mot2d;
    this-> mot2i = mot2i;
    this-> mot3d = mot3d;
    this-> mot3i = mot3i;
    this-> mot4d = mot4d;
    this-> mot4i = mot4i;
    this-> mt1 = mt1;
    this-> mt2 = mt2;
    this-> mt3 = mt3;
    this-> mt4 = mt4;
  }
  void puenteH::avanzar(int velocidad){
    digitalWrite(mot1d, 1);
    digitalWrite(mot1i, 0);
    digitalWrite(mot2d, 1);
    digitalWrite(mot2i, 0);
    digitalWrite(mot3d, 1);
    digitalWrite(mot3i, 0);
    digitalWrite(mot4d, 1);
    digitalWrite(mot4i, 0);
    analogWrite(mt1, velocidad);
    analogWrite(mt2, velocidad);
    analogWrite(mt3, velocidad);
    analogWrite(mt4, velocidad);
    }
  void puenteH::retroceder(int velocidad){
    
    digitalWrite(mot1d, 0);
    digitalWrite(mot1i, 1);
    digitalWrite(mot2d, 0);
    digitalWrite(mot2i, 1);
    digitalWrite(mot3d, 0);
    digitalWrite(mot3i, 1);
    digitalWrite(mot4d, 0);
    digitalWrite(mot4i, 1);
    analogWrite(mt1, velocidad);
    analogWrite(mt2, velocidad);
    analogWrite(mt3, velocidad);
    analogWrite(mt4, velocidad);
  }
  void puenteH::derecha(int velocidad){
    digitalWrite(mot1d, 1);
    digitalWrite(mot1i, 0);
    digitalWrite(mot2d, 0);
    digitalWrite(mot2i, 1);
    digitalWrite(mot3d, 0);
    digitalWrite(mot3i, 1);
    digitalWrite(mot4d, 1);
    digitalWrite(mot4i, 0);
    analogWrite(mt1, velocidad);
    analogWrite(mt2, velocidad);
    analogWrite(mt3, velocidad);
    analogWrite(mt4, velocidad);
  }
  void puenteH::izquierda(int velocidad){
    digitalWrite(mot1d, 0);
    digitalWrite(mot1i, 1);
    digitalWrite(mot2d, 1);
    digitalWrite(mot2i, 0);
    digitalWrite(mot3d, 1);
    digitalWrite(mot3i, 0);
    digitalWrite(mot4d, 0);
    digitalWrite(mot4i, 1);
    analogWrite(mt1, velocidad);
    analogWrite(mt2, velocidad);
    analogWrite(mt3, velocidad);
    analogWrite(mt4, velocidad);
  }
  void puenteH::girarDerecha(int velocidad){
    // digitalWrite(mot1d, );
    // digitalWrite(mot1i, );
    // digitalWrite(mot2d, );
    // digitalWrite(mot2i, );
    // digitalWrite(mot3d, );
    // digitalWrite(mot3i, );
    // digitalWrite(mot4d, );
    // digitalWrite(mot4i, );
    // analogWrite(mt1, velocidad);
    // analogWrite(mt2, velocidad);
    // analogWrite(mt3, velocidad);
    // analogWrite(mt4, velocidad);
  }
  void puenteH::girarIzquierda(int velocidad){
    // digitalWrite(mot1d, );
    // digitalWrite(mot1i, );
    // digitalWrite(mot2d, );
    // digitalWrite(mot2i, );
    // digitalWrite(mot3d, );
    // digitalWrite(mot3i, );
    // digitalWrite(mot4d, );
    // digitalWrite(mot4i, );
    // analogWrite(mt1, velocidad);
    // analogWrite(mt2, velocidad);
    // analogWrite(mt3, velocidad);
    // analogWrite(mt4, velocidad);
  }