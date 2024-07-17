#include <Arduino.h>
#include "globales.h"

const byte sensores[5] = {sensor_1, sensor_2, sensor_3, sensor_4, sensor_5};

int prom_s1 = 0;       //Valor umbral del sensor 1
int prom_s2 = 0;       //Valor umbral del sensor 2
int prom_s3 = 0;       //Valor umbral del sensor 3
int prom_s4 = 0;       //Valor umbral del sensor 4
int prom_s5 = 0;       //Valor umbral del sensor 5

void setup_sensores() {
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT); // Sensores como entrada
  }
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
          digitalWrite(led, 0);
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
          digitalWrite(led, 0);
          j = 0;
          while (j < num_mediciones) {
            prom_s2 += analogRead(sensor_2);
            delay(200);
            j++;
            Serial.println(analogRead(sensor_2));
          }
          prom_s2 /= num_mediciones;
          confirmacion();
          Serial.println(prom_s2);
          break;

        case 3:
          Serial.println("Sensor 3");
          digitalWrite(led, 0);
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
          digitalWrite(led, 0);
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
          digitalWrite(led, 0);
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
      digitalWrite(led, 0);
      break;
    }
  }
  Serial.print("Terminamos");
}

//-----------------Funciones que devuelven el valor umbral calculado del promedio de lecturas
int UMBRAL_S1() {
  return prom_s1;
}

int UMBRAL_S2() {
  return prom_s2;
}

int UMBRAL_S3() {
  return prom_s3;
}

int UMBRAL_S4() {
  return prom_s4;
}

int UMBRAL_S5() {
  return prom_s5;
}
