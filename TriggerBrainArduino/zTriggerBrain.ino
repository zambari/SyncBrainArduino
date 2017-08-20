
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
     Serial.begin(9600);
     Serial.print("n\n\n\n");
     delay(100);
     Serial.print("o hi\n\n");
     delay(100);
     
     Serial.print("\n\n\nH heres us in 9600 baud, if you can read this, you have your terminal baud at 9600\n---\n\n");
     delay(100);
     Serial.begin(38400);
     delay(100);
     Serial.print("\n\n\n 38400 baud is too high \n\n");
     delay(100);
    
     Serial.begin(31250);
     delay(100);
     Serial.print("\nGREAT NEWS Ifyou can read this, you terminal is set correctly to at 31250 baud rate required by midin-. this is string is longer than the previous oene--\n\n");
     delay(100);
     Serial.begin(9600);
     Serial.print("\n\n\^ that was a reality check - heres us at 9600 again, if you saw the above sentence as some noise you are reading at a wrong baud and now lets have some midi clock shall we? ");
     Serial.print("\n\n\n");
     //  Set MIDI baud rate:
     delay(200);
     Serial.begin(31250);
     delay(200);
     Serial.print(MIDI_START);


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
        Serial.write(MIDI_CLOCK);
        #ifdef USE_MIDI
      
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
  { byte b=Serial.2read();
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