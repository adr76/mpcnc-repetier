/*
  Basic library example for TM1640. Kept small to fit in the limited space of an ATtiny44.   
  For more information see  https://github.com/maxint-rd/TM16xx
*/

#include <TM1640.h>

// TM16xx(byte dataPin, byte clockPin, byte strobePin, byte maxDisplays, byte digits, boolean activateDisplay=true,	byte intensity=7);
//TM16xx module(9, 10, 11, 1, 4,true,1);

TM1640 module(9, 10);
//TM1640 module(9, 10, 16);    // (DIN, SCLK, Digits)

void setup()
{
  module.setSegments(1, 8); //(nVal(Digit), nPos(Seg))
  
  //module.sendCommand(00111111);
  
  //module.setDisplayDigit(1,9,false); //(byte digit, byte pos=0, boolean dot=false, const byte numberFont[] = TM16XX_NUMBER_FONT);
  //module.setDisplayToString("HALO",9,9);
  //delay(500);                        // wait
  //module.clearDisplay();
}

void loop()
{
  //int nTime = ((millis() / 1000) / 60) * 100 + (millis() / 1000) % 60; // convert time to minutes+seconds as integer
  //module.setDisplayToDecNumber(nTime, _BV(9)); // display milliseconds with dot on digit 4
  

/* TimeClock test
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  module.setupDisplay(true, 7);   // sometimes noise on the line may change the intensity level
  int nTime = ((millis() / 1000) / 60) * 100 + (millis() / 1000) % 60; // minutes+seconds as integer
  module.setDisplayToDecNumber(nTime, _BV(4)); // display dot on digit 4
  delay(500);                        // wait
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  module.setDisplayToDecNumber(nTime, _BV(3)); // display colon on digit 3
  delay(500);                        // wait 
  */
}
