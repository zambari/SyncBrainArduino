


////////////////////////////////////////////////////////////
/// Interface Layout
////////////////////////////////////////////////////////////
#include <LinkedList.h>

class PageView
{

  /// Subpages contain most of the functionality of the device

   public:
   virtual char * GetLabel();   // short label
   virtual void OnButtonPress(int buttonNr);  // active subpage will get button notifications
   virtual void PrintContent( ); // returns number of chars written


};


class Page
{
public:

  LinkedList<PageView *> *subPages = new LinkedList<PageView *>();
  PageView *activeSubPage;
  uint16_t subPageIndex;
  uint16_t subPageCount;
  uint16_t thisPageIndex;
  bool wantsSerial;
             //  LinkedList<PageView *> *subPages ;//= new LinkedList<PageView *>();
              //   PageView *activeSubPage;
                  // CUSTOMIZABLE BEGIN

                  // you must overload this function for your page to have a namespace MyNamespace
                 virtual char *GetLabel() ;
                 virtual PageView *GetSubpage(int i) ;
                 virtual void populateSubPages() ;    
                 virtual void OnClockPulse();
                 virtual void OnQuarterNote();
                 virtual int GetSubpageCount() ;
                 virtual void OnSerial(char c);
                // use this for interface
                virtual void OnButtonPress(int buttonNr);
              
                // CUSTOMIZABLE END

                // no need to touch much below that
                #pragma region semiPrivate
                // list of subpages
                #pragma endregion 
           

                  bool setSubPage(int i);

                    virtual bool handleRight();

                    virtual bool handleLeft();
                    virtual void handleButton(int buttnr);

};


////////////////////////////////////////////////////////////
/// Sysex
////////////////////////////////////////////////////////////
// comment out to disable serial echo
#define SERIAL_ECHO 

#define SYSEX_END 0xF7
#define SYSEX_START 0xF0
#define MIDI_ACTIVE_SENSE B11111110
#define MIDI_CLOCK 0xF8
#define BUFSIZE 30
#define BUFSIZE64 45
#define BAUD_MIDI 31250
#define BAUD_USART 9600


#define USE_BAUD BAUD_MIDI
#define MIDI_ACTIVE_UPDATE_TIME 500

#include <LinkedList.h>
#include <Base64.h>
long nextMills;
long nextClk;



//https://github.com/zambari/Arduino-Unity-SysEx-Blob-Bridge

/// SYSEX TRANSMIT BEGIN
/// a library maybe

class SysexTransmit{
uint8_t bufferRaw[BUFSIZE];
uint8_t bufferBase64[BUFSIZE64];
uint8_t recieveIndex;

  public:
  void TransmitBlob(char * s);
  void TransmitBlob(char * s, int blobByteCount);
  void  RunCommand(int cmd,  char* blobPointer, int decodedLen)   ;
  void  OnRecieveBlob(  char* blobPointer, int decodedLen) ;
  bool handleRpc(char thisChar) ;
 void  handleCC(char thisChar);  // need to escape character
   
};
SysexTransmit transmit;

////////////////////////////////////////////////////////////
/// LCD
////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////
/// Shift
////////////////////////////////////////////////////////////



/*
void OnNextPage();
void OnPrevPage() ;
void OnNavLeft();
void OnNavRight();
void OnPlayPress();
void OnStopPress();
void OnTempoUp();
void OnTempoDn();
*/
/*


void OnNextPage(){}
void OnPrevPage() {}
void OnNavLeft(){}
void OnNavRight(){}
void OnPlayPress(){}
void OnStopPress(){}
void OnTempoUp(){}
void OnTempoDn(){}*/
////////////////////////////////////////////////////////////
/// Shift
////////////////////////////////////////////////////////////


class Shift
{ 
 

unsigned long nextButtonScan;
unsigned long nextLedPush;
int lastInterfaceRead=0;
int interfaceRead;
public:

  bool leds[SERIAL_LED_COUNT];
 // void OnButtonPress(uint8_t butNr);
  void statusledToggle();
  void ledBarSet(uint8_t nr,bool v);
  bool ledBarGet(uint8_t nr);
  void statusledSet(bool v);
  void ledToggle(uint8_t ledNR);
  void ledSet(uint8_t ledNR,bool val);
  bool ledGet(uint8_t ledNR);
  void checkInterface();
  void newButtonReadState();
  void setupShift();

};
Shift shift;