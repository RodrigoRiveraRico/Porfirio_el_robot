#include <Arduino.h>
#include "globales.h"
#include "RTTTL.h"

//------------------------Variables-----------------------------------------------
int N_s1;       //Lectura promedio en negro del sensor 1
int N_s2;       //Lectura promedio en negro del sensor 2
int N_s3;       //Lectura promedio en negro del sensor 3
int N_s4;       //Lectura promedio en negro del sensor 4
int N_s5;       //Lectura promedio en negro del sensor 5

int B_s1;       //Lectura promedio en blanco del sensor 1
int B_s2;       //Lectura promedio en blanco del sensor 2
int B_s3;       //Lectura promedio en blanco del sensor 3
int B_s4;       //Lectura promedio en blanco del sensor 4
int B_s5;       //Lectura promedio en blanco del sensor 5

//-------------------------setup--------------------------------------------------
void setup_sensores() {
  const byte sensores[5] = {sensor_1, sensor_2, sensor_3, sensor_4, sensor_5};
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT); // Sensores como entrada
  }
}
//---------------Indicador LED-----------
void confirmacion() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(led, 0);
    delay(500);
    digitalWrite(led, 1);
    delay(500);
  }
}
//-----------------Calibración sensores--------------------
void calibrar() {
  char *song = "Ionian:d=8,o=5,b=240:c,d,e,f,g,a,b,c6";
  int j;
  byte contador = 0;
  int num_mediciones = 10;
  int prom_s1 = 0;       //Lectura promedio del sensor 1
  int prom_s2 = 0;       //Lectura promedio del sensor 2
  int prom_s3 = 0;       //Lectura promedio del sensor 3
  int prom_s4 = 0;       //Lectura promedio del sensor 4
  int prom_s5 = 0;       //Lectura promedio del sensor 5
  while (true) {
    digitalWrite(led, 1);
    if (digitalRead(push) == 1) {
      switch (contador) {
        case 0:
          Serial.println("Comenzamos calibracion");
          //confirmacion();
          play_rtttl(song);
          break;

        case 1:
          Serial.println("Calibrando blanco...");
          digitalWrite(led, 0);
          j = 0;
          while (j < num_mediciones) {
            prom_s1 += analogRead(sensor_1);
            prom_s2 += analogRead(sensor_2);
            prom_s3 += analogRead(sensor_3);
            prom_s4 += analogRead(sensor_4);
            prom_s5 += analogRead(sensor_5);
            delay(200);
            j++;
          }
          // Calculamos promedio de lecturas
          prom_s1 /= num_mediciones;
          prom_s2 /= num_mediciones;
          prom_s3 /= num_mediciones;
          prom_s4 /= num_mediciones;
          prom_s5 /= num_mediciones;
          // Guardamos las lecturas del color blanco
          B_s1 = prom_s1;
          B_s2 = prom_s2;
          B_s3 = prom_s3;
          B_s4 = prom_s4;
          B_s5 = prom_s5;
          confirmacion();
          play_rtttl(song);
          Serial.println("Resultados:");
          Serial.println(B_s1);
          Serial.println(B_s2);
          Serial.println(B_s3);
          Serial.println(B_s4);
          Serial.println(B_s5);
          break;

        case 2:
          Serial.println("Calibrando negro...");
          digitalWrite(led, 0);
          j = 0;
          prom_s1 = 0;
          prom_s2 = 0;
          prom_s3 = 0;
          prom_s4 = 0;
          prom_s5 = 0;
          while (j < num_mediciones) {
            prom_s1 += analogRead(sensor_1);
            prom_s2 += analogRead(sensor_2);
            prom_s3 += analogRead(sensor_3);
            prom_s4 += analogRead(sensor_4);
            prom_s5 += analogRead(sensor_5);
            delay(200);
            j++;
          }
          // Calculamos promedio de lecturas
          prom_s1 /= num_mediciones;
          prom_s2 /= num_mediciones;
          prom_s3 /= num_mediciones;
          prom_s4 /= num_mediciones;
          prom_s5 /= num_mediciones;
          // Guardamos las lecturas del color negro
          N_s1 = prom_s1;
          N_s2 = prom_s2;
          N_s3 = prom_s3;
          N_s4 = prom_s4;
          N_s5 = prom_s5;
          confirmacion();
          Serial.println("Resultados:");
          Serial.println(N_s1);
          Serial.println(N_s2);
          Serial.println(N_s3);
          Serial.println(N_s4);
          Serial.println(N_s5);
          break;
      }
      contador++;
      //Serial.println(contador);
    }
    if (contador == 3) {
      digitalWrite(led, 0);
      play_rtttl(song);
      break;
    }
  }
  Serial.println("Terminamos");
}
//-----------------Funciones que devuelven el umbral-----------
int UMBRAL_S1() {
  return N_s1 + (B_s1 - N_s1) * 0.8;
}

int UMBRAL_S2() {
  return N_s2 + (B_s2 - N_s2) * 0.8;
}

int UMBRAL_S3() {
  return N_s3 + (B_s3 - N_s3) * 0.8;
}

int UMBRAL_S4() {
  return N_s4 + (B_s4 - N_s4) * 0.8;
}

int UMBRAL_S5() {
  return N_s5 + (B_s5 - N_s5) * 0.8;
}
