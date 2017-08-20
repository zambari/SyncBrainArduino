
#include <TimerOne.h>


int dividedCounter;
void distributeClockToPages();
void sendClockPulse()
{if (isRunning)
  {
    //  Serial1.write(MIDI_CLOCK);
      Serial2.write(MIDI_CLOCK);
    //  Serial3.write(MIDI_CLOCK);
      pulseCount++;

      if (pulseCount%6==0)
      {
        quarterNote++;
        pulse=true;
      }
    } 
    //  pulse=true;
}



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
         lcd.print("BPM ");
         lcd.printDec(bpmDec);
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


////

class Page_BPM : public PageBase
{ 
public:


  void Play()
  {
  
    isRunning=true;
    sendMidi(MIDI_PLAY); 
  }
  
  void Stop()
  { 
    isRunning=false;
    sendMidi(MIDI_STOP); 
  }
  
  void updateBpm(int newBpm) {
    // Update the timer
    bpm=newBpm;
    bpmDec=bpm/10;
    long interval = calculateIntervalMicroSecs(bpm);
    Timer1.setPeriod(interval);
  
  }
  

bool steps[8];

  
 int myStep=-1;
    Page_BPM()
    {
     // Timer1.initialize(1000);
     // updateBpm(bpm);
      
    //  Timer1.attachInterrupt(sendClockPulse);
    //  Serial.write("bpom tra"+bpm);
    }
     ViewBpm v;

     bool handleRight() override
     {
     // clockDivisor+=1;
     // setBPM(bpm+10);
      updateBpm(bpm+100);
      debug("\nupdated bpm ");
       return true;
     }

     virtual bool handleLeft()override
     {
     updateBpm(bpm-100);
     debug("\nupdated bpm ");
      //clockDivisor--;
       return true;
     }
     void OnQuarterNote() override
     { requestLCDredraw=true;
       
      
      stepNr++;
       if (stepNr>=8) stepNr=0;


        if (stepNr==myStep)
        {
         sendMidi(NOTE_ON);
         sendMidi(0x18 );
         sendMidi(0x05 );
      debug("fUCKING SNARE PLEASE");
          shift.statusledToggle();
        }
   /*     if (stepNr==myStep+1)
        {
          Serial.print(NOTE_OFF);
          Serial.print(0x40);
          debug(0);
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
       
       //if (isActive)
       //  activeSubPage->PrintContent();
        // lcd.pushBuffer();
 
     }
  /*  void setBPM(int newbpm)
    { //debug("\n setting bpm \m");   
       bpm=newbpm; 
        long interval = calculateIntervalMicroSecs(bpm);
        debug("\n new bpm ");
        debug(interval);
        haltUpdates=true;
    Timer1.stop();
        Timer1.setPeriod(interval);
        Timer1.resume();
       // Timer1.attachInterrupt(sendClockPulse);
        haltUpdates=false; 
 
    }*/
      void OnButtonPress(int buttonNr) override
     {
       debug("onpress");   
      if (buttonNr<8)
      { 
        if (myStep==buttonNr) myStep=-1; else
        myStep=buttonNr;
        shift.ledReset();
      //int b=buttonNr-4;
      //clockDivisor+=b*10;
      //setBPM(bpm+b*10);
      }


      // activeSubPage->OnButtonPress(buttonNr);
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