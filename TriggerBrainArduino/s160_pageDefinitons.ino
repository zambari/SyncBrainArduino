//#include <LinkedList.h>


class Page_Sys : public Page
{
 //  PageSubSys1 a;
  //    PageSubSys2 b;
  //       PageSubSys3 c;



public:
 void populateSubPages() override 
{
       // subPages->add(&a);
      //   subPages->add(&b);
       //     subPages->add(&c);
}
   void handleButton(int buttnr) override
    {
            Serial.write("\n systembtBn");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
 // void test() override { Serial.write('B'); }

  char *getLabel() override
  {
    return "System";
  }
};


class B : public Page
{
                subB sb = subB();
                subB sC = subB();

public:
 void populateSubPages() override 
{
      //  subPages->add(&sb);
      //  subPages->add(&sC);
        subPages->add(&sb);
        subPages->add(&sC);
}
   void handleButton(int buttnr) override
    {
            Serial.write("\n Bn");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
 // void test() override { Serial.write('B'); }

  char *getLabel() override
  {
    return "pageB";
  }
};

class C : public Page
{

                        subC sb = subC();
                        subC sC = subC();
                        subB sB = subB();
                        subB sB2 = subB();
                        subD sD = subD();
                        subD sD2 = subD();

public:
   void handleButton(int buttnr) override
    {
            Serial.write("\n Cn");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
 
 void populateSubPages() override 
{
        subPages->add(&sb);
        subPages->add(&sC);
        subPages->add(&sB);
        subPages->add(&sD);
  }

int ledCount;

  bool handleRight() override
    { 
     

      return setSubPage(subPageIndex+1);
    }

  bool handleLeft() override
    {
      return setSubPage(subPageIndex-1);
    }
  char *getLabel() override
  {
    return "MIGACZ ";
  }
};
class D : public Page
{
                subD dd = subD();
                subD dd2 = subD();

public:
 void populateSubPages() override 
{
    subPages->add(&dd);
    subPages->add(&dd2);
    subPages->add(&dd);
    subPages->add(&dd2);

    subPages->add(&dd);
    subPages->add(&dd2);
  }
   void handleButton(int buttnr) override
    {
            Serial.write("\n btn");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
  char *getLabel() override
  {
    return "pageD";
  }
};
