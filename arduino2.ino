#include <EEPROM.h> // libreria EEPROM

// ARDUINO ESCLAVO
#include <Servo.h>
char charNumero_1;
String strNumero_1;
int numero2;

//Variables para almacenar datos en EEPROM
int servo6;
int servo9;
int servo10;
int servo11;

//variable para el timers
int retorno=0;
int contador=0;
//declaración de servos
Servo servo_6; 	//servo del base
Servo servo_9;	//servo lateral 1
Servo servo_10;	//servo lateral 2
Servo servo_11;	//servo pinza

void setup()
{
  //declaración de entradas y salidas
  DDRC = 0b11000000;
  //servos
  servo_6.attach(6, 500, 2500);
  servo_9.attach(9, 500, 2500);
  servo_10.attach(10, 500, 2500);
  servo_11.attach(11, 500, 2500);
  Serial.begin(9600);		//velocidad de transmición
  delay(500);
  
  //declaración del timer 2
  cli(); // stop interrupts
  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
  TCNT2  = 0; // initialize counter value to 0
  // set compare match register for 15037.593984962406 Hz increments
  OCR2A = 132; // = 16000000 / (8 * 15037.593984962406) - 1 (must be <256)
  // turn on CTC mode
  TCCR2B |= (1 << WGM21);
  // Set CS22, CS21 and CS20 bits for 8 prescaler
  TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei(); // allow interrupts

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
    if(PINC==0b00111110){
      servo_6.write(numero2);
      delay(15);
      servo6 = numero2;
    }
    if(PINC==0b00111101){
      servo_9.write(numero2);
      delay(15);
      servo9 = numero2;
    }
    if(PINC==0b00111011){
      servo_10.write(numero2);
      delay(15);
      servo10 = numero2;
    }
    if(PINC==0b00110111){
      servo_11.write(numero2);
      delay(15);
      servo11 = numero2;
    }
   }
  if(PINC==0b00101111){
    EEPROM.write(0, servo6);
    EEPROM.write(1, servo9);
    EEPROM.write(2, servo10);
    EEPROM.write(3, servo11);
    Serial.println("Datos Guardados");
  	}
  
  if(PINC==0b00011111){
    servo_6.write(EEPROM.read(0));
    delay(500);
    servo_9.write(EEPROM.read(1));
    delay(500);
    servo_10.write(EEPROM.read(2));
    delay(500);
    servo_11.write(EEPROM.read(3));
    delay(500);
    retorno =1;
    delay(15000);
  	}
  }

//Timer2 - retorna los servos a su posición original 
// luego de ejecutarse la EEPROM

ISR(TIMER2_COMPA_vect){
  contador++;
  if (contador == 15000){
    if (retorno==1){
      servo_6.write(0);
      delay(500);
      servo_9.write(130);
      delay(500);
      servo_10.write(0);
      delay(500);
      servo_11.write(0);
      delay(500);
      contador=0;
      retorno=0;
    }
  }
}