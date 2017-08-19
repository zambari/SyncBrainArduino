
enum Parameters { test1, test2, test3,  lcdRatio, lcdRefreshTime, interfaceButtonRead, interfaceLedWrite, writeToEprom };
#define NO_DEMO_CONTENT
#define SERIAL_LED_COUNT 16

enum ArduinoCallOrders { cmdRestart,cmdLCDLine1 ,cmdLCDLine2,cmdShowLeds, cmdCommand2};
void Restart() // Restarts program from beginning but does not reset the peripherals and registers
{
        asm volatile ("  jmp 0");  
} 

int bpm=80;