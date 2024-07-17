/*
   Seguidor de línea.

   Queremos que el robot siga una línea blanca (1.9cm) sobre un fondo negro, así se debe de
   cumplir lo siguiente:
   1) Cuando el sensor 3 (centro) detecte blanco que los dos motores avancen hacia adelante.
   2) Cuando el sensor 4 de la derecha  y el 3 detecten blanco que de vuelta ligeramente hacia la derecha.
   3) Cuando el sensor 2 de la izquierda y el 3 detecten blanco que de vuelta ligeramente hacia la izquierda.
   4) Cuando el sensor 1 y 2 detecten blanco, gira a la izquierda.
   5) Cuando el sensor 4 y 5 detecten blanco, gira a la derecha.

               //--------------------Lecturas----------------------------//
   //--Función--//-Sensor 1-//-Sensor 2-//-Sensor 3-//-Sensor 4-//-Sensor 5//
     Adelante                               >= 800
     Derecha1                               >= 800     >= 750
     Derecha2                                          >= 750      >=800
     Derecha3       >= 300     >= 800       >= 800
     Izquierda1                >= 800       >= 800
     Izquierda2     >= 300     >= 800
     Izquierda3                                        >= 750      >=800
   //---------------------------------------------------------------------//


   Valores tomados a la 1:57 pm
   //---------00100--------   Adelante
     223  740 992 641 593
     182  745 991 662 607       //Pegado a la ventana
   //---------01100--------   Izquierda
     216  987 987 591 498
     157  748 991 641 608       //Pegado a la ventana
   //---------11000--------  Izquierda
     966  961 591 544 570
     592  994 570 550 418
     478  972 604 638 643       //Pegado a la ventana
   //---------00110-------- Derecha
     166  683 990 973 701
     175  784 978 977 627       //Pegado a la ventana
   //---------00011-------- Derehca
     170  700 557 988 965
     174  680 672 989 960       //Pegado a la ventana
   //---------11100-------- Izquierda
     980  990 990 614 611
     266  993 980 564 562       //Pegado a la ventana
   //---------00111-------- Derehca
     147  753 990 989 969
     130  599 990 987 988       //pegado a la ventana

   Consideraciones.
   La velocidad del robot es un factor importante.
   El radio de giro del robot depende de la diferencia de velocidad de los dos motores,
   se debe calibrar bien esto.
   El motor 1 gira a 220 mientras que el motor 2 gira a 255 para que se vaya derecho el robot.

*/

/////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                             //
//                                  ESTE YA SIRVE                                              //
//                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  NOTAS:
//  -> Con el ciclo while en el caso 11000 , 00011 , 10000 , 00001 , 01000 , 00010 , 01100 y 00110 se logra que, al leer blanco el sensor central, haya redirección.
//  -> Hay que lograr quitar las oscilaciones cuando lee el sensor central y adyacentes (s2,ss3,s4).
//  -> Este programa es el que mejor funciona bajo el sol, hay que verificar los valores umbrales de los sensores.
//
////////////////////////////////////////////////////////////////////////////////////////////////
#include "globales.h"
#include "movimiento.h"
#include "velocidades.h"
#include "sensores.h"
#include "RTTTL.h"

//--------------------------Variables------------------------------
//----------Sensores reflexivos-------------------------
int lec1;         //Almacena la lectura del sensor 1
int lec2;         //Almacena la lectura del sensor 2
int lec3;         //Almacena la lectura del sensor 3
int lec4;         //Almacena la lectura del sensor 4
int lec5;         //Almacena la lectura del sensor 5

//-------------Umbral con valores fijos------------------------------
int umbral_s1 = 300;       //Valor umbral del sensor 1
int umbral_s2 = 800;       //Valor umbral del sensor 2
int umbral_s3 = 800;       //Valor umbral del sensor 3
int umbral_s4 = 800;       //Valor umbral del sensor 4
int umbral_s5 = 900;       //Valor umbral del sensor 5

/*
  //-----------Umbral con valores calculados en la calibración (ver setup())-------------
  int umbral_s1;       //Valor umbral del sensor 1
  int umbral_s2;       //Valor umbral del sensor 2
  int umbral_s3;       //Valor umbral del sensor 3
  int umbral_s4;       //Valor umbral del sensor 4
  int umbral_s5;       //Valor umbral del sensor 5
*/


//-----------------Función para hacer lectura de sensores---------------------------------
void medir() {
  lec1 = analogRead(sensor_1);     //lee el valor del sensor 1 y almacenalo en lec1
  lec2 = analogRead(sensor_2);     //lee el valor del sensor 1 y almacenalo en lec2
  lec3 = analogRead(sensor_3);     //lee el valor del sensor 1 y almacenalo en lec3
  lec4 = analogRead(sensor_4);     //lee el valor del sensor 1 y almacenalo en lec4
  lec5 = analogRead(sensor_5);     //lee el valor del sensor 1 y almacenalo en lec5

  /* Serial.println("Izquierda_extremo   Izquierda    Centro    Derecha  Derecha_extremo");
    Serial.print("    ");
    Serial.print(lec1);
    Serial.print("          ");
    Serial.print(lec2);
    Serial.print("          ");
    Serial.print(lec3);
    Serial.print("          ");
    Serial.print(lec4);
    Serial.print("          ");
    Serial.print(lec5);
    Serial.println("    ");
    Serial.println("    ");
    //delay(300);
  */
}


//--------------------------Canción en Buzzer-----------------------------------------
//IMPORTANTE: Descomentar la canción que se quiera utilizar.
//char *song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
char *song = "Ionian:d=8,o=5,b=240:c,d,e,f,g,a,b,c6";

void setup() {
  //Serial.begin(9600);     // Comunicación serial apagada cuando se quiera hacer uso del LED. Con comuniación serial activada el LED se queda prendido.
  pinMode(push, INPUT);   // Push button como entrada
  pinMode(led, OUTPUT);   // LED (azul) como salida
  digitalWrite(led, 0);
  setup_cancion();
  setup_movimiento();
  alto();
  setup_sensores();
  /*
    calibrar();
    umbral_s1 = UMBRAL_S1();
    umbral_s2 = UMBRAL_S2();
    umbral_s3 = UMBRAL_S3();
    umbral_s4 = UMBRAL_S4();
    umbral_s5 = UMBRAL_S5();
  */
}

void loop() {
  medir();      //Lee los sensores

  //---------00100--------
  // 223  740 992 641 593
  //182  745 991 662 607       //Pegado a la ventana

  //----------------------------Lectura-00100------------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    adelante();
  }

  //----------------------------Lectura-01000------------------------------------
  if (lec1 < umbral_s1 &&  lec2 >= umbral_s2  && lec3 < umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      izquierda21();
      medir();
    }
    //adelante();
    derecha12();
  }

  //----------------------------Lectura-00010------------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 < umbral_s3 && lec4 >= umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      derecha21();
      medir();
    }
    //adelante();
    izquierda12();
  }

  //---------01100--------
  //   216  987 987 591 498
  // 157  748 991 641 608        //Pegado a la ventana

  //-----------------------------Lectura-01100-----------------------------------
  if (lec1 < umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      //izquierda12();
      izquierda21(); // Funciona mejor con este giro
      medir();
    }
    //adelante();
    derecha12();
  }

  //---------00110--------
  //  166  683 990 973 701
  //  175  784 978 977 627       //Pegado a la ventana

  //-----------------------------Lectura-00110-----------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 >= umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      //derecha12();
      derecha21(); // Funciona mejor con este giro
      medir();
    }
    //adelante();
    izquierda12();
  }

  //---------00011--------
  //  170  700 557 988 965
  //174  680 672 989 960       //Pegado a la ventana

  //-----------------------------Lectura-00011----------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 < umbral_s3 && lec4 >= umbral_s4 && lec5 >= umbral_s5) {
    while (lec3 < umbral_s3) {
      derecha31();
      medir();
    }
    adelante();
  }

  //---------11000--------
  //   966  961 591 544 570
  //   592  994 570 550 418
  //   478  972 604 638 643       //Pegado a la ventana

  //-----------------------------Lectura-11000----------------------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 < umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      izquierda31();
      medir();
    }
    adelante();
  }

  //---------00111--------
  //  147  753 990 989 969
  //  130  599 990 987 988       //pegado a la ventana

  //-----------------------------Lectura-00111----------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 >= umbral_s4 && lec5 >= umbral_s5) {
    derecha21();
  }

  //---------11100--------
  //  980  990 990 614 611
  //  266  993 980 564 562       //Pegado a la ventana

  //-----------------------------Lectura-11100----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    izquierda21();
  }

  //-----------------------------Lectura-10000----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      izquierda31();
      medir();
    }
    adelante();
  }

  //-----------------------------Lectura-00001----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    while (lec3 < umbral_s3) {
      derecha31();
      medir();
    }
    adelante();
  }

  /*
    //----------------------------Lectura-00000------------------------------------
    if(lec1 < 300 &&  lec2 < 800  && lec3 < 800 && lec4 < 800 && lec5 < 800) {
    delay(100);
      alto();
      }
  */
}
