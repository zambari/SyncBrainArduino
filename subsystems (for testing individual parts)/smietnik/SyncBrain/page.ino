
class PageAbstract
{
public:
//  Subpage subpages[1] = {Subpage()}; //1
  Subpage *activeSubpage;

  int activeSubPageIndex;

  virtual void PageAbstract::PushLabel()=0;// {    Serial.write('base');  } ; //PageAbstract::

  virtual bool PageAbstract::handleNext() = 0;

  virtual bool PageAbstract::handlePrev() = 0;

  virtual bool PageAbstract::setSubPageIndex(int i) = 0;

 // virtual void PageAbstract::clearRefreshFlag() = 0;

  //virtual char *PageAbstract::GetContent() = 0;
  //virtual
  virtual void PageAbstract::AdvanceStep() = 0;
};
class Subpage
{
public:
  char *subLabel = " xx"; //unty editor only
  Subpage()
  {
    subLabel = "SUBp1";
  }

  virtual char *Subpage::GetLabel()
  {
    return subLabel;
  }
  virtual char *Subpage::GetContent()
  {
    return (char *)"subcontent";
  }
};

class PageBase : public PageAbstract
{
public:
//  Subpage subpages[1] = {Subpage()}; //1
  Subpage *activeSubpage;

  int activeSubPageIndex;

   void PageBase::PushLabel() override {};// {    Serial.write('base');  } ; //PageBase::

   bool PageBase::handleNext() override {};

   bool PageBase::handlePrev()  override {};

   bool PageBase::setSubPageIndex(int i) override {};

 // virtual void PageBase::clearRefreshFlag() = 0;

  //virtual char *PageBase::GetContent() = 0;
  //virtual
   void PageBase::AdvanceStep() override {};
};
class  Pagetttt : public PageBase
{
public:

   bool Pagetttt::handleNext()override {return true;} 

   bool Pagetttt::handlePrev()override {return true;} 

   bool Pagetttt::setSubPageIndex(int i) override {return true;} 

 // virtual void PageBase::clearRefreshFlag() = 0;

   //char *PageBase::GetContent(){};
  //virtual
   void Pagetttt::AdvanceStep() override {};
};

class  Pagetttt : public PageAbstract
{
public:

   bool Pagetttt::handleNext()override {return true;} 

   bool Pagetttt::handlePrev()override {return true;} 

   bool Pagetttt::setSubPageIndex(int i) override {return true;} 

 // virtual void PageAbstract::clearRefreshFlag() = 0;

   //char *PageAbstract::GetContent(){};
  //virtual
   void Pagetttt::AdvanceStep() override {};
};
class  Paget1 : public Pagetttt
{
public:
//  Subpage subpages[1] = {Subpage()}; //1
//  Subpage *activeSubpage;


   void Paget1::PushLabel() override { 
 lcd.setCursor(0,0);
 lcd.write("fdfds");
     Serial.write('t');
   } // {    Serial.write('base');  } ; //PageAbstract::

   bool Paget1::handleNext()override {return true;} 

   bool Paget1::handlePrev()override {return true;} 

   bool Paget1::setSubPageIndex(int i) override {return true;} 

 // virtual void PageAbstract::clearRefreshFlag() = 0;

   //char *PageAbstract::GetContent(){};
  //virtual
   void Paget1::AdvanceStep() override {};
};


class  Paget2 : public Pagetttt
{
void Paget2::PushLabel() override {
 lcd.setCursor(0,0);
 lcd.write("22222");
  Serial.write('c');
 } // {    Serial.write('base');  } ; //PageAbstract::


};

class Page : public PageAbstract
{
  int subpageLength = 4;

public:
  bool requestRedrawFlag;
  bool wantsSteps = true;

  bool Page::setSubPageIndex(int i) override
  {
    if (i >= subpageLength || i <= 0)
    {
      return false;
    }
 //   activeSubPageIndex = i;
//    activeSubpage = &subpages[activeSubPageIndex];
   // requestRedrawFlag = true;
    return true;
  }

  //virtual
  void Page::PushLabel() override
  {
    lcd.setCursor(0,0);
    lcd.write("sss");
    Serial.write('x');
  }
  char *Page::GetContent() 
  {
    return (char *)"---";
  }
  void Page::AdvanceStep() override
  {
    //  Serial.write(GetLabel());
  }

  bool Page::handleNext() override
  {
    Serial.write("Page::handleNext()");

    Serial.write(activeSubPageIndex);
    return true;
  //  return setSubPageIndex(activeSubPageIndex + 1);
  }
  bool Page::handlePrev() override
  {
    Serial.write(" Page::handlePrev(");
    return true;
 //   return setSubPageIndex(activeSubPageIndex - 1);
  }

  Page() /// create your supage layuout
  {
    //  subpageLength = 1;
  //  activeSubpage = &subpages[0];
  }
};

///////////////////////////

class PageBPMSub1 : public Subpage
{
public:
  PageBPMSub1()
  {
    //  subLabel = (char *)"bs1";
  }
  const char *lbl = "bpm2 content \0";
  char *PageBPMSub1::getContent()
  {
    return lbl;
  }
};

class PageBPMSub2 : public PageBPMSub1
{
public:
  PageBPMSub2()
  {
    //  subLabel = (char *)"PageBPMSub2";
  }

  /*  public override string subLabel { get { 
           return  "bbs2";
}
}
    */
};
class PageBPM : public Page 
{
/*
  void PageBPM::PushLabel() override
  {
    lcd.setCursor(0,0);
    lcd.write("cxcx");
   // Serial.write(" \n\nBPTM BPMT ");
  }
*/
};
/*
class PageBPM : public Page  ,public PageAbstract
{
public:
  Subpage subpages[2] = {PageBPMSub1(), PageBPMSub2()};
  PageBPM() //: Page(),PageBPMSub1(),PageBPMSub2()
  {
    Serial.write(" bpm constructor called");
    //  //setSubPageIndex(activeSubPageIndex + 1);
    //  subpages[0] =  PageBPMSub1();
    //  subpages[1] =  PageBPMSub2();
  }
  char *PageBPM::GetLabel()// override
  {
    return (char *)" BPM ";
  }
  char *PageBPM::GetContent() override
  {
    return (char *)"bbbsss";
  }

  void PageBPM::PushLabel() override
  {
    Serial.write("cxcxcxc");
    // lcd.setCursor(3);
    // lcd.write("aaa");
  }
  bool PageBPM::handlePrev() override
  {
    Serial.write(" PageBPM::handlePrev() ");
    return setSubPageIndex(activeSubPageIndex - 1);
  }
  bool PageBPM::handleNext() override
  {
    Serial.write("r   PageBPM::handleNext()  ");

    Serial.write(activeSubPageIndex);
    return setSubPageIndex(activeSubPageIndex + 1);
  }
};*/

/////////////////////////
//Page pages[] = { PageBPM(),Page(), PageBPM()};
byte pageCount = 3;
PageAbstract *activePage;
bool udpateDisplayFlag = false;
byte activePageIndex = 0;

Paget1 pages[] = {   Paget1(),
                     Paget1(),
                     Paget1(),
                     Paget1(), };


/*


class Subpage
{
public:
  char *subLabel = " xx"; //unty editor only
  Subpage()
  {
    subLabel = "SUBp1";
  }

  virtual char *Subpage::GetLabel()
  {
    return subLabel;
  }
  virtual char *Subpage::GetContent()
  {
    return (char *)"subcontent";
  }
};

class PageAbstract
{
public:
  Subpage subpages[1] = {Subpage()}; //1
  Subpage *activeSubpage;

  int activeSubPageIndex;

  virtual void PageAbstract::PushLabel() {
    Serial.write('base');

  } ; //PageAbstract::

  virtual bool PageAbstract::handleNext() = 0;

  virtual bool PageAbstract::handlePrev() = 0;

  virtual bool PageAbstract::setSubPageIndex(int i) = 0;

 // virtual void PageAbstract::clearRefreshFlag() = 0;

  virtual char *PageAbstract::GetContent() = 0;
  //virtual
  virtual void PageAbstract::AdvanceStep() = 0;
};

class Page : public PageAbstract
{
  int subpageLength = 4;

public:
  bool requestRedrawFlag;
  bool wantsSteps = true;
  bool Page::setSubPageIndex(int i) override

  {
    if (i >= subpageLength || i <= 0)
    {
      return false;
    }
    activeSubPageIndex = i;
    activeSubpage = &subpages[activeSubPageIndex];
    requestRedrawFlag = true;
    return true;
  }

 // char Page::*GetLabel() override {}

  //virtual
  void Page::PushLabel() override
  {
    //l  cd.setCursor(0,0);
   /// lcd.write("ahaha");
    Serial.write("sth");
    // lcd.setCursor(3);
    // lcd.write("aaa");
  }
  char *Page::GetContent() override
  {
    return (char *)"---";
  }
  //virtual
  void Page::AdvanceStep() override
  {
    //  Serial.write(GetLabel());
  }

  bool Page::handleNext() override
  {
    Serial.write("Page::handleNext()");

    Serial.write(activeSubPageIndex);
    return true;
  //  return setSubPageIndex(activeSubPageIndex + 1);
  }
  bool Page::handlePrev() override
  {
    Serial.write(" Page::handlePrev(");
    return true;
 //   return setSubPageIndex(activeSubPageIndex - 1);
  }

  Page() /// create your supage layuout
  {
    //  subpageLength = 1;
    activeSubpage = &subpages[0];
  }
};

///////////////////////////

class PageBPMSub1 : public Subpage
{
public:
  PageBPMSub1()
  {
    //  subLabel = (char *)"bs1";
  }
  const char *lbl = "bpm2 content \0";
  char *PageBPMSub1::getContent()
  {
    return lbl;
  }
};

class PageBPMSub2 : public PageBPMSub1
{
public:
  PageBPMSub2()
  {
    //  subLabel = (char *)"PageBPMSub2";
  }

  /*  public override string subLabel { get { 
           return  "bbs2";
}
}
    */
//};
////class PageBPM : public Page 
//{
/*
  void PageBPM::PushLabel() override
  {
    lcd.setCursor(0,0);
    lcd.write("cxcx");
   // Serial.write(" \n\nBPTM BPMT ");
  }
*/
//};
/*
class PageBPM : public Page  ,public PageAbstract
{
public:
  Subpage subpages[2] = {PageBPMSub1(), PageBPMSub2()};
  PageBPM() //: Page(),PageBPMSub1(),PageBPMSub2()
  {
    Serial.write(" bpm constructor called");
    //  //setSubPageIndex(activeSubPageIndex + 1);
    //  subpages[0] =  PageBPMSub1();
    //  subpages[1] =  PageBPMSub2();
  }
  char *PageBPM::GetLabel()// override
  {
    return (char *)" BPM ";
  }
  char *PageBPM::GetContent() override
  {
    return (char *)"bbbsss";
  }

  void PageBPM::PushLabel() override
  {
    Serial.write("cxcxcxc");
    // lcd.setCursor(3);
    // lcd.write("aaa");
  }
  bool PageBPM::handlePrev() override
  {
    Serial.write(" PageBPM::handlePrev() ");
    return setSubPageIndex(activeSubPageIndex - 1);
  }
  bool PageBPM::handleNext() override
  {
    Serial.write("r   PageBPM::handleNext()  ");

    Serial.write(activeSubPageIndex);
    return setSubPageIndex(activeSubPageIndex + 1);
  }
}; 

/////////////////////////
//Page pages[] = { PageBPM(),Page(), PageBPM()};
byte pageCount = 3;
PageAbstract *activePage;
bool udpateDisplayFlag = false;
byte activePageIndex = 0;

PageAbstract pages[] = {Page(), PageBPM(),Page()};

*/