#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
HX711 balanza;

void setup() {
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  lcd.setCursor(0,0);
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");

  Serial.begin(9600);
  balanza.begin(2, 3);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(-703.68); // Establecemos la escala
  balanza.tare(80);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}

void loop() {
  float peso = balanza.get_units(40);
  Serial.print("Peso: ");
  Serial.print(peso, 2);
  Serial.println(" g");
  lcd.clear();
  lcd.println(peso, 0);
  lcd.print(" gramos");
  delay(500);
}