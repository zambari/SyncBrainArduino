

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
                virtual void OnSerial(char c)
              {

              }
                 virtual void OnClockPulse()
                {
                }
                virtual void OnQuarterNote() 
                {
                }
                virtual void OnButtonPress(int buttonNr)
                {
                  activeSubPage->OnButtonPress(buttonNr);
                }
               
                #pragma region semiPrivate
                // list of subpages
                #pragma endregion 
        
                virtual void populateSubPages(){}
      
                  bool setSubPage(int i)
                    { Serial.print("subp ");
                
                          if (i<0||i>=subPageCount)  
                            return false;
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
                      ;
                    }

};
