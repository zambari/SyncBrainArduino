
#define SYSEX_END 0xF7
#include <Base64.h>
#define SYSEX_START 0xF0
#define MIDI_ACTIVE_SENSE B11111110
#define MIDI_CLOCK 0xF8
#define BUFSIZE 30
#define BUFSIZE64 45
void Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
} 

class Rpc{

uint8_t bufferRaw[BUFSIZE];
uint8_t bufferBase64[BUFSIZE64];
uint8_t recieveIndex;
bool isRecieving=false;

void printBuf(char * label,char * buf, int len)
{
   Serial.println();
   Serial.print("Listing buffer :");
   Serial.println(label);
   
  for (int i=0;i<len;i++)
  {
    Serial.print(" value ");
    Serial.print(i);
    Serial.print(' ');
    Serial.print((int)buf[i]);
    Serial.print(" [");
    Serial.print((char)buf[i]);
    Serial.print("]\n");
    //printVal(recBuf[i]);
  }
  
}

void store(uint8_t nextChar)
{
  bufferRaw[recieveIndex++]=nextChar;
}



  public:

  void PrintString(char * s)
  { 
    int index=0;
    while (s[index]!=0&&index<BUFSIZE)
    {  
      
      Serial.print("\n  printing string \n");
      bufferRaw[index]=s[index];
      index++;
    }
 
    int encodedLen=0;  base64_encode(bufferBase64,bufferRaw,index);

    Serial.print((char)SYSEX_START);
 Serial.print((char)SYSEX_START); Serial.print((char)SYSEX_START);
    for (int i=0;i<encodedLen;i++)
    Serial.print((char)bufferBase64[i]);
    
    Serial.print((char)SYSEX_END);
    

  }
  void OnRecieveComplete()
  { 

   int decodedLen=  base64_decode(bufferRaw,bufferBase64,recieveIndex);
   ParseBlob();
   PrintString("ala ma kota");
  }
  bool handleRpc(char thisChar)  // need to escape character
  { 
    if (thisChar==(char)SYSEX_START)
        {
          if (isRecieving) Serial.print("sysex stat while recireving");
          isRecieving=true;
          recieveIndex=0;

    } else
    if (isRecieving)
    {    if (thisChar=='*') Reset();
          if (thisChar==(char)SYSEX_END)
          {
            isRecieving=false;
            OnRecieveComplete();
          }
          else
          {
              bufferBase64[recieveIndex]=thisChar;
              recieveIndex++;
               if (recieveIndex>=BUFSIZE64)
               {
                Serial.print("\nBuffer Overflow\n");
                isRecieving=false;
                return false;
               }    
          }
        return true;    
    } 
    else
    {
     #ifdef SERIAL_ECHO
      Serial.print("ECHO:");    Serial.print(thisChar); Serial.print('\n');
      #endif
    }
  }
};
Rpc rpc;


