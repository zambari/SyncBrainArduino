class SubPage
{
   public:
   char displayLine[16];
   char *buf=*displayLine;
  virtual char * getLabel();
  virtual void OnButtonPress(int buttonNr)
  {
  }
  virtual void  getContent()
  {
  }

};

