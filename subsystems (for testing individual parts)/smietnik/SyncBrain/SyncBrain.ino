//#include <TimerOne.h>
#define interfaceClockPin 2
#define interfaceDataPin 4
#define interfaceLedPin 5
#define interfaceShiftPin 3



void checkSerial()
{
    while (Serial.available() > 0) {
    // read the incoming byte:
    
    // HOLY READ
//    incomingByte = Serial.read();
  
   }
}

char decBuffer[] = {0,0,0,0,0,0,0};
char decFill = '0';

byte lcdX=0;  // storing last writrten lcd coortinates
byte lcdY=0;
/*
void Log(const char* label,char *c)
{   Serial.write('\nLog:');
   Serial.write(label);   Serial.write(' : ');
  Serial.write(c);   Serial.write('\n');
}
void Logn(char *c)
{
  Log(c);
    Serial.write('newline\n');
}
void Log(const char c) //disable log when using mdi
{
  Serial.write(c);
}
void Log(const char *c) //disable log when using mdi
{
  Serial.write(c);
}*/
#define CLOCKS_PER_BEAT 24

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
