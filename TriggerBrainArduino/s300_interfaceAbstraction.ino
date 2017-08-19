

void ReloadSub()
{        Serial.write("\n sub page redraw \n");
        
        lcd.clearLine(0);
        lcd.print("Sub ");
        lcd.printDigit(activePage->subPageIndex+1);
        lcd.print("/");
        lcd.printDigit(activePage->subPageCount);
        lcd.print(" ");
        lcd.print(activePage->activeSubPage->getLabel());
        lcd.print("   ");
        lcd.clearLine(1);
      //  lcd.print(activePage->activeSubPage->getContent());
        lcd.commitBuffer();
     //   nextLcdRedrawTopTime=millis()+LCD_REFRESH_LAZY*2; // but we do not refresh it for now
   //     nextLcdRedrawBottomTime=millis()+LCD_REFRESH_LAZY;
      delayLcdRefresh(LCD_REFRESH_LAZY);
        DrawLayout();
        requestLCDredraw=true;

}

void delayLcdRefresh(int ms)
{
            nextLcdRedrawTopTime=millis()+ms; // but we do not refresh it for now
        nextLcdRedrawBottomTime=millis()+ms;
}
void ReloadSubFailed(int reason)
{      
        
        lcd.clearLine(0);
        if (reason==1)
            lcd.print("<-first ");
           else  
         if (reason==2)
            lcd.print(">- final subpage");
           else  
           lcd.print("reason unkonwon ");
        lcd.commitBufferTop();

        nextLcdRedrawTopTime=millis()+LCD_REFRESH_LAZY*2; // but we do not refresh it for now
        nextLcdRedrawBottomTime=millis()+LCD_REFRESH_LAZY;
        DrawLayout();
        requestLCDredraw=true;

}
void DrawLayout()
{
     lcd.clearLine(0);
        lcd.setCursor(0,0);
        lcd. printDigit(activePageIndex+1);
        lcd.print(':');
        lcd. printDigit(activePage->subPageIndex+1);
        lcd.print(' ');
        lcd.print(activePage->getLabel());
        lcd.print(':');
        lcd.print(activePage->activeSubPage->getLabel());   
        lcd.print("       ");
        lcd.clearLine(1);
     //   lcd.print(activePage->activeSubPage->getContent());
  
}
void ReloadPage()
{
        if (activePage==NULL) Serial.write("\nacive page null \n");
              if (&activePage==NULL) Serial.write("\nacive page &null \n");
    byte currentSubPageIndex=activePage->subPageIndex;
    Serial.write('\n');
    Serial.write(activePageIndex);
    Serial.write(" sdsioda s sdsd ");
    Serial.write(activePage->subPageIndex+'0');
    Serial.write('\n');
  /* activePage=pages->get(activePageIndex); //to robi blad
     //activePage->setSubPage(currentSubPageIndex); // lets try to keep our subpage
  Serial.write("\n page redraw \n");
        Serial.write(activePageIndex+'0');   
      lcd.clearLine(0);
        lcd.print("Page ");
        lcd.printDigit(activePageIndex+1);
        lcd.print("/");
        lcd.printDigit(pageCount);
        lcd.print(" ");
   //     lcd.print(activePage->getLabel());
        lcd.print("       ");
        lcd.setCursor(0,1);
        
        lcd.print("SubP ");
       // lcd.printDigit(activePage->subPageIndex+1);
        lcd.print("/");
      //  lcd.printDigit(activePage->subPageCount);
        lcd.print(" ");
        //lcd.print(activePage->activeSubPage->getLabel());
        lcd.print("       ");
*/
    
     //   lcd.commitBuffer();
        lcd.commitBuffer();
       nextLcdRedrawTopTime=millis()+LCD_REFRESH_LAZY; // but we do not refresh it for now
        nextLcdRedrawBottomTime=millis()+LCD_REFRESH_LAZY*2;
        DrawLayout();
  //byte count=0;

        
        // instead :
        
      
        requestLCDredraw=true;
   }

/*
void OnNextPage()
{
        activePageIndex++;
        if (activePageIndex >= pageCount)   activePageIndex =0;
        Serial.write("\n1next\n");
        ReloadPage();
}

void OnPrevPage()    {  
        activePageIndex--;
        if (activePageIndex <0)     activePageIndex =  pageCount-1 ;
        Serial.write("\nprev\n");
        ReloadPage();
}
void OnNavLeft()
{
         if ( activePage->handleLeft())     ReloadSub();
         else ReloadSubFailed(1);
}

void OnNavRight()
{  
        if (   activePage->handleRight())   ReloadSub();
          else ReloadSubFailed(2);
}

void OnPlayPress()
{
       Serial.write("\nplay\n"); 
}

void OnStopPress()
{  
      Serial.write("\nstip\n");
}

void OnTempoUp()
{  
Serial.write("\nDn\n");      
}

void OnTempoDn()
{  
      Serial.write("\nup\n");
}
void OnButtonPress(uint8_t butNr)
{
    activePage->handleButton(butNr);
   
}*/
