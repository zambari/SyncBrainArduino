
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
#define CLOCKS_PER_BEAT 24
#define PPQN 6
#define MAXQNOTES 24 * 64
#define LCD_REFRESH_LAZY 740
#define LCD_REFRESH_FAST 140
#define NO_DEMO_CONTENT 


long nextLcdRedrawBottomTime;
long nextLcdRedrawTopTime;
int quarterNote;
int pulseCount;
bool requestLCDredraw=false;

byte lcdX=0;
byte lcdY=0;
byte pageCount = 3;
int activePageIndex=0;

void Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
} 