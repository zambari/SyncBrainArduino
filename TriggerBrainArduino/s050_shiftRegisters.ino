#define SERIAL_LED_COUNT 16
#define SERIAL_LED_OFFSET 15
#define NO_DEMO_CONTENT


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
#include <digitalWriteFast.h>
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  SETUP AND MAIN LOOP BELOW

//#ifndef NO_DEMO_CONTENT

void OnNextPage(){}
void OnPrevPage() {}
void OnNavLeft(){}
void OnNavRight(){}
void OnPlayPress(){}
void OnStopPress(){}
void OnTempoUp(){}
void OnTempoDn(){}

//#endif

class Shift
{ 
 

unsigned long nextButtonScan;
unsigned long nextLedPush;
int lastInterfaceRead=0;
int interfaceRead;
public:

  bool leds[SERIAL_LED_COUNT];
  
  
  //#ifndef NO_DEMO_CONTENT
  
    void OnButtonPress(uint8_t butNr)
    { statusledToggle();
      ledToggle(butNr);
    if (butNr<4)
    {
      ledBarSet(butNr, !ledBarGet(butNr));
    }
            Serial.print("\nbutton press ");
            Serial.print((int)butNr);
            Serial.print("\n");
          char b[4];
          b[0]='b';
          b[1]=(char)((butNr)&0xFF);
          b[2]=(char)((butNr>>8)&0xFF);
          b[3]=0;
          transmit.TransmitBlob(b);
    }
    

   // #endif
    void statusledToggle()
    {
      ledToggle(11);
    }
    void ledBarSet(uint8_t nr,bool v)
    {
      ledSet(LED_BAR_OFFSET-nr,v);
    }
    bool ledBarGet(uint8_t nr)
    {
    return  ledGet(LED_BAR_OFFSET-nr);
    }
    void statusledSet(bool v)
    {
      ledSet(11,v);
    }
    void ledToggle(uint8_t ledNR)
    {
      ledNR=SERIAL_LED_OFFSET-ledNR;
      leds[ledNR]=!leds[ledNR];
    }
    void ledSet(uint8_t ledNR,bool val)
    { 
      ledNR=SERIAL_LED_OFFSET-ledNR;
      leds[ledNR]=val;
    }
    bool ledGet(uint8_t ledNR)
    {
      
      
      ledNR=SERIAL_LED_OFFSET-ledNR;
     return leds[ledNR];
    }



void checkInterface()
{   
      unsigned long currentMillis=millis();
      if (currentMillis>nextButtonScan)
      {
      nextButtonScan=currentMillis+SCAN_BUTTONS_EVERY;
      digitalWriteFast(interfaceShiftPin,LOW); 
      digitalWriteFast(interfaceShiftPin,HIGH);
            interfaceRead=0; 
            for (int i=0;i<SERIAL_LED_COUNT;i++) { 
                byte but1=digitalRead(interfaceDataPin);   
                interfaceRead=(interfaceRead<<1)+but1;
                if (leds[i])
               {digitalWriteFast(interfaceLedPin,HIGH);}
                 else
                {digitalWriteFast(interfaceLedPin,LOW);}
                digitalWriteFast(interfaceClockPin,LOW);
                digitalWriteFast(interfaceClockPin,HIGH);
           } 
          if (lastInterfaceRead!=interfaceRead)      // If keyboard has changed
            { newButtonReadState();
              lastInterfaceRead=interfaceRead;
          }
      }
}


void newButtonReadState()
{ 
  /// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  STRETCH BUTTONS BEGIN
  ///lcdw
  if (interfaceRead & BUTTON_MENU_UP)
  { OnPrevPage();OnButtonPress(8);} 
  if (interfaceRead & BUTTON_MENU_DOWN)
  {  OnNextPage();OnButtonPress(9);} 
  if (interfaceRead & BUTTON_MENU_LEFT)
  { OnNavLeft();OnButtonPress(10);} 
  if (interfaceRead & BUTTON_MENU_RIGHT)
  { OnNavRight();OnButtonPress(11);} 

  if (interfaceRead & BUTTON_TEMPO_UP)
  { OnTempoUp();OnButtonPress(12);} 
  if (interfaceRead & BUTTON_TEMPO_DOWN)
   {   OnTempoDn();OnButtonPress(13); } 
  if (interfaceRead & BUTTON_TEMPO_PLAY)
  {
    OnButtonPress(14);
    OnPlayPress();
      }

  if (interfaceRead & BUTTON_TEMPO_STOP)
    OnStopPress();
  if (interfaceRead & BUTTON_SEL_1)
    OnButtonPress(0);
  if (interfaceRead & BUTTON_SEL_2)
    OnButtonPress(1);
  if (interfaceRead & BUTTON_SEL_3)
    OnButtonPress(2);
  if (interfaceRead & BUTTON_SEL_4)
    OnButtonPress(3);
  if (interfaceRead & BUTTON_SEL_5)
    OnButtonPress(4);
  if (interfaceRead & BUTTON_SEL_6)
    OnButtonPress(5);
  if (interfaceRead & BUTTON_SEL_7)
    OnButtonPress(6);
  if (interfaceRead & BUTTON_SEL_8)
    OnButtonPress(7);
}

  void setupShift()
  {  
    pinModeFast(interfaceDataPin,INPUT);
    pinModeFast(interfaceClockPin,OUTPUT);
    pinModeFast(interfaceLedPin,OUTPUT);
    pinModeFast(interfaceShiftPin,OUTPUT);

  }
};
Shift shift;
/*
#ifndef NO_DEMO_CONTENT
void setup() { 
   Serial.begin(9600);                
   shift.setupShift();
}


void loop() {  
         shift.checkInterface(); 
                
  } 
#endif*/
