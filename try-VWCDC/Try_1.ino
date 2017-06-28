/*
Testlauf, bin mal gespannt
*/

#define F_CPU 16000000UL
#define UART_BAUD_RATE 9600

byte start = 0;

//byte senden(byte, byte, byte, byte, byte, byte, byte, byte);
//byte transmite(byte);
//void radio_interrupt();


// timer interrupt service routine
ISR(Timer0_COMPA_vect)
{    
   if(start) 
   {
     PORTD ^= (1<<PD5);
     start = 0;
   }
   else
   {
     PORTD ^= (1<<PD5);
     start = 1;
   }
}



void setup() {
  //Pins einrichten
  //Vorbereitungen für Bitbanging SPI
  pinMode(PD5, OUTPUT);
  pinMode(PD7, OUTPUT);
  
  
  //Serielle Komunikation
  //Beginne Serielle Kommunikation
  Serial.begin(UART_BAUD_RATE);
  
  //Sende Hallo Welt!
  Serial.println("Hallo Welt!");
  
  
  //Timer einrichten
  noInterrupts(); //keine Interupts
  TCCR0A |= (1<<CS00);
  TCNT0 = 89; //Timer vorbelegen
  interrupts(); //erlaube Interupts
  
  
  //Pin Interrupt einrichten
  //attachInterrupt(0, radio_interrupt, CHANGE);
  
  //while(!start){
  //  senden(0x74, 0xBE, 0xFD, 0xFF, 0xF6, 0xFF, 0x8F, 0x7C);//IDLE
  //  delay(40);
  //}
  
  //Serial.println("Start Signal erhalten!");
}

void loop() {
    //senden(0x34, 0xBE, 0xFE, 0xFF, 0xFE, 0xFF, 0xCF, 0x3C);//PLAY
    //delay(40);
}








/*
byte senden(byte c0, byte c1, byte c2, byte c3, byte c4, byte c5, byte c6, byte c7){
  byte paket[8] = {c0, c1, c2, c3, c4, c5, c6, c7};
  byte bytes = 0;
  for(bytes = 0; bytes < 8; bytes++){
    transmite(paket[bytes]);
    delay(1);
  }
  
  PORTD &= B1011111; //Setze Clock und Daten 0
}

byte transmite(byte data){
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B10000000) << 0);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B01000000) << 1);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00100000) << 2);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00010000) << 3);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00001000) << 4);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00000100) << 5);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00000010) << 6);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
  delayMicroseconds(9);
  
  PORTD |= B00100000;//Setze Clock 1
  delayMicroseconds(6);
  PORTD = (PORTD & B01111111) | ((data & B00000001) << 7);//Daten anlegen
  delayMicroseconds(2);
  PORTD &= B11011111; //Setze Clock 0
}

void radio_interrupt() {
  //Prüfen ob pin high
  if(PORTD & B00000100) {
    start = 1;
  }
}
*