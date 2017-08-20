

#define NO_DEMO_CONTENT
#include <digitalWriteFast.h>
#define DIGITAL_WRITE_COMMAND digitalWriteFast
#define interfaceClockPin 2
#define interfaceDataPin 4
#define interfaceLedPin 5
#define interfaceShiftPin 3

#define LED_BAR_OFFSET 12

#define BUTTON_SEL_1 256
#define BUTTON_SEL_2 512
#define BUTTON_SEL_3 1024
#define BUTTON_SEL_4 2048
#define BUTTON_SEL_5 4096
#define BUTTON_SEL_6 8192
#define BUTTON_SEL_7 16384
#define BUTTON_SEL_8 32768
#define BUTTON_MENU_UP 32
#define BUTTON_MENU_DOWN 1
#define BUTTON_MENU_LEFT 64
#define BUTTON_MENU_RIGHT 128 
#define BUTTON_TEMPO_UP 16  //4
#define BUTTON_TEMPO_DOWN 8 //2
#define BUTTON_TEMPO_PLAY 2 //16
#define BUTTON_TEMPO_STOP 4 //8
#define LED_BEAT_1 8
#define LED_BEAT_2 4
#define LED_BEAT_3 2
#define LED_BEAT_4 1
#define LED_AUX_1 16
#define LED_SEL_8 256 
#define LED_SEL_7 512
#define LED_SEL_6 1024
#define LED_SEL_5 2048
#define LED_SEL_4 4096
#define LED_SEL_3 8192
#define LED_SEL_2 16386
#define LED_SEL_1 32768
#define MASK_LSB 0x00ff
#define MASK_MSB 0xff00 
#define MIDILED 4
#define SCAN_BUTTONS_EVERY 30
void OnNextPage();
void OnPrevPage() ;
void OnNavLeft();
void OnNavRight();
void OnPlayPress();
void OnStopPress();
void OnTempoUp();
void OnTempoDn();

void OnButtonPress(uint8_t butNr);

   
   void Shift::newButtonReadState(unsigned int state)
   {  statusledToggle();
     /// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  STRETCH BUTTONS BEGIN
     ///lcdw
     debug("\n buttons tatus ");
     debug(state);


     if( (state & BUTTON_TEMPO_UP) &&   (state & BUTTON_TEMPO_DOWN))   { Reset();} 

     if (state & BUTTON_MENU_UP)
     { OnPrevPage();OnButtonPress(8);} 
     if (state & BUTTON_MENU_DOWN)
     {  OnNextPage();OnButtonPress(9);} 
     if (state & BUTTON_MENU_LEFT)
     { OnNavLeft();OnButtonPress(10);} 
     if (state & BUTTON_MENU_RIGHT)
     { OnNavRight();OnButtonPress(11);} 
   
     if (state & BUTTON_TEMPO_UP)
     { OnTempoUp();OnButtonPress(12);} 
     if (state & BUTTON_TEMPO_DOWN)
      {   OnTempoDn();OnButtonPress(13); } 
     if (state & BUTTON_TEMPO_PLAY)
     {
       OnButtonPress(14);
       OnPlayPress();
         }
   
     if (state & BUTTON_TEMPO_STOP)
       OnStopPress();
     if (state & BUTTON_SEL_1)
       OnButtonPress(0);
     if (state & BUTTON_SEL_2)
       OnButtonPress(1);
     if (state & BUTTON_SEL_3)
       OnButtonPress(2);
     if (state & BUTTON_SEL_4)
       OnButtonPress(3);
     if (state & BUTTON_SEL_5)
       OnButtonPress(4);
     if (state & BUTTON_SEL_6)
       OnButtonPress(5);
     if (state & BUTTON_SEL_7)
       OnButtonPress(6);
     if (state & BUTTON_SEL_8)
       OnButtonPress(7);
   }
   // #endif
    void Shift::statusledToggle()
    {
      ledToggle(11);
    }
    void Shift::ledBarSet(uint8_t nr,bool v)
    {
      ledSet(LED_BAR_OFFSET-nr,v);
    }
    bool Shift::ledBarGet(uint8_t nr)
    {
    return  ledGet(LED_BAR_OFFSET-nr);
    }
    void Shift::statusledSet(bool v)
    {
      ledSet(11,v);
    }
    void Shift::ledToggle(uint8_t ledNR)
    {
      ledNR=SERIAL_LED_OFFSET-ledNR;
      leds[ledNR]=!leds[ledNR];
    }
    void Shift::ledReset()
    {
      for (int i=0;i<=8;i++)
      leds[i]=false;
      
    }
    void Shift::ledSet(uint8_t ledNR,bool val)
    { 
      ledNR=SERIAL_LED_OFFSET-ledNR;
      leds[ledNR]=val;
    }
    bool Shift::ledGet(uint8_t ledNR)
    {
      
      
      ledNR=SERIAL_LED_OFFSET-ledNR;
     return leds[ledNR];
    }



void Shift::checkInterface()
{   
      unsigned long currentMillis=millis();
      if (currentMillis>nextButtonScan)
      {
      nextButtonScan=currentMillis+SCAN_BUTTONS_EVERY;
      DIGITAL_WRITE_COMMAND(interfaceShiftPin,LOW); 
      delayMicroseconds(1);
      DIGITAL_WRITE_COMMAND(interfaceShiftPin,HIGH);
      delayMicroseconds(1);
            interfaceRead=0; 
            for (int i=0;i<SERIAL_LED_COUNT;i++) { 
                byte but1=digitalRead(interfaceDataPin);   
                interfaceRead=(interfaceRead<<1)+but1;
                if (leds[i])
               {DIGITAL_WRITE_COMMAND(interfaceLedPin,HIGH);}
                 else
                {DIGITAL_WRITE_COMMAND(interfaceLedPin,LOW);}
                DIGITAL_WRITE_COMMAND(interfaceClockPin,LOW);
                DIGITAL_WRITE_COMMAND(interfaceClockPin,HIGH);
           } 
          if (lastInterfaceRead!=interfaceRead)      // If keyboard has changed
            { 
              if (interfaceRead==0)
              newButtonReadState(lastInterfaceRead);
              lastInterfaceRead=interfaceRead;
          }
      }
}



  void Shift::setupShift()
  {  
    pinMode(interfaceDataPin,INPUT);
    pinMode(interfaceClockPin,OUTPUT);
    pinMode(interfaceLedPin,OUTPUT);
    pinMode(interfaceShiftPin,OUTPUT);
  }
