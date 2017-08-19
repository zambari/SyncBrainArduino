//#include <LinkedList.h>


class Page_Sys : public PageBase
{
   PageSubSys1 a;
   PageSubSys1 b;
   PageSubSys1 c;
public:
  
 void populateSubPages() override 
{ 
       subPages->add(&a);
     subPages->add(&b);
           subPages->add(&c);
           subPageIndex = 0;
           subPageCount = subPages->size();
           activeSubPage = subPages->get(0);
}
   void handleButton(int buttnr) override
    {
            Serial.write("\n systembtBn");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
 // void test() override { Serial.write('B'); }
 char *GetLabel() override
 {
   return "SYS";
 }
};

class Page_Diag : public PageBase
{   
   SubPageDiag a;
   
   SubPageDiag b;
   SubPageDiag c;
public:

 void populateSubPages() override 
{  
       subPages->add(&a);
       subPages->add(&b);
       subPages->add(&c);
     
           subPageIndex = 0;
           subPageCount = subPages->size();
           activeSubPage = subPages->get(0);
}
   void handleButton(int buttnr) override
    {
            Serial.write("\n diagbt");
            Serial.write('0'+buttnr);
            Serial.write("\n");
    }
  char *GetLabel() override
  {
    return "Diag";
  }
};