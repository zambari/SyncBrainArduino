
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
    Serial.begin(31250);                // MIDI Baud
   //Serial.begin(9600); // MIDI Baud
      Serial.write("\n+++\n\n");
     /// PlayIntroSequece();
     // delay(100);
    
    //if (debugPin>0) pinMode(debugPin,OUTPUT); // if debug >1, init debug led on pin (13?)
    // if (debugPin2>0) pinMode(debugPin2,OUTPUT); // if debug >1, init debug led on pin (13?)
      
     delay(100);
   shift.setupShift();
  nextLcdRedrawTopTime=millis()+LCD_REFRESH_FAST;
 nextLcdRedrawBottomTime=millis()+LCD_REFRESH_FAST;


     setUpPages();
     ReloadPage();
        }


void checkSerial()
{
   
  while (Serial.available()) 
  { byte b=Serial.read();
      transmit.handleRpc(b);

        shift.statusledToggle();
      for (int i = 0; i <pageCount; i++)
      {
        
          pages->get(i)->OnSerial(b);
        

      }
    }
    //  transmit.handleCC(b);90
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