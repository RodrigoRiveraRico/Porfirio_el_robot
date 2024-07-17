#include <Arduino.h>
#include "velocidades.h"

//------------------Motores-----------------------------
#define in1 2     // Input 1
#define in2 4     // Input 2
#define mot1 5    // Enable 1 (motor izquierdo)
#define mot2 6    // Enable 2 (motor derecho)
#define in3 7     // Input 3
#define in4 8     // Input 4

//----------------setup--------------------------------------
void setup_movimiento() {
  const byte motores[6] = {in1, in2, mot1, mot2, in3, in4};
  for (int i = 0; i < 6; i++) {
    pinMode(motores[i], OUTPUT); // Motores como salida
  }
}

//---------------------------------------Funciones-----------------------------------
//////// En general tenemos que velo > veloc > veloci
void adelante() {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, velo - 35);
  analogWrite(mot2, velo);
}
void atras() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, velo - 35);
  analogWrite(mot2, velo);
}
void alto() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  analogWrite(mot1, 0);
  analogWrite(mot2, 0);
}




//----------Giros con ambos motores hacia adelante------------------
void izquierda11() {       //Ambos motores hacia adelante.
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloc - 10);
  analogWrite(mot2, velo);
}
void derecha11() {        //Ambos motores hacia adelante.
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, velo);
  analogWrite(mot2, veloc - 10);
}
void izquierda12() {       //Ambos motores hacia adelante.
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloc);
  analogWrite(mot2, velo);
}
void derecha12() {         //Ambos motores hacia adelante.
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, velo);
  analogWrite(mot2, veloc);
}




//---------Giros con un motor hacia atrás (giros sobre el eje del robot)--------------
void izquierda21() {     //Motor1 gira hacia atrás.
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloci + 10);
  analogWrite(mot2, veloc);
}
void derecha21() {       //Motor2 gira hacia atrás.
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, veloc);
  analogWrite(mot2, veloci + 10);
}






//---------Giros con un motor detenido (giros con una rueda como pivote)--------------
void izquierda31() {    //Motor1 gira hacia atrás. Frena en seco el Motor1
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloci);
  analogWrite(mot2, veloc);
}
void derecha31() {       //Motor2 gira hacia atrás. Frena en seco el Motor2
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, veloc);
  analogWrite(mot2, veloci);
}
void izquierda32() {     //Motor1 gira hacia atrás. Frena en seco el Motor1
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloci - 10);
  analogWrite(mot2, veloc - 10);
}
void derecha32() {       //Motor2 gira hacia atrás. Frena en seco el Motor2
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, veloc - 10);
  analogWrite(mot2, veloci - 10);
}
