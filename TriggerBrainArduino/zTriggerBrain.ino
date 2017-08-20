
#include <LinkedList.h>


void PlayIntroSequece()
{
    lcd.loadCustomChars();
    lcd.clearLine(2);

    lcd.printTo(0, 0, (char *)"Awake");
    lcd.pushBuffer();
    delay(1000);
    Serial.write("pushting buf");
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
    Serial.write("pushting buf2");
    lcd.pushBuffer();
    delay(1000);
}

void test()
{
    Serial.print(".");
}
void setup()
{
    
    setUpPages();
    
    Serial.begin(9600);
    Serial1.begin(31250);
    Serial2.begin(31250);
    Serial3.begin(31250);
    // Attach the interrupt to send the MIDI clock and start the timer
    Timer1.initialize(1);
    Timer1.setPeriod(calculateIntervalMicroSecs(bpm));
    Timer1.attachInterrupt(sendClockPulse);

    debug("\nrestarted\m");

        delay(100);
        shift.setupShift();
        nextLcdRedrawTopTime=millis()+LCD_REFRESH_FAST;
        nextLcdRedrawBottomTime=millis()+LCD_REFRESH_FAST;
        ReloadPage();
       
        while (Serial1.available()) Serial1.read();
}

void distributeClockToPages()
{  
    
    if (isRunning)
    {
        dividedCounter++;
        if (dividedCounter%(4)==0) 
        { debug('0'); } 
        else  { debug('.');}

        pulse=false;
        for (int i = 0; i < pageCount; i++)
            pages->get(i)->OnQuarterNote();
    }
        
}


/// ######################
/// MAIN LOOP 
/// ######################
        void loop()
                {
                if (pulse) distributeClockToPages();
                    checkSerial(); //*1000
                shift.checkInterface();
                 lcd.checkIfNeedsUpdate();

        }