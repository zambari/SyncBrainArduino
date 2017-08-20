


Page_Sys a = Page_Sys();
Page_Diag b = Page_Diag();

void setUpPages()
{
    

  pages->add(&analyzer);
  pages->add(&clock);
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
        debug("\ncreated \n\n");
        debug(activePage->GetLabel());

        for (int i = 0; i <pageCount; i++)
        {      pages->get(i)->populateSubPages();
            debug("\n other pages:");
            debug(pages->get(i)->GetLabel());  
            debug(" has subs : ");
      
            debug( pages->get(i)->GetSubpageCount() ); 
            debug(" has subs : ");
            
                  debug( pages->get(i)->subPageCount ); 
            debug(" fisrt sub is: ");
            debug( pages->get(i)->GetSubpage(0)->GetLabel() ); 
            debug(" \n ");
          // =pages->get(i)->subPages->size();



        }
        activePage->GetSubpage(0)->PrintContent(); //
        delay(300);
        debug("lested \n");

   
        debug("listing \n");
  
  for (int i = 0; i < activePage->GetSubpageCount() ; i++)
  {
    debug("\n subpage ");
    debug(i);
      debug(" - ");
    
    lcd.clearLine(0);
  

    lcd.pushBuffer();

    
  }
  delay(300);
  debug("lested \n");
}
