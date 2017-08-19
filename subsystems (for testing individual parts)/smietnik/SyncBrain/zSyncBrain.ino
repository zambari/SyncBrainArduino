#include "LinkedList.h"
/////////////////////////
//Page pages[] = { PageBPM(),Page(), PageBPM()};
//byte pageCount = 3;
//Page *activePage;
//bool udpateDisplayFlag=false;
//byte activePageIndex=0;
void setup()
{
  //Serial.begin(31250);                // MIDI Baud
  Serial.begin(9600); // MIDI Baud
  pinMode(interfaceDataPin, INPUT);
  pinMode(interfaceClockPin, OUTPUT);
  pinMode(interfaceLedPin, OUTPUT);
  pinMode(interfaceShiftPin, OUTPUT);
  //if (debugPin>0) pinMode(debugPin,OUTPUT); // if debug >1, init debug led on pin (13?)
  // if (debugPin2>0) pinMode(debugPin2,OUTPUT); // if debug >1, init debug led on pin (13?)
  lcd.loadCustomChars();
  lcd.writeTo(0, 0, (char *)"AV-Bcain v.0.019");
  lcd.setCursor(0, 1);
  lcd.writeCustom(6);
  lcd.writeCustom(5);
  lcd.writeCustom(4);
  lcd.writeCustom(3);
  lcd.writeCustom(2);
  lcd.writeCustom(1);
  lcd.writeCustom(0);
  lcd.writeCustom(0);

  lcd.commitBuffer();

  //delay(500); // start delay

  //debugFlash();
  //lcdMsg2((char *)"READY         ::");
  // Timer1.initialize(1);
  // Timer1.setPeriod(calculateIntervalMicroSecs(1000));
  // Timer1.attachInterrupt(sendClockPulse);

  // activePage = &pages[0];

  Serial.write("\n\n\nStarting:\n------\n\n");
  delay(10);





 //  Instantiate a LinkedList that will hold 'integer'
//LinkedList<PageBase> myLinkedList = LinkedList<PageBase>();

// Or just this
//LinkedList<int> myLinkedList;

// But if you are instantiating a pointer LinkedList...
LinkedList<Paget1> *myLinkedL2ist = new LinkedList<PageBase>();
myLinkedL2ist->add(Paget1);

// If you want a LinkedList with any other type such as 'MyClass'
// Make sure you call delete(MyClass) when you remove!
////LinkedList<MyClass> *myLinkedList = new LinkedList<MyClass>();
  //// updateDisplay();
  /*
A *a1=&A();
A *a2=&A();;
B *b1=&B();;
B *b2=&B();;
C *c1=&C();

a1->logme();
c1->logme();*/

  /*

C  *c[]={&A(),&B(),&A(),&B()};
c[0]->logme();
c[1]->logme();
c[2]->logme();
c[3]->logme();*/

  //a1.setNext();

  /*
  C  am[]={ A(),B(),A()};
  C  *a[]={&am[0],&am[1],&am[2]};

am[0].logme();
 am[1].logme();
  am[2].logme();

 a[0]->logme();
 a[1]->logme();
  a[2]->logme();
   Serial.write("setting next");
   if (a[0]==&am[0]) Serial.write("true"); else Serial.write("false");
am[0].setNext(a[0]);*/
  //am[1].setNext(&am[2]);
  /*

  //A a;
    a[0].logme();
   
    a[1].logme();
    a[2].logme();
    Serial.write("\n------\n\n");
  (&a[0])->logme();
   
  (&a[1])->logme();
  (&a[2])->logme();
    Serial.write("\n------\n\n");*/
}

//77777777777777777777777777777777777777777

#define PPQN 6
#define MAXQNOTES 24 * 64
int quarterNote;
//int pageCount =1;
uint16_t pulseCount;
void sendClockPulse()
{
  pulseCount++;
  if (pulseCount >= MAXQNOTES)
  {
    pulseCount = 0;
  }
  if (pulseCount % 6 == 0)
  {
    quarterNote++;
    for (int i = 0; i < pageCount; i++)
    {
      // if (pages[i]->wantsSteps)
      //      pages[i]->AdvanceStep();
    }
  }
}

long calculateIntervalMicroSecs(int bpm)
{
  // Take care about overflows!
  return 60L * 1000 * 1000 * 10 / bpm / CLOCKS_PER_BEAT;
}

void updateDisplay()
{
  // char *line2=*
  ///writeTo(0, 0, activePage->GetLabel() /*(char*) activePage->activeSubpage->getContent()*/);
  ///writeTo(0, 1, activePage->GetContent() /*(char*) activePage->activeSubpage->getContent()*/);
  /*lcdCursor(0, 0);
  writeDec(pulseCount, 2);
  activePage->clearRefreshFlag();*/
}
void loop()
{
  for (int i = 0; i < 3; i++)

  {
    // Logn(i+'0');
    //  Serial.write(i + '0');
    // Serial.write(" o \n");
    // lcd.setCursor(0,0);
    //lcd.writetDec (i,2);
    // l//cd.write(*pages[i]->GetLabel());
    //    if (pages[i] == NULL)
    //    Serial.write("null");
    //  else
    //    Serial.write("notNull");
Serial.write('\n');
       Serial.write(i+' ');
       Serial.write('\n');
     pages[i].PushLabel();
    lcd.commitBuffer();
    int k=0;
    while (k<1000)
    {
      k++;
      checkInterface();
    }
    
    // lcd.writeTo(0,0,"abc"); //
    // Serial.write(*pages[i]->GetLabel());
  }

  return;

  
  if (udpateDisplayFlag)
    updateDisplay();
  //if (activePage.requestRedrawFlag)  updateDisplay();
  //requestRedrawFlag
  // return;
  //currentMs = millis();
  checkSerial(); // our main function - reads the UART and parses MIDI messages.

  // INTERFACE HANDLING
  //ifaceRatioCounter++;
  // if (ifaceRatioCounter > ifaceRatio)
  {
    // ifaceRatioCounter = 0;
    checkInterface();
  } // update interface only every ifaceRatio cycles
  //  TODO TODO TODO TODO: CHANGE TO DO IT ONLY IF LCD CHAS CHANGED!!!
  // lcdRatioCounter++;
  // if ((lcdRatioCounter > lcdRatio))
  // {
  //   lcdRatioCounter = 0;
  //lcdDrawInterface();
  //lcdPrintBuffer();
  //  if (lcdInhibit < 1)
  {

    /*  lcd.clearLine(0);
    lcd.setCursor(1, 1);
   // lcd.lcdPrintDec(millis(), 5);
    lcd.setCursor(1, 0);
    //lcd.lcdPrintDec(millis(), 5);
    lcd.write(" ");
    lcd.lcdPrintBuffer();

    delay(1000);*/
  }
}
