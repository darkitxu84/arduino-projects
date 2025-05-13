// Librerias
#include <Servo.h>

// Constantes
#define OPENED true
#define CLOSED false
#define SERVO_PIN 5
#define OPENED_DEGREES 48
#define CLOSED_DEGREES 97

// Declaramos la variable para controlar el servo
Servo servoMotor;
bool servoStatus = CLOSED;

void servOpen() {
  servoMotor.write( OPENED_DEGREES );
  servoStatus = OPENED;
  Serial.print( "Abriendo compuerta!\n" );
  return;
}

void servClose() {
  servoMotor.write( CLOSED_DEGREES );
  servoStatus = CLOSED;
  Serial.print("Cerrando compuerta!\n");
  return;
}

void servTimer(unsigned long time) {
  servOpen();
  delay(time);
  servClose();
}

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin( 9600 );
 
  // Iniciamos el servo
  servoMotor.attach( SERVO_PIN );
  servoMotor.write( CLOSED_DEGREES );
}

void loop() {
  if(Serial.available() != 0) {
    char option = Serial.read();
    
    if(option == 'o') servOpen();
    else if (option == 'c') servClose();
    else if (option == 't') {
      servTimer(2000);
    }
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
