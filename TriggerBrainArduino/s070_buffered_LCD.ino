
#define LCD_REFRESH_LAZY 340
#define LCD_REFRESH_FAST 90
#define LCD_FULL_REFRESH 3000


// ZBR 2017
// Part of SyncBrain, a continuation of AVBrain from 2009
// https://github.com/zambari/SyncBrainArduino

// The idea for buffered LCD is that we decouple printing to a 16x4 buffer in CGRAM
// and pushing it out to the actual LCD
// this is primarly to have control over when does the pushing happen,
// as we will be operating on tight timings
// this way it is also simpler to rawing complex screens
// we can also draw a screen, push it (using lcd.push)

// draw another screen, but delay screen refresh, to display notifications etc
// hardware interfacing is based on lib4LCD with tiny tiny tweaks

// all the heavy lifting is done via wrapping lib4LCD

// http://www.stefanomanni.it/arduino/lib4lcd/


class lib4LCD
{ // class definition has to be included here because I'm not importing is as a library - if the include worked it wouldnt have to be here
public:
  lib4LCD(int, int, int, int, int, int, int, int);
  void print(char[]);
  void print(char);
  void clear();
  void setCursor(int, int);
  void home();
  void newCustomChar(int, uint8_t[]);
  void printCustomChar(int);
  void sendCommand(uint8_t);
  void sendData(uint8_t);

private:
  void init(int, int, int, int, int, int);
  void begin(int, int);
  void push4Bits(uint8_t);
  void enablePinPulse();
  void write(char);

  int rs_pin;       // Selects registers. LOW: instruction register(command) ; HIGH: data register(data)
  int enable_pin;   // Starts data and command read/write
  int data_pins[4]; // In 4-bit mode used only D4,D5,D6,D7
  int nrows;        // Number of rows
  int ncols;        // Number of columns
};





lib4LCD lcdLib(16, 2, 13, 12, 11, 10, 9, 8); //LCD PINOUTS go here

/*
//class BUFFEREDLCD
{

  
private:
  
unsigned long nextLcdRedrawBottomTime;
unsigned long nextLcdRedrawTopTime;
  bool requestLCDredraw=false;
  char decBuffer[7] = {0,0,0,0,0,0,0};
  char decFill = '0';
public:

                byte lcdBuffer[4][16] = {
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+', '-', '+', '-'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
  
                   /* void write(char c)
                    {
                      if (lcdX>=16) return;
                  
                    }
                  
               
                bool dirtyFlag;
                uint8_t lcdX; //carret
                uint8_t lcdY;
*/
               // void BUFFEREDLCD::setCursor(uint8_t x)
              //  {
              //    lcdX = x;
             //   }

                void BUFFEREDLCD::setCursor(uint8_t x, uint8_t y)
                {
                  lcdX = x;
                  lcdY = y;
                }
                void BUFFEREDLCD::printTo(byte x, byte y, char printString[])
                {
                  byte i = 0;
                  while (printString[i]) // 0 terminated string
                  {
                    lcdBuffer[y][x + i] = printString[i]; // przepisujemy do matrycy bufora
                    i++;
                  }
                  lcdX = x + i;
                  lcdY = y;
                    dirtyFlag=true;
                }
                void BUFFEREDLCD::setDirty()
                {
                  dirtyFlag=true;
                }  
                void BUFFEREDLCD::print(char print)
                {
                  lcdBuffer[lcdY][lcdX ++] = print; 
                }
                void BUFFEREDLCD::print(char * printString)
                {
                  byte i = 0;
                  while (printString[i]&&(lcdX + i<16)) // 0 terminated string
                  {
                    lcdBuffer[lcdY][lcdX + i] = printString[i]; // przepisujemy do matrycy bufora
                    i++;
                  }
                  lcdX = lcdX + i;
                  if (lcdX>=16)
                  { lcdX=0;
                  }
                  dirtyFlag=true;
                }

                void  BUFFEREDLCD::printCustom(byte znak)
                {

                  lcdBuffer[lcdY][lcdX] = znak;
                  dirtyFlag=true;
                  lcdX++;
                }

                void  BUFFEREDLCD::clearLine(byte line)
                {
                  dirtyFlag=true;
                  lcdX=0;
                  lcdY=line;
                  if (line==2) {
                    clearLine(0);
                    clearLine(1);
                    return;
                  }
                    for (int i = 0; i < 16; i++)
                      {
                      lcdBuffer[line][i] = ' ';
                      }
                }


                void   BUFFEREDLCD::printDigit(const unsigned int value)
                {  char thisChar = value + '0';
                   print(thisChar);
                           
                }
                void   BUFFEREDLCD::printDec(const unsigned int value)
                {
                  printDec(value,3);
                }
                            void  BUFFEREDLCD::printDec(const unsigned long value, const unsigned char precision)
                            { // OR WRITE DEC?
                              unsigned long temp1;
                              unsigned char temp2, i;
                              if (precision > 6)
                              { // sanity check
                                lcdLib.print('X');
                                return;
                              }
                              temp1 = value;
                              i = 5;
                              int n = 0;
                              do
                              { 
            
                                temp2 = temp1 % 10; // bust a digit off the low order end
                                char thisChar = temp2 + '0';
                                decBuffer[i--] = thisChar; // stick it in the buffer
                                                          // Log("currentchar ",thisChar);
                                                          //  * lcdBuffer[lcdX++,lcdY]=thisChar;
                                temp1 /= 10;               // shift the whole mess to the right
                              } while (temp1);             // just so long as there's some left
                              while (i >= (6 - precision))
                                decBuffer[i--] = decFill;
                              i++; // went too far
            
                              int k = 0;
                                dirtyFlag=true;
                                print(&decBuffer[i]);
                            }
            
                            void   BUFFEREDLCD::printHex(byte value)
                            { // basedk to 7.5 to get a working one
                              char temp;
                              temp = value >> 4;
                              temp += (temp > 9) ? 'A' - 10 : '0';
                              char temp2[2]; // DIRTY DIRTY HACK
                              temp2[1] = 0;  // DIRTY DIRTY HACK
                              temp2[0] = temp;
                              //temp2=temp;  void write(char printString[])
                              print(temp2);
                              //  lcdLib.print (temp);
                              temp = value & 0x0f;
                              temp += (temp > 9) ? 'A' - 10 : '0';
                              temp2[0] = temp;
                              print(temp2);
                                dirtyFlag=true;
                              //  lcdLib.print (temp);
                            }
            
      void BUFFEREDLCD::pushBufferTop()
      {  
        lcdLib.setCursor(0, 0);
        for (int i = 0; i < 16; i++)
          lcdLib.print(lcdBuffer[0][i]);
          nextFullRedrawTime+=LCD_REFRESH_LAZY;
          nextLcdRedrawTopTime+=LCD_REFRESH_FAST;
      }

      void BUFFEREDLCD::pushBufferBottom()
      {
        lcdLib.setCursor(0, 1);
        for (int i = 0; i < 16; i++)
          lcdLib.print(lcdBuffer[1][i]);
          nextLcdRedrawBottomTime+=LCD_REFRESH_FAST;
          nextFullRedrawTime+=LCD_REFRESH_LAZY;
      }

      void BUFFEREDLCD::pushBuffer()
      {
        nextLcdRedrawBottomTime+=LCD_REFRESH_FAST;
        nextLcdRedrawTopTime+=LCD_REFRESH_FAST;
        nextFullRedrawTime+=LCD_FULL_REFRESH;

        lcdLib.setCursor(0, 0);
        for (int i = 0; i < 16; i++)
          lcdLib.print(lcdBuffer[0][i]);
        lcdLib.setCursor(0, 1);
        for (int i = 0; i < 16; i++)
          lcdLib.print(lcdBuffer[1][i]);
        dirtyFlag=false;
      }

                
              byte char7[8] = {
                  B11111,
                  B00100,
                  B00100,
                  B00100,
                  B00100,
                  B00100,
                  B01110,
              };
              byte char6[8] = {
                  B00000,
                  B01110,
                  B00100,
                  B00100,
                  B00100,
                  B00100,
                  B00100,
              };
              byte char5[8] = {
                  B00000,
                  B00000,
                  B01110,
                  B00100,
                  B00100,
                  B00100,
                  B00100,
              };
              byte char4[8] = {
                  B00000,
                  B00000,
                  B00000,
                  B01110,
                  B00100,
                  B00100,
                  B00100,
              };
              byte char3[8] = {
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B01110,
                  B00100,
                  B00100,
              };

              byte char2[8] = {
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B01110,
                  B00100,
              };

              byte char1[8] = {
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B01110,
              };

              void BUFFEREDLCD::loadCustomChars()
              {
                lcdLib.newCustomChar(0, char1);
                lcdLib.newCustomChar(1, char2);
                lcdLib.newCustomChar(2, char3);
                lcdLib.newCustomChar(3, char4);
                lcdLib.newCustomChar(4, char5);
                lcdLib.newCustomChar(5, char6);
                lcdLib.newCustomChar(6, char7);
              }
              void BUFFEREDLCD::delayNextLcdRefreshBottom(int miliseconds)
              {
                nextLcdRedrawBottomTime=millis()+miliseconds;
              }
              void BUFFEREDLCD::delayNextLcdRefreshTop(int miliseconds)
              {
                nextLcdRedrawTopTime=millis()+miliseconds;
              }
              void BUFFEREDLCD::delayNextLcdRefresh(int miliseconds)
              {
                delayNextLcdRefreshTop(miliseconds);
                delayNextLcdRefreshBottom(miliseconds);
             
              }

              void  BUFFEREDLCD::checkIfNeedsUpdate()
              { 
                unsigned long currentMillis=millis();
                if (currentMillis>nextFullRedrawTime)
                {     
                  DrawLayout();
                  nextFullRedrawTime=currentMillis+LCD_FULL_REFRESH;
                   nextLcdRedrawTopTime=currentMillis+LCD_REFRESH_LAZY;
                  
                  lcd.pushBuffer();
                } else
                {
                 if (/*requestLCDredraw &&*/ currentMillis>nextLcdRedrawTopTime)
                  {
                    if (requestLCDredraw)
                    { DrawLayout(); requestLCDredraw=false;}
                   nextLcdRedrawTopTime=currentMillis+LCD_REFRESH_LAZY;
                   lcd.pushBufferTop();
                   requestLCDredraw=false;
                  }
                 if (requestLCDredraw&& currentMillis>nextLcdRedrawBottomTime)
                  {
                    if (requestLCDredraw)
                    { DrawLayoutBottom(); requestLCDredraw=false;
                    }
                    nextLcdRedrawBottomTime=currentMillis+LCD_REFRESH_FAST;
                    lcd.pushBufferBottom();
                     requestLCDredraw=false;
                  }
                
                }  
              }

// http://www.stefanomanni.it/arduino/lib4lcd/
//#include "lib4LCD.h"

#ifndef lib4LCD_h
#define lib4LCD_h

#include <string.h>

// Commands (Uncustomizable)      // DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0  //FLAGS

#define CMD_FUNCTIONSET 0x20 //  0  0   1   DL  N   F   * * interface data lenght( DL) ;  number of lines (N) ; font size (F)
#define CMD_ENTRYMODESET 0x04 //  0 0   0   0   0   1  I/D  S cursor move direction (I/D)  ;  display shift (S)
#define CMD_DISPLAYCONTROL 0x08 //  0 0   0   0   1   D   C B display on/off (D) ;  cursor on/off (C)  ; blink on/off (B)
#define CMD_CLEARDISPLAY 0x01 //  0 0   0   0   0   0   0 1
#define CMD_RETURNHOME 0x02 //  0 0   0   0   0   0   1 0
#define CMD_SETDDRAMADDR 0x80 //  1  ADD ADD ADD ADD ADD ADD ADD  ADD=DDRAM address and corresponds to cursor address
#define CMD_SETCGRAMADDR 0x40 //  0   1  ACG ACG ACG ACG ACG ACG  ACG=CGRAM address
#define FOURBITMODE 0x00 // DL=0 (interface data lenght = 4 bits)
#define TWOLINE 0x08     // N=1 (numbers of lines=2)
#define SINGLELINE 0x00  // N=0 (numbers of lines=1)
#define FONT5X8 0x00     // F=0 (font size=5x8)
#define ENTRYLEFT 0x02           // I/D=1 (increment cursor position by 1 after print a char on lcdLib)
#define ENTRYSHIFTDECREMENT 0x00 // S=0 (no display shift)
#define DISPLAYON 0x04 // D=1
#define CURSOROFF 0x00 // C=0
#define BLINKOFF 0x00  // B=0

#endif

// LIB4LCD.CPP ORIGINAL FILE
/*++++++++++++++++++ CONSTRUCTOR +++++++++++++++++++++++++*/
lib4LCD::lib4LCD(int numCols, int numRows, int rs, int enable, int d4, int d5, int d6, int d7)
{
  init(rs, enable, d4, d5, d6, d7);
  begin(numCols, numRows);
}

/*++++++++++++++++++ INITIALIZE ++++++++++++++++++++++++++*/
void lib4LCD::init(int rs, int enable, int d4, int d5, int d6, int d7)
{

  data_pins[0] = d4;
  data_pins[1] = d5;
  data_pins[2] = d6;
  data_pins[3] = d7;

  rs_pin = rs;
  enable_pin = enable;

  for (int i = 0; i < 4; i++)
  {
    pinMode(data_pins[i], OUTPUT);
  }
  pinMode(rs_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);
}

void lib4LCD::begin(int numCols, int numRows)
{

  nrows = numRows;
  ncols = numCols;
  delayMicroseconds(50000); //we need at least 40ms after power rises above 2.7V
  sendCommand(0x03);
  delayMicroseconds(4500); // wait at least 4.1ms
  sendCommand(0x03);
  delayMicroseconds(150); // wait at least 100us
  sendCommand(0x03);
  sendCommand(0x02);
  uint8_t functionset = FOURBITMODE | SINGLELINE | FONT5X8;
  if (nrows > 1)
    functionset |= TWOLINE;
  sendCommand(CMD_FUNCTIONSET | functionset);
  sendCommand(CMD_DISPLAYCONTROL | DISPLAYON | CURSOROFF | BLINKOFF);
  sendCommand(CMD_ENTRYMODESET | ENTRYLEFT | ENTRYSHIFTDECREMENT);
  clear();
}

/*+++++++++++++++ HIGH LEVEL COMMANDS FOR THE USER ++++++++++++*/

void lib4LCD::clear()
{
  sendCommand(CMD_CLEARDISPLAY); // clear display, set cursor position to zero
  delayMicroseconds(2000);       // this command it's very slowly
}

void lib4LCD::home()
{
  sendCommand(CMD_RETURNHOME); // clear display, set cursor position to zero
  delayMicroseconds(2000);     // this command it's very slowly
}

void lib4LCD::setCursor(int col, int row)
{
  int row_offsets[] = {0x00, 0x40, 0x14, 0x54}; //offsets for first,second,third and fourth row
  if (row >= nrows)
    row = nrows - 1;
  if (col >= ncols)
    col = ncols - 1;
  sendCommand(CMD_SETDDRAMADDR | (col + row_offsets[row]));
}

void lib4LCD::newCustomChar(int location, uint8_t pattern[])
{                  //Fill the first 8 CGRAM locations
  location &= 0x7; //if location>7 or location<0
  sendCommand(CMD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++)
    sendData(pattern[i]);
  sendCommand(CMD_SETDDRAMADDR); //re-position DDRAM address counter in the current position
}

void lib4LCD::print(char string[])
{ //print an entire string on LCD
  int i;
  for (i = 0; i < strlen(string); i++)
    write(string[i]);
}

void lib4LCD::print(char c)
{ //overloading print for receving a single char as parameter
  write(c);
}

void lib4LCD::printCustomChar(int location)
{
  sendData(location);
}

void lib4LCD::write(char c)
{ //print a single char on LCD
  sendData(c);
}

/*++++++++++++++++++++++ LOW LEVEL COMMANDS ++++++++++++++++++++*/

void lib4LCD::sendCommand(uint8_t value)
{

  digitalWrite(rs_pin, LOW);
  //first nibble
  push4Bits(value >> 4); //the data transfer is completed after the 4-bit data has been transferred twice
  enablePinPulse();
  //second nibble
  push4Bits(value);
  enablePinPulse();
}

void lib4LCD::sendData(uint8_t value)
{

  digitalWrite(rs_pin, HIGH); //the only difference with sendCommand routine

  //first nibble
  push4Bits(value >> 4); //the data transfer is completed after the 4-bit data has been transferred twice
  enablePinPulse();

  //second nibble
  push4Bits(value);
  enablePinPulse();
}

void lib4LCD::push4Bits(uint8_t value)
{
  for (int i = 0; i < 4; i++)
    digitalWrite(data_pins[i], (value >> i) & 0x01);
}

void lib4LCD::enablePinPulse()
{
  digitalWrite(enable_pin, LOW);
  delayMicroseconds(1);
  digitalWrite(enable_pin, HIGH);
  delayMicroseconds(1); // high level must be at least 450ns
  digitalWrite(enable_pin, LOW);
  delayMicroseconds(1); // at least 37us to settle
  // TO FUCK UP TIMINNGS

  //  delayMicroseconds(900);// just to screw things up.
}




#ifndef NO_DEMO_CONTENT
void PlayIntroSequece()
{
    lcd.loadCustomChars();
    lcd.clearLine(2);

    lcd.printTo(0, 0, (char *)"Awake");
    lcd.pushBuffer();
    delay(1000);
    Serial.write("pushting buf");
    lcd.printTo(0, 0, (char *)"LCD Buffered");
    lcd.setCursor(0, 1);
    lcd.printCustom(6);
    lcd.printCustom(5);
    lcd.printCustom(4);
    lcd.printCustom(3);
    lcd.printCustom(2);
    lcd.printCustom(1);
    lcd.printCustom(0);
    lcd.printCustom(0);
    lcd.pushBuffer();
    delay(1000);
}
#endif