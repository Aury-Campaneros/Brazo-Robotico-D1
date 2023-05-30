// ARDUINO MAESTRO
int adcValue;
char charNumero[4];
String strNumero;

int convertedValuePot1;   // Valor convertido de 0 a 180 en Potenciometro 1
int convertedValuePot2;   // Valor convertido de 0 a 180 en Potenciometro 2
int convertedValuePot3;   // Valor convertido de 0 a 180 en Potenciometro 3
int convertedValuePot4;   // Valor convertido de 0 a 180 en Potenciometro 4

volatile bool pot1 = false;          //Bandera Potenciometro 1
volatile bool pot2 = false;          //Bandera Potenciometro 2
volatile bool pot3 = false;          //Bandera Potenciometro 3
volatile bool pot4 = false;          //Bandera Potenciometro 4

void setup() {
    //Configurar pines digitales 8, 9, 10 y 11 como salidas
  DDRB = B00001111;

  // Configurar PD2 como entrada con pull-up
  DDRD &= ~(1 << DDD2);
  PORTD |= (1 << PORTD2);

  // Configurar PD3 como entrada con pull-up
  DDRD &= ~(1 << DDD3);
  PORTD |= (1 << PORTD3);

  // Configurar PD4 como entrada con pull-up
  DDRD &= ~(1 << DDD4);
  PORTD |= (1 << PORTD4);

  // Configurar PD4 como entrada con pull-up
  DDRD &= ~(1 << DDD5);
  PORTD |= (1 << PORTD5);

  //configuración de la interrupción
  PCIFR |= (1 << PCIF2); // Limpiar bandera de interrupción en el puerto D, ponemos en 1 para limpiar
  PCICR |= (1 << PCIE2); //habilitar el grupo de interrupciones del puerto D
  PCMSK2 |= (1 << PCINT18);  // Seleccionar el pin a monitorear en el registro PCMSK2, Bit 18 corresponde a PD2
  PCMSK2 |= (1 << PCINT19);  // Seleccionar el pin a monitorear en el registro PCMSK2, Bit 19 corresponde a PD3
  PCMSK2 |= (1 << PCINT20);  // Seleccionar el pin a monitorear en el registro PCMSK2, Bit 20 corresponde a PD4
  PCMSK2 |= (1 << PCINT21);  // Seleccionar el pin a monitorear en el registro PCMSK2, Bit 20 corresponde a PD5

  Serial.begin(9600);
}

void loop() {
  if(pot1 == true){
    //Lectura Analogica
    ADMUX = 4;              //canal 4 = PC4 = A4
    // Configurar el pin como entrada
    DDRC &= ~(1 << PC4);
    //Vref interno = 01
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0);

    ADMUX &= ~(1<<ADLAR);     //ajuste a la derecha de la salida de 10 bits

    delay(20);  //esperar a que se estabilice el voltaje

    // Configurar el prescaler a 128, debe ser siempre menor a 200KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

    ADCSRA |= (1 << ADEN);    // Habilitar el ADC
    //DDRC = 0;

    ADCSRA |= (1 << ADSC);        // Iniciar la conversión
    while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
    uint16_t adcValue = ADC;      // obtener los 10 bits de la conversión ADCH:ADCL
    
    //Serial.println(adcValue);
    //delay(200);
    int EntradaPot1 = adcValue;
    convertedValuePot1 = map(EntradaPot1, 0, 1023, 0, 180);
    //Serial.println(convertedValuePot1);
    //Serial.write(convertedValue);
    delay(200);
    
    //convertir int a string
    strNumero = convertedValuePot1;
    //convertir string a char
    strNumero.toCharArray(charNumero,4);
    Serial.write(charNumero);
    Serial.print('\n');
    delay(200);
  }

  if(pot2 == true){
    //Lectura Analogica
    ADMUX = 3;              //canal 3 = PC3 = A3
    // Configurar el pin como entrada
    DDRC &= ~(1 << PC3);
    //Vref interno = 01
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0);

    ADMUX &= ~(1<<ADLAR);     //ajuste a la derecha de la salida de 10 bits

    delay(20);  //esperar a que se estabilice el voltaje

    // Configurar el prescaler a 128, debe ser siempre menor a 200KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

    ADCSRA |= (1 << ADEN);    // Habilitar el ADC
    //DDRC = 0;

    ADCSRA |= (1 << ADSC);        // Iniciar la conversión
    while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
    uint16_t adcValue = ADC;      // obtener los 10 bits de la conversión ADCH:ADCL
    
    //Serial.println(adcValue);
    //delay(200);
    int EntradaPot2 = adcValue;
    convertedValuePot2 = map(EntradaPot2, 0, 1023, 0, 180);
    Serial.println(convertedValuePot2);
    //Serial.write(convertedValue);
    delay(200);

    //convertir int a string
    strNumero = convertedValuePot2;
    //convertir string a char
    strNumero.toCharArray(charNumero,4);
    Serial.write(charNumero);
    Serial.print('\n');
    delay(200);
  }

  if(pot3 == true){
    //Lectura Analogica
    ADMUX = 2;              //canal 2 = PC2 = A2
    // Configurar el pin como entrada
    DDRC &= ~(1 << PC2);
    //Vref interno = 01
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0);

    ADMUX &= ~(1<<ADLAR);     //ajuste a la derecha de la salida de 10 bits

    delay(20);  //esperar a que se estabilice el voltaje

    // Configurar el prescaler a 128, debe ser siempre menor a 200KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

    ADCSRA |= (1 << ADEN);    // Habilitar el ADC
    //DDRC = 0;

    ADCSRA |= (1 << ADSC);        // Iniciar la conversión
    while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
    uint16_t adcValue = ADC;      // obtener los 10 bits de la conversión ADCH:ADCL
    
    //Serial.println(adcValue);
    //delay(200);
    int EntradaPot3 = adcValue;
    convertedValuePot3 = map(EntradaPot3, 0, 1023, 0, 180);
    Serial.println(convertedValuePot3);
    //Serial.write(convertedValue);
    delay(200);

    //convertir int a string
    strNumero = convertedValuePot3;
    //convertir string a char
    strNumero.toCharArray(charNumero,4);
    Serial.write(charNumero);
    Serial.print('\n');
    delay(200);
  }

  if(pot4 == true){
    //Lectura Analogica
    ADMUX = 1;              //canal 1 = PC1 = A1
    // Configurar el pin como entrada
    DDRC &= ~(1 << PC2);
    //Vref interno = 01
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0);

    ADMUX &= ~(1<<ADLAR);     //ajuste a la derecha de la salida de 10 bits

    delay(20);  //esperar a que se estabilice el voltaje

    // Configurar el prescaler a 128, debe ser siempre menor a 200KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

    ADCSRA |= (1 << ADEN);    // Habilitar el ADC
    //DDRC = 0;

    ADCSRA |= (1 << ADSC);        // Iniciar la conversión
    while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
    uint16_t adcValue = ADC;      // obtener los 10 bits de la conversión ADCH:ADCL
    
    //Serial.println(adcValue);
    //delay(200);
    int EntradaPot4 = adcValue;
    convertedValuePot4 = map(EntradaPot4, 0, 1023, 0, 180);
    Serial.println(convertedValuePot4);
    //Serial.write(convertedValue);
    delay(200);

    //convertir int a string
    strNumero = convertedValuePot4;
    //convertir string a char
    strNumero.toCharArray(charNumero,4);
    Serial.write(charNumero);
    Serial.print('\n');
    delay(200);
  }
}

ISR(PCINT2_vect) {
  cli(); 
  // Si la entrada 2 permanece en 1
   	if ( PIND & (1 << PIND2)){       
      PORTB &= B11111110; //Configurar en estado bajo led del pin 8 (apagado)
      pot1 = false;
    } else { //Si la entrada 2 cambia a 0
      PORTB |= B00000001; //Configurar en estado alto led del pin 8 (encendido)
      pot1 = true;
    }
  //PCIFR |= (1 << PCIF2); // Limpiar bandera de interrupción en el puerto D, se apaga automatico en la interrupcion
  sei(); // Habilitar interrupciones globales

  cli(); 
  // Si la entrada 3 permanece en 1
   	if ( PIND & (1 << PIND3) ) {       
      PORTB &= B11111101; //Configurar en estado bajo led del pin 8 (apagado)
      pot2 = false;
    } else { //Si la entrada 2 cambia a 0
      PORTB |= B00000010; //Configurar en estado alto led del pin 8 (encendido)
      pot2 = true;
    }
  //PCIFR |= (1 << PCIF2); // Limpiar bandera de interrupción en el puerto D, se apaga automatico en la interrupcion
  sei(); // Habilitar interrupciones globales

  cli(); 
  // Si la entrada 4 permanece en 1
   	if ( PIND & (1 << PIND4) ) {       
      PORTB &= B11111011; //Configurar en estado bajo led del pin 8 (apagado)
      pot3 = false;
    } else { //Si la entrada 2 cambia a 0
      PORTB |= B00000100; //Configurar en estado alto led del pin 8 (encendido)
      pot3 = true;
    }
  //PCIFR |= (1 << PCIF2); // Limpiar bandera de interrupción en el puerto D, se apaga automatico en la interrupcion
  sei(); // Habilitar interrupciones globales

  cli(); 
  // Si la entrada 4 permanece en 1
   	if ( PIND & (1 << PIND5) ) {       
      PORTB &= B11110111; //Configurar en estado bajo led del pin 8 (apagado)
      pot4 = false;
    } else { //Si la entrada 2 cambia a 0
      PORTB |= B00001000; //Configurar en estado alto led del pin 8 (encendido)
      pot4 = true;
    }
  //PCIFR |= (1 << PCIF2); // Limpiar bandera de interrupción en el puerto D, se apaga automatico en la interrupcion
  sei(); // Habilitar interrupciones globales

}
