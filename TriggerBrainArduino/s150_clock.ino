
#include <TimerOne.h>
#define CLOCKS_PER_BEAT 24
#define NOTE_OFF 0x80
#define NOTE_ON 0x90
class ViewTrig : public PageView
{
  
public:
     char * GetLabel() override { return "trig";};
     void OnButtonPress(int buttonNr) override {
       if (buttonNr>8) return;

     }

 
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);

         lcd.printDec(bpm);
         lcd.print("  ");
         lcd.printDec(clockDivisor,2);
         lcd.print("  ");
         lcd.printDec(pulseCount,4);
    }
};

int stepNr;

class ViewBpm : public PageView
{
public:
     char * GetLabel() override { return "bpms";};
     void OnButtonPress(int buttonNr) override {
       
     }

 
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);

         lcd.printDec(bpm);
         lcd.print(" ");
         lcd.printDec(clockDivisor,2);
         lcd.print(" ");
         lcd.printDec(pulseCount,4);
         lcd.print(" ");
         lcd.printDec(stepNr);
    }
};
long calculateIntervalMicroSecs(int bpm) {
  // Take care about overflows!
  return 60L * 1000 * 1000 * 10 / bpm / CLOCKS_PER_BEAT;
}


bool haltUpdates=false;

class Page_BPM : public PageBase
{ 
public:

bool steps[8];

  
 int myStep;
    Page_BPM()
    {
      Timer1.initialize(1000);
      setBPM(bpm);
     Timer1.attachInterrupt(sendClockPulse);
    //  Serial.write("bpom tra"+bpm);
    }
     ViewBpm v;

     bool handleRight() override
     {
      clockDivisor+=1;
      //setBPM(bpm+1);
       return true;
     }
     void OnQuarterNote() override
     {
       stepNr++;
       if (stepNr>=8) stepNr=0;


        if (stepNr==myStep)
        {
          Serial.write(NOTE_ON);
          Serial.write(0x18 );
          Serial.write(0x05 );
          shift.statusledToggle();
        }
   /*     if (stepNr==myStep+1)
        {
          Serial.print(NOTE_OFF);
          Serial.print(0x40);
          Serial.print(0);
        }*/

       shift.ledReset();
       for (int i=0;i<8;i++)
       {
         if (i==stepNr||i==myStep)
         {
          shift.ledSet(i,true);
         } else 
         shift.ledSet(i,false);
       }
       
       //if (hasFocus)
       //  activeSubPage->PrintContent();
        // lcd.commitBuffer();
 
     }
    void setBPM(int newbpm)
    { //Serial.print("\n setting bpm \m");   
       bpm=newbpm; 
        long interval = calculateIntervalMicroSecs(bpm);
        Serial.print("\n new bpm ");
        Serial.print(interval);
        haltUpdates=true;
    Timer1.stop();
        Timer1.setPeriod(interval);
        Timer1.resume();
       // Timer1.attachInterrupt(sendClockPulse);
        haltUpdates=false;
 
    }
      void OnButtonPress(int buttonNr) override
     {
       Serial.print("onpress");   
      if (buttonNr<8)
      {myStep=buttonNr;
        shift.ledReset();
      //int b=buttonNr-4;
      //clockDivisor+=b*10;
      //setBPM(bpm+b*10);
      }


      // activeSubPage->OnButtonPress(buttonNr);
     }
     virtual bool handleLeft()override
     {
      //setBPM(bpm-1);
      clockDivisor--;
       return true;
     }
  void populateSubPages() override 
 {   
        subPages->add(&v);
      
            subPageIndex = 0;
            subPageCount = subPages->size();
            activeSubPage = subPages->get(0);
 }
  char *GetLabel() override
  {
    return "BPM";
  }
};

Page_BPM clock=Page_BPM();