/*
* VAG_CDC.c
*
* Created: 30.03.2017 20:00:51
* Author: Abrell Markus
*
* BC127  //ovc3860
*
* http://www.14core.com/wiring-the-xs3868-ovc3860-stereo-bluetooth-2-0-edr-module/
*
* https://learn.sparkfun.com/tutorials/understanding-the-bc127-bluetooth-module#introduction
*
*/

#define F_CPU 8000000UL
#define UART_BAUD_RATE 9600

#define CLOCKPIN  13
#define DATAPIN   14

#include <inttypes.h>
#include <SPI.h>

//void send_package(uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7);
//uint8_t spi_xmit(uint8_t val);

int count = 0;
int data[] = {0, 0, 0, 0, 0, 0, 0, 0};

// timer interrupt service routine
ISR(Timer0_COMPA_vect)
{
   //Setze vorlauf
   TCNT0 = 89;
   
   //Prüfe ob 8 Bits gesendet
   if(count < 8)
   {
     
     //Wenn Clock low dann lege daten an
     if(!(digitalRead(CLOCKPIN)))
     {
       digitalWrite(DATAPIN, (data>>count)%2);//Schreibe Daten
     }
     else
     {
       count++;
     }
     
     digitalWrite(CLOCKPIN, digitalRead(CLOCKPIN) ^ 1); // toggle CLOCK pin
   }
   //Setze den Zähler zurück
   else
   {
     count = 0;
   }
}

void setup() {
   //Beginne Serielle Kommunikation
   Serial.begin(UART_BAUD_RATE);
   
   //Sende Hallo Welt!
   Serial.println("Hallo Welt!");
   
   //Beginne SPI Kommunikation
   SPI.begin();  //Verbindung starten
   //SPI.setClockDivider(SPI_CLOCK_DIV128);  //Geschwindigkeit verlangsamen
   SPI.beginTransaction(SPISettings(62500, MSBFIRST, SPI_MODE0));
   
   //Vorbereitungen für Bitbanging SPI
   pinMode(CLOCKPIN, OUTPUT);
   pinMode(DATAPIN, OUTPUT);
   
   //Timer einrichten
   noInterrupts(); //keine Interupts
   TCCR0A |= (1<<CS00);
   TCNT0 = 89;
   interrupts(); //erlaube Interupts
}

void loop() {
    //Prüfen ob daten angekommen sind zum verarbeiten
    if (Serial.available())
    {
      //Serielles Zeichen einlesen
      char ch = Serial.read();
      
      if(ch == 's' || ch == 'S')
      {
        Serial.println("Start!");
        /*send_package(0x74,0xBE,0xFE,0xFF,0xFF,0xFF,0x8F,0x7C); //idle
        _delay_ms(10);
        send_package(0x34,0xFF,0xFE,0xFE,0xFE,0xFF,0xFA,0x3C); //load disc
        _delay_ms(100);
        send_package(0x74,0xBE,0xFE,0xFF,0xFF,0xFF,0x8F,0x7C); //idle
        _delay_ms(10);
        /*
        w = 1;
        
        while(w)
        {
          send_package(0x34,0xBE,0xFF,0xFF,0xFF,0xFF,0xCF,0x3C);
          _delay_ms(41);
          
          if (Serial.available()) w = 0;
        }
        */
      }
      else
      {
        Serial.println("Stop!");
      }
    }
}

void send_package(uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7)
{
  if(count == 0)
  {
    dat
  }
  /*
	SPI.transfer(c0);
	data=c0;
	_delay_us(874);
	SPI.transfer(c1);
	data=c1;
	_delay_us(874);
	SPI.transfer(c2);
	data=c2;
	_delay_us(874);
	SPI.transfer(c3);
	data=c3;
	_delay_us(874);
	SPI.transfer(c4);
	data=c4;
	_delay_us(874);
	SPI.transfer(c5);
	data=c5;
	_delay_us(874);
	SPI.transfer(c6);
	data=c6;
	_delay_us(874);
	SPI.transfer(c7);
	data=c7;*/
}

/*Zerlegen des Bytes int die einzelnen Bits
int bittransfer(uint8_t bit)
{
  data[0] = (bit&1);
  data[1] = (bit&2)>>1;
  data[2] = (bit&4)>>2;
  data[3] = (bit&8)>>3;
  data[4] = (bit&16)>>4;
  data[5] = (bit&32)>>5;
  data[6] = (bit&64)>>6;
  data[7] = (bit&128)>>7;
}*/
