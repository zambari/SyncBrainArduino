#include <LinkedList.h>

class Page
{
public:
                  LinkedList<SubPage *> *subPages = new LinkedList<SubPage *>();
                  SubPage *activeSubPage;
                  // CUSTOMIZABLE BEGIN

                  // you must overload this function for your page to have a namespace MyNamespace
                  virtual char *getLabel() = 0; // { return "my class"; }

                  // override this function to create layout for your pages
                  // it gets called by the constructor

                  virtual void populateSubPages() {}; // {
                                                  //  SubPage emptySubpage=SubPage();
                                                  //  subPages.Add(emptySubpage); // jsut in case you forget, you need at least one subpage

                  // ADD MRE PAGES HERE

                // this will get called on every clock pulse, use to do timing related stuff

                virtual void OnClockPulse()
                {
                }
                virtual void OnQuarterNote()
                {
                }

                // use this for interface
                virtual void OnButtonPress(int buttonNr)
                {
                  activeSubPage->OnButtonPress(buttonNr);
                }

                // CUSTOMIZABLE END

                // no need to touch much below that
                #pragma region semiPrivate
                // list of subpages
                #pragma endregion 
                uint16_t subPageIndex;
                uint16_t subPageCount;
                uint16_t thisPageIndex;

                void postLayout(int i)
                {
                  thisPageIndex = i;
                  subPageIndex = 0;
                  subPageCount = subPages->size();
                  activeSubPage = subPages->get(0);
                }
                  bool setSubPage(int i)
                    {
                          if (i<0||i>=subPageCount)  
                            return false;
                          subPageIndex=i;
                          activeSubPage = subPages->get(subPageIndex);
                          requestLCDredraw = true;
                      return true;
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
                      return setSubPage(subPageIndex-1);
                    }

};
