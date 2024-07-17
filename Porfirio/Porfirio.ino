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
//  NOTA: SE BUSCA LA VELOCIDAD MÁXIMA CON LA QUE PUEDE FUNCIONAR EL ROBOT CON PESO.
//  NOTA 2: TIEMPO QUE TARDA EN DAR UNA VUELTA 16.6 SEGUNDOS.
//  NOTA 3: Modificación a partir de la versión 5
//
////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------Variables------------------------------

//----------Sensores reflexivos-------------------------
#define sensor_1 A0    // sensor izquierdo extremo
#define sensor_2 A1    // sensor izquierdo
#define sensor_3 A2    // sensor central
#define sensor_4 A3    // sensor derecho
#define sensor_5 A4    // sensor derecho extremo  

int lec1;         //Almacena la lectura del sensor 1
int lec2;         //Almacena la lectura del sensor 2
int lec3;         //Almacena la lectura del sensor 3
int lec4;         //Almacena la lectura del sensor 4
int lec5;         //Almacena la lectura del sensor 5

const byte sensores[5] = {sensor_1, sensor_2, sensor_3, sensor_4, sensor_5};
//  int sensores[4] = {lec1,lec2,lec3,lec4,lec5};   //almacena la lectura de los sensores
int blanco;                //Variable que dirá cuando estamos en la línea
int anterior;              //Variable auxiliar para regresar a la línea blanca
int pasadito = 10;         //Valor que al sumar o restar permitirá que gire el seguidor
int umbral_s1 = 300;       //Valor umbral del sensor 1
int umbral_s2 = 800;       //Valor umbral del sensor 2
int umbral_s3 = 800;       //Valor umbral del sensor 3
int umbral_s4 = 800;       //Valor umbral del sensor 4
int umbral_s5 = 800;       //Valor umbral del sensor 5

int prom_s1 = 0;       //Valor umbral del sensor 1
int prom_s2 = 0;       //Valor umbral del sensor 2
int prom_s3 = 0;       //Valor umbral del sensor 3
int prom_s4 = 0;       //Valor umbral del sensor 4
int prom_s5 = 0;       //Valor umbral del sensor 5
//---------------------
#define led 1

//------------------Buzzer
#define buzz 3

//------------------Motores
#define in1 2     // Input 1
#define in2 4     // Input 2
#define mot1 5    // Enable 1 (motor izquierdo)
#define mot2 6    // Enable 2 (motor derecho)
#define in3 7     // Input 3
#define in4 8     // Input 4

const byte motores[6] = {in1, in2, mot1, mot2, in3, in4};
int velo = 150 + 40 + 30 ;         //velocidad a la que girarán las llantas, 1a 200, 2da 150
int veloc = 100 + 20 + 45;
int veloci = 50 + 10;


// Push button
#define push 13    // Push button
byte puch;
//---------------------------------------Funciones----

void adelante(int velo) {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, velo - 35);
  analogWrite(mot2, velo);
}

void atras(int velo) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, velo - 35);
  analogWrite(mot2, velo);
}

void izquierda1(int velo) {       //Giro de acuerdo al sensor 3 y 4
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloc);
  analogWrite(mot2, velo);
}

void derecha1(int velo) {        //Giro de acuerdo al sensor 2 y 3
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, velo);
  analogWrite(mot2, veloc);
}

void izquierda2(int velo) {     //Giro de acuerdo al sensor 1 y 2
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloci + 10);
  analogWrite(mot2, veloc);
}

void derecha2(int velo) {       //Giro de acuerdo al sensor 4 y 5
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, veloc);
  analogWrite(mot2, veloci + 10);
}

void izquierda3(int velo) { //Giro de acuerdo al sensor 1 y 2
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  analogWrite(mot1, veloci);
  analogWrite(mot2, veloc);
}
void derecha3(int velo) {       //Giro de acuerdo al sensor 4 y 5
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  analogWrite(mot1, veloc);
  analogWrite(mot2, veloci);
}

void alto() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  analogWrite(mot1, 0);
  analogWrite(mot2, 0);
}

void medir() {
  lec1 = analogRead(sensor_1);     //lee el valor del sensor 1 y almacenalo en lec1
  lec2 = analogRead(sensor_2);     //lee el valor del sensor 1 y almacenalo en lec2
  lec3 = analogRead(sensor_3);     //lee el valor del sensor 1 y almacenalo en lec3
  lec4 = analogRead(sensor_4);     //lee el valor del sensor 1 y almacenalo en lec4
  lec5 = analogRead(sensor_5);     //lee el valor del sensor 1 y almacenalo en lec5
}

void confirmacion() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(led, 0);
    delay(500);
    digitalWrite(led, 1);
    delay(500);
  }
}

void calibrar() {
  int j;
  byte contador = 0;
  int num_mediciones = 10;
  while (true) {
    digitalWrite(led, 1);
    if (digitalRead(push) == 1) {
      switch (contador) {
        case 0:
          Serial.println("Comenzamos calibracion");
          confirmacion();
          break;

        case 1:
          Serial.println("Sensor 1");
          digitalWrite(led,0);
          j = 0;
          while (j < num_mediciones) {
            prom_s1 += analogRead(sensor_1);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_1));
          }
          prom_s1 /= num_mediciones;
          confirmacion();
          Serial.println(prom_s1);
          break;

        case 2:
          Serial.println("Sensor 2");
          digitalWrite(led,0);
          j = 0;
          while (j < num_mediciones) {
            prom_s2 += analogRead(sensor_2);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_2));
          }
          prom_s2 /= num_mediciones;
          Serial.println(prom_s2);
          confirmacion();
          break;

        case 3:
          Serial.println("Sensor 3");
          digitalWrite(led,0);
          j = 0;
          while (j < num_mediciones) {
            prom_s3 += analogRead(sensor_3);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_3));
          }
          prom_s3 /= num_mediciones;
          confirmacion();
          Serial.println(prom_s3);
          break;

        case 4:
          Serial.println("Sensor 4");
          digitalWrite(led,0);
          j = 0;
          while (j < num_mediciones) {
            prom_s4 += analogRead(sensor_4);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_4));
          }
          prom_s4 /= num_mediciones;
          confirmacion();
          Serial.println(prom_s4);
          break;

        case 5:
          Serial.println("Sensor 5");
          digitalWrite(led,0);
          j = 0;
          while (j < num_mediciones) {
            prom_s5 += analogRead(sensor_5);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_5));
          }
          prom_s5 /= num_mediciones;
          confirmacion();
          Serial.println(prom_s5);
          break;
      }
      contador++;
      //Serial.println(contador);
    }
    if (contador == 6) {
      digitalWrite(led,0);
      break;
    }
  }
  Serial.print("Terminamos");
}
//-------------------------------------------------------------------------------

void setup() {
  //Serial.begin(9600);   // Comunicación serial apagada cuando se quiera controlar el led
  pinMode(led, OUTPUT); // led (azul) como salida
  digitalWrite(led, 0);
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT); // Sensores como entrada
  }
  for (int i = 0; i < 6; i++) {
    pinMode(motores[i], OUTPUT); // Motores como salida
  }
  pinMode(push, INPUT);  // Push button como entrada
  alto();
  calibrar();
}

void loop() {


  /*
    medir();
    Serial.println("Izquierda_extremo   Izquierda    Centro    Derecha  Derecha_extremo");
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
    delay(300);
  */
  medir();      //lee los sensores

  //---------00100--------
  // 223  740 992 641 593
  //182  745 991 662 607       //Pegado a la ventana

  //----------------------------Lectura-00100------------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    adelante(velo);
    //    delay(20);
  }

  //---------01100--------
  //   216  987 987 591 498
  // 157  748 991 641 608        //Pegado a la ventana

  //-----------------------------Lectura-01100-----------------------------------
  if (lec1 < umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {
    //   digitalWrite(led,1);
    izquierda1(velo);
    //    delay(20);
    //    derecha2(velo);
    //    delay(10);
    //    digitalWrite(led,0);
  }

  //---------00110--------
  //  166  683 990 973 701
  //  175  784 978 977 627       //Pegado a la ventana


  //-----------------------------Lectura-00110-----------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 >= umbral_s4 && lec5 < umbral_s5) {
    //    digitalWrite(led,1);
    derecha1(velo);
    //    delay(20);
    //    derecha2(velo);
    //    delay(10);
  }

  //---------00011--------
  //  170  700 557 988 965
  //174  680 672 989 960       //Pegado a la ventana

  //-----------------------------Lectura-00011----------------------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 < umbral_s3 && lec4 >= umbral_s4 && lec5 >= umbral_s5) {

    derecha3(velo);
    medir();            //vuelve a medir los sensores.
    if (lec1 < 300 &&  lec2 < 800  && lec3 >= 700 && lec4 >= 700 && lec5 < 700) {
      izquierda3(velo);
    }
  }

  //---------11000--------
  //   966  961 591 544 570
  //   592  994 570 550 418
  //   478  972 604 638 643       //Pegado a la ventana

  //-----------------------------Lectura-11000----------------------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 < umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {


    izquierda3(velo);
    //   delay(40);
    // derecha2(velo);
    //delay(20);
  }

  //---------00111--------
  //  147  753 990 989 969
  //  130  599 990 987 988       //pegado a la ventana

  //-----------------------------Lectura-00111----------------------
  if (lec1 < umbral_s1 &&  lec2 < umbral_s2  && lec3 >= umbral_s3 && lec4 >= umbral_s4 && lec5 >= umbral_s5) {
    derecha2(velo);
    //   delay(120);
    // izquierda2(velo);
    // delay(20);


  }
  //---------11100--------
  //  980  990 990 614 611
  //  266  993 980 564 562       //Pegado a la ventana

  //-----------------------------Lectura-11100----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {


    izquierda2(velo);
    //    delay(60);
    //  derecha2(velo);
    //delay(20);
  }

  //-----------------------------Lectura-10000----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {


    izquierda2(velo);
    //    delay(60);
    //  derecha2(velo);
    //delay(20);
  }

  //-----------------------------Lectura-00001----------------------
  if (lec1 >= umbral_s1 &&  lec2 >= umbral_s2  && lec3 >= umbral_s3 && lec4 < umbral_s4 && lec5 < umbral_s5) {


    derecha2(velo);
    //    delay(60);
    //  derecha2(velo);
    //delay(20);
  }
  /*
    //----------------------------Lectura-00000------------------------------------
    if(lec1 < 300 &&  lec2 < 800  && lec3 < 800 && lec4 < 800 && lec5 < 800) {
    delay(100);
      alto();

      }
  */
}
