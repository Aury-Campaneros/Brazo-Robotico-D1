// ARDUINO ESCLAVO
#include <Servo.h>
char charNumero_1;
String strNumero_1;
int numero2;

//declaración de servos
Servo servo_6; 	//servo del base
Servo servo_9;	//servo lateral 1
Servo servo_10;	//servo lateral 2
Servo servo_11;	//servo pinza

void setup()
{
  //declaración de entradas y salidas
  DDRC = 0b11110000;
  //servos
  servo_6.attach(6, 500, 2500);
  servo_9.attach(9, 500, 2500);
  servo_10.attach(10, 500, 2500);
  servo_11.attach(11, 500, 2500);
  Serial.begin(9600);		//velocidad de transmición
  delay(500);
}

void loop()
{  
  // recepción de datos
  if(Serial.available()>0)
  {
    String cadena = Serial.readStringUntil('\n');	// lectura de datos
 	//convertir string to int
    numero2 = cadena.toInt();
    Serial.println(numero2);
    if(PINC==0b00001110){
      servo_6.write(numero2);
      delay(15);
    }
    if(PINC==0b00001101){
      servo_9.write(numero2);
      delay(15);
    }
    if(PINC==0b00001011){
      servo_10.write(numero2);
      delay(15);
    }
    if(PINC==0b00000111){
      servo_11.write(numero2);
      delay(15);
    }
   }
  }