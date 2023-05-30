// ARDUINO MAESTRO

int adcValue;
char charNumero[4];
String strNumero;

void setup()
{
  //Lectura Analogica
  ADMUX = 5;              //canal 4 = PC4 = A4
  // Configurar el pin como entrada
  DDRC &= ~(1 << PC5);
  //Vref interno = 01
  ADMUX &= ~(1<<REFS1);
  ADMUX |= (1<<REFS0);

  ADMUX &= ~(1<<ADLAR);     //ajuste a la derecha de la salida de 10 bits

  delay(20);  //esperar a que se estabilice el voltaje

  // Configurar el prescaler a 128, debe ser siempre menor a 200KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

  ADCSRA |= (1 << ADEN);    // Habilitar el ADC
  //DDRC = 0;
  Serial.begin(9600);		//velocidad de transmición
}

void loop()
{
  ADCSRA |= (1 << ADSC);        // Iniciar la conversión
  while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
  adcValue = ADC/5.683;      // obtener los 10 bits de la conversión ADCH:ADCL
  delay(500);
  //convertir int a string
  strNumero =adcValue;
  //convertir string a char
  strNumero.toCharArray(charNumero,4);
  Serial.write(charNumero);
  Serial.print('\n');
  delay(200);
}