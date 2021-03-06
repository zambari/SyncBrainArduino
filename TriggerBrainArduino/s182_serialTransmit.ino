bool isRecieving=false;

#define MY_CC 109
#define CC B10110000



void SerialTransmit::TransmitBlob(char * s)
{ 
    int counter=0;
    while(s[counter]!=0 && counter<BUFSIZE)
    counter++;
    TransmitBlob(s,counter);
}

void SerialTransmit::TransmitBlob(char * s, int blobByteCount)
{ 
/*
  Serial.print("blobtramit\ncount is ");
  Serial.print(blobByteCount);
  Serial.print("\n");  
  Serial.print(s); 
   Serial.print("\n");*/

  for (int i=0;i<blobByteCount;i++)
  bufferRaw[i]=s[i];
  int encodedLen= base64_encode(bufferBase64,bufferRaw,blobByteCount); // *output, *input, *le
  Serial.print((char)SYSEX_START);
  for (int i=0;i<blobByteCount;i++)
      Serial.print((char)bufferBase64[i]);
  Serial.print((char)SYSEX_END);
}

void  SerialTransmit::RunCommand(int cmd,  char* blobPointer, int decodedLen)   
{      Serial.print("\n runCommand \n ");
        Serial.print(cmd);
        Serial.print("\n");
        switch (cmd)
        {
        case cmdRestart: Restart();
        case cmdLCDLine1:
            lcd.printTo(0,0,blobPointer);
            lcd.pushBuffer();
            //TransmitBlob("ala ma ko");  // here you can light a LED or whaevert
        break;
        case cmdLCDLine2:
            lcd.printTo(0,1,blobPointer);
            lcd.pushBuffer();
        break;
        case cmdShowLeds:
        if (decodedLen!=16) 
        {   Serial.print(" wrong decode len ");
            Serial.print(decodedLen);
        }


          for (int i=0;i<16;i++)
            shift.ledSet(i,blobPointer[i]=='T');
           

        break;
        case 4: 
        TransmitBlob("ala ma kotazaa");
        break;
        case 5: 
          TransmitBlob("ala ma kotazaza");
        break;
        case 6: 
          TransmitBlob("ala ma kotazazaza");
        break;
        }
}
void ReloadPage();
void  SerialTransmit::OnRecieveBlob(  char* blobPointer, int decodedLen)        // DO USEFUL STUFF HERE
{
  RunCommand(blobPointer[0],blobPointer+1,decodedLen-1);
}
void handleCC(byte value)
{ 
  clock.updateBpm(value);
  ReloadPage();
}
byte cc_state;

void SerialTransmit::handleCC(char thisChar)  // need to escape character
{ 
if (cc_state==0)
{

  if (thisChar==CC) { cc_state=1;  }
  return; 
} else
if (cc_state==1)
{
  if (thisChar==MY_CC) { cc_state=2; return; }
 else cc_state=0;
} else
if (cc_state==2)
{
  handleCC(thisChar);
  cc_state=0;
} else cc_state=0;
}

  bool SerialTransmit::handleRpc(char thisChar)  // need to escape character
  { 
    if (thisChar==(char)SYSEX_START)
        {
          if (isRecieving) Serial.print("sysex stat while recireving");
          isRecieving=true;
          recieveIndex=0;

    } else
    if (isRecieving)
    { 
          if (thisChar==(char)SYSEX_END)
          {
            isRecieving=false;
            int decodedLen=  base64_decode(bufferRaw,bufferBase64,recieveIndex);
            OnRecieveBlob(bufferRaw,decodedLen);
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



  //////


  void distributeSerial(char r)
  {
  
  //  for (int i = 0; i <pageCount; i++)
           //   pages->get(i)->OnSerial(b);
  }
  

  
void checkSerial()
{

    while (Serial2.available()) 
    { byte midiByte=Serial2.read();
        rcvCnt++;
        if (rcvCnt>254) rcvCnt=0;
         debug(midiByte);
      ////  debug(b);
       // debug("\n");
     //   transmit.handleRpc(b);
     //   Serial1.write(b);   // loopback
    analyzer.OnSerial(midiByte);
    shift.statusledToggle();
         
      }
  while (Serial.available()) 
  { byte dbgByte=Serial.read();
         transmit.handleRpc(dbgByte);
   // shift.statusledToggle();
       //  for (int i = 0; i <pageCount; i++)
       //   pages->get(i)->OnSerial(b);
    }
    
    //  transmit.handleCC(b);90
}