#include <LinkedList.h>

class PageBase: public Page
{
public:
  uint16_t subPageIndex;
  uint16_t subPageCount;
  uint16_t thisPageIndex;
  bool wantsSerial;
                virtual char *GetLabel() 
                {
                  return "unnamed";
                }; // { return "my class"; }
                bool wantsNoters;


                /// IMPORTANT METHODS TO OVERLOAD
                virtual void populateSubPages(){}              // fill in your subpages here
                virtual void OnQuarterNote() { }               // recieved on next quareter note clock OnClockPulse

                virtual void OnSerial(char c)    {   }         // not implemented
                virtual void OnClockPulse() { }                // not implemented
            
                virtual void OnButtonPress(int buttonNr)       // handles interface reads
                {
                  activeSubPage->OnButtonPress(buttonNr);
                }

                virtual void OnGotFocus() { isActive=true; }
                virtual void OnLostFocus(){ isActive=false; }
              
      
                 bool setSubPage(int i)
                 { 
                       if (i<0||i>=subPageCount)    return false;
                          subPageIndex=i;
                          activeSubPage = subPages->get(subPageIndex);
                          requestLCDredraw = true;
                      return true;
                    }
                    virtual  int GetSubpageCount() 
                    
                                    {
                                      return subPageCount;
                                    }
                     PageView *GetSubpage(int i)  {
                                      return subPages->get(i);
                                    }
                    virtual bool handleRight()
                    {
                      return setSubPage(subPageIndex+1);
                    }

                    virtual bool handleLeft()
                    {
                      return setSubPage(subPageIndex-1);
                    }
                    virtual void handleButton(int buttnr)
                    {
                      
                    }

};

Page *activePage;

LinkedList<Page *> *pages = new LinkedList<Page *>();