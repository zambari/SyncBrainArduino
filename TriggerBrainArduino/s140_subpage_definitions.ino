/*class subB : public PageView
{
public:
 
     char* GetLabel () override    {

        return ("BBB");
    } 
};

*/
class PageSubSys1 : public PageView
{
public:
     char * GetLabel() override { return "sub1";};
     void OnButtonPress(int buttonNr) override {}
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);
         lcd.print("hello");
    }
};
class SubPageDiag : public PageView
{
public:
     char * GetLabel() override { return "dia";};
     void OnButtonPress(int buttonNr) override {}
     
     void  PrintContent( ) override
     {
         lcd.clearLine(1);
         lcd.print("dfdfdfd");
    }
};
