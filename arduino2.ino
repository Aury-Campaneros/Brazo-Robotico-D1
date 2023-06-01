// ARDUINO ESCLAVO
#include <Servo.h>
char charNumero_1;
String strNumero_1;
int numero2;

#include <EEPROM.h> // Incluir libreria para EEPROM 

//Variables para almacenar datos en EEPROM
int servo6;
int servo9;
int servo10;
int servo11;

//Definir Variable para el timers
int retorno = 0;
int contador = 0;

//Definir nombre y posiciones de los Servos
Servo servo_6; 	//Servo del base
Servo servo_9;	//Servo lateral 1
Servo servo_10;	//Servo lateral 2
Servo servo_11;	//Servo Garra

void setup() {
  //Declarar de entradas y salidas
  DDRC = 0b11000000;
  //Declarar servos
  servo_6.attach(6, 500, 2500);
  servo_9.attach(9, 500, 2500);
  servo_10.attach(10, 500, 2500);
  servo_11.attach(11, 500, 2500);
  Serial.begin(9600);		//velocidad de transmición
  delay(500);
  
  //Declarar del timer 2
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

void loop() {  
  // Lectura de Datos de datos
  if(Serial.available()>0)
  {
    String cadena = Serial.readStringUntil('\n');	// lectura de datos
 	//convertir string to int
    numero2 = cadena.toInt();
    Serial.println(numero2);
    if(PINC==0b00111110){
      servo_6.write(numero2);
      delay(15);
      servo6 = numero2; //Guardar posicion del servo 6 en variable
    }
    if(PINC==0b00111101){
      servo_9.write(numero2);
      delay(15);
      servo9 = numero2; //Guardar posicion del servo 9 en variable
    }
    if(PINC==0b00111011){
      servo_10.write(numero2);
      delay(15);
      servo10 = numero2; //Guardar posicion del servo 10 en variable
    }
    if(PINC==0b00110111){
      servo_11.write(numero2);
      delay(15);
      servo11 = numero2; //Guardar posicion del servo 11 en variable
    }
   }
  
  if(PINC==0b00101111){ //Cuando se presione el boton 1
    EEPROM.write(0, servo6); //Guardar en el espacio 0 de la EEPROM la posicion del Servo 6
    EEPROM.write(1, servo9); //Guardar en el espacio 1 de la EEPROM la posicion del Servo 9
    EEPROM.write(2, servo10); //Guardar en el espacio 2 de la EEPROM la posicion del Servo 10
    EEPROM.write(3, servo11); //Guardar en el espacio 3 de la EEPROM la posicion del Servo 11
    Serial.println("Datos Guardados"); //Mostrar en consola datos guardados
  	}
  
  if(PINC==0b00011111){ //Cuando se presione el boton 2
    servo_6.write(EEPROM.read(0)); //Posicionar el Servo 6, leyendo la posicion que se guardo en la EEPROM en el espacio 0
    delay(250);                    //Tiempo para estabilizar
    servo_9.write(EEPROM.read(1)); //Posicionar el Servo 9, leyendo la posicion que se guardo en la EEPROM en el espacio 1
    delay(250);                    //Tiempo para estabilizar
    servo_10.write(EEPROM.read(2)); //Posicionar el Servo 10, leyendo la posicion que se guardo en la EEPROM en el espacio 2
    delay(250);                     //Tiempo para estabilizar
    servo_11.write(EEPROM.read(3)); //Posicionar el Servo 11, leyendo la posicion que se guardo en la EEPROM en el espacio 3
    delay(250);                     //Tiempo para estabilizar
    retorno = 1;                     //Activar bandera de retorno 
    delay(15000);                   //Esperar 15 segundos
  	}
  }

//Timer2 - retorna los servos a su posición 0
// luego de ejecutarse la EEPROM
ISR(TIMER2_COMPA_vect){ 
  contador++; //Definir incremento de contador
  if (contador == 15000){ //Cuando hayan pasado los 15 segundos
    if (retorno == 1){ //Y la bandera de retorno este activada 
      servo_6.write(0); //Posicionar Servo 6 en 0 
      delay(500);       //Tiempo de estabilizacion
      servo_9.write(130); //Posicionar Servo 9 en 0
      delay(500);         //Tiempo de estabilizacion
      servo_10.write(0); //Posicionar Servo 10 en 0
      delay(500);        //Tiempo de estabilizacion
      servo_11.write(0); //Posicionar Servo 11 en 0
      delay(500);        //Tiempo de estabilizacion
      contador = 0; //Resetear contador
      retorno = 0;  //Apagar bandera de retorno
    }
  }
}