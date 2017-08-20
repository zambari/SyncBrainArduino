#include <TimerOne.h>
#define CLOCKS_PER_BEAT 24
byte midiFrame[5];
bool d;
int rcvCnt;

class ViewAna : public PageView
{
public:
     char * GetLabel() override { return "ANLZ";};
     void OnButtonPress(int buttonNr) override {

     }

 
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);
         if (d)
         lcd.print("m ");   
         else
         lcd.print("M ");   
          lcd.printHex(rcvCnt);
          lcd.print("-");   
          lcd.printHex(midiFrame[0]);
   
         lcd.printHex(midiFrame[1]);
  
         lcd.printHex(midiFrame[2]);
   
         lcd.printHex(midiFrame[3]);
 
         lcd.printHex(midiFrame[4]);
    }
};


class Page_Analyzer : public PageBase
{ 
public:

    ViewAna v=ViewAna();
    int nextIndex=0;

    void OnSerial(char c) override
    {  
      //  rc
      //  if (isActive)
      d=!d;
        if (c&B10000000) nextIndex=0;
        midiFrame[nextIndex]=c;
        nextIndex++;
     
        //activeSubPage->PrintContent();
       requestLCDredraw=true;
        
        if (nextIndex>3)
        { nextIndex=0;
            //lcd.setCursor(0,1);
            
        }
    
    }
  
  void populateSubPages() override 
 {          wantsNoters=true;
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

Page_Analyzer analyzer=Page_Analyzer();