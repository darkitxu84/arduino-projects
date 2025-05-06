#include <Servo.h>
#define OPENED true
#define CLOSED false

// Declaramos la variable para controlar el servo
Servo servoMotor;
bool servoStatus = CLOSED;
 
void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
 
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(5);
  servoMotor.write(0);
}

void servOpen() {
  servoMotor.write(180);
  servoStatus = OPENED;
  Serial.print("Abriendo!\n");
  return;
}

void servClose() {
  servoMotor.write(0);
  servoStatus = CLOSED;
  Serial.print("Cerrando!\n");
  return;
}

void loop() {
  if(Serial.available() != 0) {
    char option = Serial.read();
    
    if(option == 'o') servOpen();
    else if (option == 'c') servClose();
  } 
  
/* 
  servoMotor.write(0);
  delay(250);
  
  servoMotor.write(45);
  delay(250);
  
  servoMotor.write(90);
  delay(250);

  servoMotor.write(135);
  delay(250);

  servoMotor.write(180);
  delay(250);
*/
}
