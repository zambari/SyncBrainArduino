
enum Parameters { test1, test2, test3,  lcdRatio, lcdRefreshTime, interfaceButtonRead, interfaceLedWrite, writeToEprom };
#define NO_DEMO_CONTENT
#define SERIAL_LED_COUNT 16

#define MIDI_STOP 0xFC
#define MIDI_START 0xFA
#define MIDI_PLAY MIDI_START
#define CLOCKS_PER_BEAT 24
#define NOTE_OFF 0x80
#define NOTE_ON 0x90

enum ArduinoCallOrders { cmdRestart,cmdLCDLine1 ,cmdLCDLine2,cmdShowLeds, cmdCommand2};
void Restart() // Restarts program from beginning but does not reset the peripherals and registers
{
        asm volatile ("  jmp 0");  
} 

int bpm=80;
int clockDivisor=18 ;
int clockCounter;