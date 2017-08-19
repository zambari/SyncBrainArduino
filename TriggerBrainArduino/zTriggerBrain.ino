#include <TimerOne.h>
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
    //Serial.begin(31250);                // MIDI Baud
    Serial.begin(9600); // MIDI Baud
      Serial.write("\nAwake after restart");
      PlayIntroSequece();
      delay(100);
    
    //if (debugPin>0) pinMode(debugPin,OUTPUT); // if debug >1, init debug led on pin (13?)
    // if (debugPin2>0) pinMode(debugPin2,OUTPUT); // if debug >1, init debug led on pin (13?)
      
     delay(100);
   shift.setupShift();
  nextLcdRedrawTopTime=millis()+LCD_REFRESH_FAST;
 nextLcdRedrawBottomTime=millis()+LCD_REFRESH_FAST;
 Timer1.initialize(1);
 Timer1.setPeriod(calculateIntervalMicroSecs(1000));
 Timer1.attachInterrupt(sendClockPulse);

  //      Serial.write("\nSetting up pages\n");

    //    delay(1000);
      //  setUpPages();
        //Serial.write("\nReloadingp pages\n");

        //delay(1000);
     //ReloadPage();
        }


void checkSerial()
{
   
  while (Serial.available()) 
  { 
      transmit.handleRpc(Serial.read());

  }
  
}




void sendClockPulse()
{
  
  pulseCount++;
  if (pulseCount >= MAXQNOTES)
    pulseCount = 0;
  if (pulseCount % 6 == 0)
  {
    quarterNote++;
    for (int i = 0; i < pageCount; i++)
    {
      // if (pages[i]->wantsSteps)
      //      pages[i]->AdvanceStep();
    }
  }
    Serial.write(MIDI_CLOCK);
}
void checkIfLcdNeedsUpdate()
{
   if (/*requestLCDredraw &&*/ millis()>nextLcdRedrawTopTime)
    {
     nextLcdRedrawTopTime=millis()+LCD_REFRESH_LAZY;
     lcd.commitBufferTop();
     requestLCDredraw=false;
    }
   if (/*requestLCDredraw &&*/ millis()>nextLcdRedrawBottomTime)
    {
     nextLcdRedrawBottomTime=millis()+LCD_REFRESH_FAST;
     lcd.commitBufferBottom();
     requestLCDredraw=false;
    }
  
    
}
long unsigned lastMillis;
void loop()
{
   checkSerial(); //*1000
    shift.checkInterface();
   checkIfLcdNeedsUpdate();
   
}