

/// end buffered lcd
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

//lib4LCD(int numCols, int numRows, int rs, int enable,int d4, int d5, int d6, int d7)
lib4LCD lcdLib(16, 2, 13, 12, 11, 10, 9, 8); //LCD PINOUTS go here

class BUFFEREDLCD
{
  uint8_t lcdX;
  uint8_t lcdY;


  byte lcdBuffer[4][16] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+', '-', '+', '-'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
public:
  bool dirtyFlag;

  void writetDec(const unsigned int value, const unsigned char precision)
  { // OR WRITE DEC?
    unsigned int temp1;
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
    write (&decBuffer[i]);
  }

  void writeHex(byte value)
  { // basedk to 7.5 to get a working one
    char temp;
    temp = value >> 4;
    temp += (temp > 9) ? 'A' - 10 : '0';
    char temp2[2]; // DIRTY DIRTY HACK
    temp2[1] = 0;  // DIRTY DIRTY HACK
    temp2[0] = temp;
    //temp2=temp;  void write(char printString[])
    write(temp2);
    //  lcdLib.print (temp);
    temp = value & 0x0f;
    temp += (temp > 9) ? 'A' - 10 : '0';
    temp2[0] = temp;
    write(temp2);
      dirtyFlag=true;
    //  lcdLib.print (temp);
  }

  void writeTo(byte x, byte y, char printString[])
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

  void write(char printString[])
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

  void writeCustom(byte znak)
  {

    lcdBuffer[lcdY][lcdX] = znak;
    dirtyFlag=true;
    lcdX++;
  }

  void clearLine(byte line)
  {
    
  for (int i = 0; i < 16; i++)
    {
    lcdBuffer[line][i] = ' ';
    }
    dirtyFlag=true;
  }

  void commitBuffer()
  {
    lcdLib.setCursor(0, 0);
    for (int i = 0; i < 16; i++)
    {
      lcdLib.print(lcdBuffer[0][i]);
    }
    lcdLib.setCursor(0, 1);

    for (int i = 0; i < 16; i++)
    {
      lcdLib.print(lcdBuffer[1][i]);
    }
    dirtyFlag=false;
  }
  void BUFFEREDLCD::setCursor(uint8_t x)
  {
    lcdX = x;
  
  }

  void BUFFEREDLCD::setCursor(uint8_t x, uint8_t y)
  {
    lcdX = x;
    lcdY = y;
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

void loadCustomChars()
{
  lcdLib.newCustomChar(0, char1);
  lcdLib.newCustomChar(1, char2);
  lcdLib.newCustomChar(2, char3);
  lcdLib.newCustomChar(3, char4);
  lcdLib.newCustomChar(4, char5);
  lcdLib.newCustomChar(5, char6);
  lcdLib.newCustomChar(6, char7);
}

};
BUFFEREDLCD lcd;

/*

void writeDec (const unsigned int out, int precision) { // OR PRITN DEC?
  unsigned int temp1;
  unsigned char temp2, i;
 //=3;
  temp1 = out;
  i = 5;

  do {                                // at least once
    temp2 = temp1 % 10;               // bust a digit off the low order end
    decBuffer[i--] = temp2 + '0';     // stick it in the buffer
    temp1 /= 10;                      // shift the whole mess to the right
  } while (temp1);                    // just so long as there's some left
  while (i >= (6 - precision)) decBuffer[i--] = decFill;
  i++;                                // went too far

int k=0;
while (k<precision)
{
   * lcdBuffer[lcdX++,lcdY]=decBuffer[k];
    k++;
}
  //lcdLib.print (&decBuffer[i]);
 // write (&decBuffer[i]);
}
*/

// LIB4LCD by Stefano Manni

//INTRODUCTION

// Lib4LCD is a simple but functional library allows an Arduino board to control LCDs based on the Hitachi HD44780 (or a compatible) chipset.
// The library works ONLY with 4 bit mode so uses only six pin on your Arduino (4 data lines in addition to the rs, and enable pin).
/*
FUNCTIONS

lib4LCD(int numCols, int numRows, int rs, int enable,int d4, int d5, int d6, int d7): Contructor
Parameters:

- rs: the number of the Arduino pin that is connected to the RS pin on the LCD

- enable: the number of the Arduino pin that is connected to the enable pin on the LCD

- d4, d5, d6, d7: the numbers of the Arduino pins that are connected to the corresponding data pins on the LCD

print(char or string): Prints a single char or a string to LCD.
clear(): Clears the LCD screen and positions the cursor in the upper-left corner.
setCursor(int col, int row): Sets cursor position. First column/row is identified by 0.
home(): Positions the cursor in the upper-left corner (0,0).
newCustomChar (int location, uint8_t[] pattern): fill one of the eight location in CGRAM with a custom char.
Parameters:

- location: indicates location in CGRAM and must be a number between 0 and 7

- pattern: 5×8 pattern of custom char. See example called “heart” for clarification.

printCustomChar (int location): print the custom char in location on the LCD.*/

// http://www.stefanomanni.it/arduino/lib4lcd/
//#include "lib4LCD.h"

#ifndef lib4LCD_h
#define lib4LCD_h

#include <string.h>
//#include "WProgram.h"

// Commands (Uncustomizable)			// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0	//FLAGS

#define CMD_FUNCTIONSET 0x20 //  0	0   1   DL  N   F   *	*	interface data lenght( DL) ;  number of lines (N) ; font size (F)

#define CMD_ENTRYMODESET 0x04 //  0	0   0   0   0   1  I/D	S	cursor move direction (I/D)  ;  display shift (S)

#define CMD_DISPLAYCONTROL 0x08 //  0	0   0   0   1   D   C	B	display on/off (D) ;  cursor on/off (C)  ; blink on/off (B)

#define CMD_CLEARDISPLAY 0x01 //  0	0   0   0   0   0   0	1

#define CMD_RETURNHOME 0x02 //  0	0   0   0   0   0   1	0

#define CMD_SETDDRAMADDR 0x80 //  1  ADD ADD ADD ADD ADD ADD ADD 	ADD=DDRAM address and corresponds to cursor address

#define CMD_SETCGRAMADDR 0x40 //  0   1  ACG ACG ACG ACG ACG ACG	ACG=CGRAM address

// Flags for function set command (Customizable)
#define FOURBITMODE 0x00 // DL=0 (interface data lenght = 4 bits)
#define TWOLINE 0x08     // N=1 (numbers of lines=2)
#define SINGLELINE 0x00  // N=0 (numbers of lines=1)
#define FONT5X8 0x00     // F=0 (font size=5x8)

// Flags for display entry mode command (Customizable)
#define ENTRYLEFT 0x02           // I/D=1 (increment cursor position by 1 after print a char on lcdLib)
#define ENTRYSHIFTDECREMENT 0x00 // S=0 (no display shift)

// Flags for display on/off control command (Customizable)
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

  // try to set 4 bit mode.  This is according to the hitachi HD44780 datasheet (figure 24, pag 46)
  sendCommand(0x03);
  delayMicroseconds(4500); // wait at least 4.1ms

  // second try
  sendCommand(0x03);
  delayMicroseconds(150); // wait at least 100us

  // finally third go!
  sendCommand(0x03);

  // finally, set to 4-bit interface
  sendCommand(0x02);

  //Function set: set data interface length (mode), number of lines, font size
  uint8_t functionset = FOURBITMODE | SINGLELINE | FONT5X8;
  if (nrows > 1)
  {
    functionset |= TWOLINE;
  }
  sendCommand(CMD_FUNCTIONSET | functionset);

  //Display control: turn the display on with no cursor or blinking
  sendCommand(CMD_DISPLAYCONTROL | DISPLAYON | CURSOROFF | BLINKOFF);

  //Entry mode set: set default text direction (from left to right)
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
  {
    row = nrows - 1;
  } // on the last row because we count rows starting w/0
  if (col >= ncols)
  {
    col = ncols - 1;
  } // on the last col because we count cols starting w/0
  sendCommand(CMD_SETDDRAMADDR | (col + row_offsets[row]));
}

void lib4LCD::newCustomChar(int location, uint8_t pattern[])
{                  //Fill the first 8 CGRAM locations
  location &= 0x7; //if location>7 or location<0
  sendCommand(CMD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++)
  {
    sendData(pattern[i]);
  }
  sendCommand(CMD_SETDDRAMADDR); //re-position DDRAM address counter in the current position
}

void lib4LCD::print(char string[])
{ //print an entire string on LCD
  int i;
  for (i = 0; i < strlen(string); i++)
  {
    write(string[i]);
  }
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
  {
    digitalWrite(data_pins[i], (value >> i) & 0x01);
  }
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
