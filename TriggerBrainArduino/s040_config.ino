
enum Parameters { test1, test2, test3,  lcdRatio, lcdRefreshTime, interfaceButtonRead, interfaceLedWrite, writeToEprom };
#define NO_DEMO_CONTENT


#define MIDI_STOP 0xFC
#define MIDI_START 0xFA
#define MIDI_PLAY MIDI_START
#define CLOCKS_PER_BEAT 24
#define NOTE_OFF 0x80
#define NOTE_ON 0x90
#define debug(x); Serial.print(x);
#define Delay delay
enum ArduinoCallOrders { cmdRestart,cmdLCDLine1 ,cmdLCDLine2,cmdShowLeds, cmdCommand2};
void Restart() // Restarts program from beginning but does not reset the peripherals and registers
{
        asm volatile ("  jmp 0");  
} 
void sendMidi(char c)
{
  //  Serial1.write(c);
    Serial2.write(c);
   // Serial3.write(c);
    //add routing

}


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

#define PPQN 6
#define MAXQNOTES 24 * 64
#define LCD_REFRESH_LAZY 740
#define LCD_REFRESH_FAST 140
#define NO_DEMO_CONTENT 

bool pulse;

void Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
} 
int bpm=1200;
int bpmDec=120;
int clockDivisor=18 ;
int clockCounter;
bool isRunning=false;

long nextLcdRedrawBottomTime;
long nextLcdRedrawTopTime;

int quarterNote;
int pulseCount;
bool requestLCDredraw=false;

byte pageCount = 3;
int activePageIndex=0;

