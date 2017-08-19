

#include <LinkedList.h>
Page *activePage;

LinkedList<Page *> *pages = new LinkedList<Page *>();
Page_Sys a = Page_Sys();
Page_Diag b = Page_Diag();

void setUpPages()
{
    
  pages->add(&clock);
  pages->add(&analyzer);
  pages->add(&a);

  pages->add(&b);
  /*
  D d = D();
  B b = B();
  C c = C();
  D d2 = D();
  B b2 = B();
  C c2 = C();
  pages->add(&c2);
  pages->add(&b);
  pages->add(&c);
  pages->add(&d);
  pages->add(&b2);
  pages->add(&c2);
  pages->add(&d2);
*/
        pageCount=pages->size();
        activePage=pages->get(0);
        Serial.print("\ncreated \n\n");
        Serial.print(activePage->GetLabel());

        for (int i = 0; i <pageCount; i++)
        {      pages->get(i)->populateSubPages();
            Serial.print("\n other pages:");
            Serial.print(pages->get(i)->GetLabel());  
            Serial.print(" has subs : ");
      
            Serial.print( pages->get(i)->GetSubpageCount() ); 
            Serial.print(" has subs : ");
            
                  Serial.print( pages->get(i)->subPageCount ); 
            Serial.print(" fisrt sub is: ");
            Serial.print( pages->get(i)->GetSubpage(0)->GetLabel() ); 
            Serial.print(" \n ");
          // =pages->get(i)->subPages->size();



        }
        activePage->GetSubpage(0)->PrintContent(); //
        delay(300);
        Serial.print("lested \n");

   
        Serial.print("listing \n");
  
  for (int i = 0; i < activePage->GetSubpageCount() ; i++)
  {
    Serial.print("\n subpage ");
    Serial.print(i);
      Serial.print(" - ");
    
    lcd.clearLine(0);
  

    lcd.commitBuffer();

    
  }
  delay(300);
  Serial.print("lested \n");
}
