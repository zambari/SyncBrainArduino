class subB : public SubPage
{
public:
 
     char* getLabel () override    {

        return ("BBB");
    } 
};


class PageSubSys1 : public SubPage
{
public:



  void getContent() override
  {
     /* int p=pulseCount;
char a='0'+p%10;
p/=10;
char b='0'+p%10;
p/=10;
char c='0'+p%10;
char *abc[]={&a,&b,&c};*/
displayLine[0]='a';
displayLine[1]='b';
displayLine[2]='h';
     // return *buf;
  }
   char* getLabel () override    {

        return ("sys1");
    } 
};


class PageSubSys2 : public SubPage
{
public:



  void getContent() override
  {
      
      char buf[16];

    //  return buf;
  }

   char* getLabel () override    {

        return ("sys2");
    } 
};


class PageSubSys3 : public SubPage
{
public:


   char* getLabel () override    {

        return ("sys3");
    } 
};

class subC : public SubPage
{
public:



   char* getLabel () override    {

        return ("CCC");
    } 
};

class subD : public SubPage
{
public:

 // A() {}   
 char* getLabel () override    {
        return ("DDD");
    } 
 
};


class settingPage : public SubPage
{
public:

 // A() {}   
 char* getLabel () override    {

        return ("DDD");
    } 
 
};
