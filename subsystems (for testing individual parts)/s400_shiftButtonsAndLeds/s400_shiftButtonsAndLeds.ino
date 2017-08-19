
#define interfaceClockPin 2
#define interfaceDataPin 4
#define interfaceLedPin 5
#define interfaceShiftPin 3


#define SERIAL_LED_COUNT 16
#define INTERFACE_SCAN_REFRESH_TIME 20
#define INTERFACE_LED_REFRESH_TIME 455
#define INTERFACE_LED_HOLD_TIME 630
#define LED_SKIP_RATIO 10



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

#ifndef NO_DEMO_CONTENT



void OnNextPage(){}

void OnPrevPage() {}
void OnNavLeft(){}
void OnNavRight(){}
void OnPlayPress(){}
void OnStopPress(){}
void OnTempoUp(){}
void OnTempoDn(){}

#endif

class Shift {
public:
  #ifndef NO_DEMO_CONTENT

  void OnButtonPress(uint8_t butNr)
  {
    toggleLed(butNr);
  Serial.print("\nbutton press ");
  Serial.print((int)butNr);
  Serial.print("\n");
  }
  
#endif
  
  int interfaceRead;
  unsigned long nextShiftRefreshTime;
  unsigned long nextLedRefreshTime;
  int lastInterfaceRead = 3;
bool ledStatus[SERIAL_LED_COUNT];
void setLed(int i, bool value)
{
  if (i >= 0 && i < SERIAL_LED_COUNT)
    ledStatus[i] = value;
}
void toggleLed(int i)
{
  if (i >= 0 && i < SERIAL_LED_COUNT)
  {
    ledStatus[i] = !ledStatus[i];
  }
}

/*
void checkInterface()
{
if (millis()<nextLcdRefreshTime) return;
  nextLcdRefreshTime=millis()+INTERFACE_SCAN_REFRESH_TIME;
        digitalWrite(interfaceShiftPin, LOW);
        digitalWrite(interfaceShiftPin, HIGH);
        interfaceRead = 0; //reset status just in case

        //  READ FROM INTERFACE Serial input BEGIN
        bool last=false;
        for (int i = 0; i < SERIAL_LED_COUNT; i++)
      
         digitalWrite(interfaceLedPin, ((statusLed >> i) & 1));
          //if ( ledStatus[SERIAL_LED_COUNT])
        //  digitalWrite(interfaceLedPin,HIGH); //-i
       //   else
        //  digitalWrite(interfaceLedPin,LOW); //-i
         interafaceClk()  ;
        //     digitalWrite(interfaceClockPin, LOW);
      //  digitalWrite(interfaceClockPin, HIGH);
        } //  READ FROM INTERFACE input END

        interfaceRead = interfaceRead;
        // KEYBOARD BEGIN
        if (lastInterfaceRead != interfaceRead) // If keyboard has changed
        {
          // add shift in handlebuttons i guess
          lastInterfaceRead = interfaceRead;
          checkButtonStateChange();
        }
}*/

uint8_t ledSkipCounter;
bool showingLed;
void pushLeds(){
  
  for (int i = 0; i < SERIAL_LED_COUNT; i++)
  {
      bool thisLedStatus = ledStatus[i];
   //   digitalWrite(interfaceLedPin,((statusLed>>i)&1));
      if (thisLedStatus)
        digitalWrite(interfaceLedPin, HIGH); //-i
      else
        digitalWrite(interfaceLedPin, LOW); //-i


        digitalWrite(interfaceShiftPin, LOW);
        digitalWrite(interfaceShiftPin, HIGH);
   //Serial.print("\n");
   //Serial.print(i);
   //if (thisLedStatus)
   //Serial.print("HIGH");//-i
 //else
 //Serial.print("LOW");//-i

  } //  READ FROM INTERFACE input END
}
void readButtons()
{ 
  digitalWrite(interfaceShiftPin, LOW);
  digitalWrite(interfaceShiftPin, HIGH);
  interfaceRead = 0; 
  for (int i = 0; i < SERIAL_LED_COUNT; i++)
  {
    byte but1 = digitalRead(interfaceDataPin);
    interfaceRead = (interfaceRead << 1) + but1;
    digitalWrite(interfaceShiftPin, LOW);
    digitalWrite(interfaceShiftPin, HIGH);
  } 
  checkButtonStateChange();
}
void checkInterface()
{
unsigned long currentMillis=millis();//cache
  
  if (currentMillis>nextLedRefreshTime)
  {  digitalWrite(interfaceShiftPin, LOW);
    digitalWrite(interfaceShiftPin, HIGH);
    if (!showingLed)
    {
      showingLed=true;
      Serial.print("s");
      nextLedRefreshTime=currentMillis+INTERFACE_LED_HOLD_TIME;
      pushLeds();
    } else
    {   Serial.print("n");
      showingLed=false;
      digitalWrite(interfaceLedPin, LOW); 
      nextLedRefreshTime=currentMillis+INTERFACE_LED_REFRESH_TIME;
    }
 
  }
  if (currentMillis> nextShiftRefreshTime)
  {  
   
    nextShiftRefreshTime = currentMillis+ INTERFACE_SCAN_REFRESH_TIME;
    readButtons();
//reset status just in case
  //bool last = false;
//  bool powerLeds = true;//false;
 // ledSkipCounter++;
 // if (ledSkipCounter >= LED_SKIP_RATIO)
//  {
//    ledSkipCounter = 0;
//    powerLeds = true;
//  }
  //  READ FROM INTERFACE Serial input BEGIN
 

  // KEYBOARD BEGIN
  
 // add shift in handlebuttons i guess
  
  }

}/*
void interfaceClk()
{
  digitalWrite(interfaceClockPin, LOW);
  digitalWrite(interfaceClockPin, HIGH);
  // shift registers are really quick so we dont need any additional delays here - not on my  74hct at least
}*/


void checkButtonStateChange()
{ if (lastInterfaceRead == interfaceRead) 
  {// If keyboard has changed
    Serial.print("btn3");
    return;
  }
  Serial.print("btn");
  lastInterfaceRead = interfaceRead;
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

void shiftSetup()
{
    pinMode(interfaceDataPin, INPUT);
    pinMode(interfaceClockPin, OUTPUT);
    pinMode(interfaceLedPin, OUTPUT);
    pinMode(interfaceShiftPin, OUTPUT);
    lastInterfaceRead=2;
}
};
Shift shift;
#ifndef NO_DEMO_CONTENT
void setup()
{
  Serial.begin(9600);
  Serial.print("hello\n");
  shift. shiftSetup();
}

unsigned long nextLedChange;
void loop()
{
 
  shift.checkInterface();
  if (millis()>nextLedChange)
  {
    nextLedChange=millis()+100;
    int ledIndex=random(0,16);
    int    ledIndex2=random(0,16);
  
    shift.setLed(ledIndex,true);

    shift.setLed(ledIndex2,false);
   // shift.setLed(random(0,16),false);
  }
}
#endif

