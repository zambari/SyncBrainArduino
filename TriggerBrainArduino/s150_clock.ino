#include <TimerOne.h>
#define CLOCKS_PER_BEAT 24

class ViewBpm : public PageView
{
public:
     char * GetLabel() override { return "bpms";};
     void OnButtonPress(int buttonNr) override {

Serial.print("btrtn");

     }

 
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);

         lcd.printDec(bpm);
    }
};

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


long calculateIntervalMicroSecs(int bpm)
{
  // Take care about overflows!
  return 60L * 1000 * 1000  / bpm / CLOCKS_PER_BEAT;
}

void setTimerSpeed()
{      Timer1.setPeriod(calculateIntervalMicroSecs(bpm));
}

class Page_BPM : public PageBase
{ 
public:


  
 
    Page_BPM()
    {
      Timer1.initialize(1);
      setTimerSpeed();
      Timer1.attachInterrupt(sendClockPulse);
    //  Serial.write("bpom tra"+bpm);
    }
     ViewBpm v;

     bool handleRight() override
     {
       bpm++;
       s
       setTimerSpeed();
       return true;
     }
 
     virtual bool handleLeft()override
     {
       bpm--;
       lcd.setDirty();
       setTimerSpeed();
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