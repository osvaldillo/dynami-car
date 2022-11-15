#ifndef _puenteH_H
#define _puenteH_H
#include <Arduino.h>
class puenteH{
  private:
  int mot1d; //motor frontal derecho- avance hacia el frente
  int mot1i; //motor frontal derecho- avance hacia atrás
  
  int mot2d; //motor frontal izquierdo- avance hacia el frente
  int mot2i; //motor frontal izquierdo- avance hacia atrás
  
  int mot3d; //motor trasero derecho- avance hacia el frente
  int mot3i; //motor trasero derecho- avance hacia atrás

  int mot4d; //motor trasero izquierdo- avance hacia el frente
  int mot4i; //motor trasero izquierdo- avance hacia atrás
  
  int velocidad; //velocidad en pwm
  
  float mt1;
  float mt2;
  float mt3;
  float mt4;

  public:
  
  puenteH(int mot1d,int mot1i,int mot2d,int mot2i,int mot3d,int mot3i,int mot4d,int mot4i,float mt1,float mt2,float mt3,float mt4);
    
  void avanzar(int velocidad);
  void retroceder(int velocidad);
  void derecha(int velocidad);
  void izquierda(int velocidad);
  void girarDerecha(int velocidad);
  void girarIzquierda(int velocidad);
};

#endif