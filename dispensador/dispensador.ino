// Librerias
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "HX711.h"

// Pines
#define SERVO_PIN 5
#define BALANZA_DT_PIN 2
#define BALANZA_SCK_PIN 3

// Constantes Servo
#define OPENED true
#define CLOSED false
#define OPENED_DEGREES 48
#define CLOSED_DEGREES 97

// Variables Globales
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor;
HX711 balanza;
bool servoStatus = CLOSED;

void servOpen() {
  servoMotor.write(OPENED_DEGREES);
  servoStatus = OPENED;
  Serial.print("Abriendo compuerta!\n");
  return;
}

void servClose() {
  servoMotor.write(CLOSED_DEGREES);
  servoStatus = CLOSED;
  Serial.print("Cerrando compuerta!\n");
  return;
}

void dispensar(unsigned long time) {
  Serial.print("Dispensando comida...");

  lcd.clear();
  lcd.print("Dispensando la");
  lcd.setCursor(0, 1);
  lcd.print("Comida!");

  servOpen();
  delay(time);
  servClose();

  lcd.clear();
  lcd.print("Comida");
  lcd.setCursor(0, 1);
  lcd.print("Dispensada!");
  
  Serial.print("Comida Dispensada!\n");
}

void updateLcd() {
  float peso = balanza.get_units(40);
  lcd.clear();
  lcd.print("Comida Actual:");
  lcd.setCursor(0, 1);
  lcd.print(peso);
  lcd.print(" gramos");
}

void setup() {
  // Iniciamos el monitor serie
  Serial.begin(9600);
  Serial.print("Iniciando Arduino...\n");

  // Iniciamos la pantalla e imprimimos texto inicial
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Tarando...");
  lcd.setCursor(0, 1);
  lcd.print("No coloque peso!");

  // Iniciamos el servo y lo establecemos en su posición inicial
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(CLOSED_DEGREES);

  // Iniciamos la balanza y la taramos
  balanza.begin(BALANZA_DT_PIN, BALANZA_SCK_PIN);
  balanza.set_scale(-703.68);
  balanza.tare(80);

  Serial.print("Inicializacion Lista!\n");  
}

void loop() {
  if (Serial.available() != 0) {
    char option = Serial.read();

    if (option == 'o') servOpen();
    else if (option == 'c') servClose();
    else if (option == 't') dispensar(3000);
    return;
  }

  updateLcd();
  delay(100);
}
