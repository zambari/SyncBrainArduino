
#include <LinkedList.h>


void PlayIntroSequece()
{
    lcd.loadCustomChars();
    lcd.clearLine(2);

    lcd.printTo(0, 0, (char *)"Awake");
    lcd.commitBuffer();
    delay(1000);
    Serial.write("committing buf");
    lcd.printTo(0, 0, (char *)"AV-Bcain v.0.019");
    lcd.setCursor(0, 1);
    lcd.printCustom(6);
    lcd.printCustom(5);
    lcd.printCustom(4);
    lcd.printCustom(3);
    lcd.printCustom(2);
    lcd.printCustom(1);
    lcd.printCustom(0);
    lcd.printCustom(0);
    Serial.write("committing buf2");
    lcd.commitBuffer();
    delay(1000);
}


void setup()
{
    
    setUpPages();
    
    
    
    
    /*
#ifdef USE_MIDI
    Serial.begin(BAUD_MIDI);                // MIDI Baud
#else
Serial.begin(BAUD_USART);       
#endif*/
   // Serial.begin(9600); // MIDI Baud
   //   Serial.write("\n+++\n\n");
     /// PlayIntroSequece();
     //Serial.begin(38400);
     Serial.begin(31250);
     //  Set MIDI baud rate:
  //   Serial1.begin(31250);


        delay(100);
        shift.setupShift();
        nextLcdRedrawTopTime=millis()+LCD_REFRESH_FAST;
        nextLcdRedrawBottomTime=millis()+LCD_REFRESH_FAST;


        ReloadPage();
}
bool pulse;
void sendClockPulse()
{
      pulse=true;
}
void _sendClockPulse()
{
      pulse=false;
      clockCounter++;
      if (clockCounter<clockDivisor)
      {
          return;
      }  clockCounter=0;
        pulseCount++;

        #ifdef USE_MIDI
        Serial.write(MIDI_CLOCK);
        //Serial.write((int)0x90);
        //Serial.write((int)0x20);
        //Serial.write((int)0x40);
          //Serial.write(MIDI_CLOCK);
          //Serial.write((char)0x01);
          //Serial.write((char)0x01);
      #endif
        if (haltUpdates) return;
        if (pulseCount >= MAXQNOTES)
          pulseCount = 0;
         // for (int i = 0; i < pageCount; i++)
        //    pages->get(i)->OnClockPulse();
        if (pulseCount % 6 == 0)
        {
          quarterNote++;
          for (int i = 0; i < pageCount; i++)
          pages->get(i)->OnQuarterNote();
        }
        
}

void checkSerial()
{
   
  while (Serial.available()) 
  { byte b=Serial.read();
      transmit.handleRpc(b);

        shift.statusledToggle();
       //  for (int i = 0; i <pageCount; i++)
       //   pages->get(i)->OnSerial(b);
    }
    //  transmit.handleCC(b);90
}



long unsigned lastMillis;
void loop()
{
 if (pulse) _sendClockPulse();
  unsigned long m1=millis();
   checkSerial(); //*1000
    shift.checkInterface();
    if (pulse) _sendClockPulse();
  lcd.checkIfNeedsUpdate();
  unsigned long m2=millis();
  int delta=m2-m1;
  //cd.setCursor(0,0);
  //lcd.printDec(delta,4);
  //lcd.commitBuffer();
}