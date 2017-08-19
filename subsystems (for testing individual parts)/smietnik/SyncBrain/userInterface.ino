
int interfaceStatus;
int lastInterfaceRead = 0;
int interfaceRead;
int statusLed = 0;

void checkInterface()
{
    digitalWrite(interfaceShiftPin, LOW);
    digitalWrite(interfaceShiftPin, HIGH);
    // statusLed=interfaceRead;
    interfaceRead = 0; //reset status just in case

    //  READ FROM INTERFACE Serial input BEGIN
    for (int i = 0; i < 16; i++)
    {
        byte but1 = digitalRead(interfaceDataPin);
        interfaceRead = (interfaceRead << 1) + but1;
        digitalWrite(interfaceLedPin, ((statusLed >> i) & 1));
        interfaceClk();
    } //  READ FROM INTERFACE input END

    interfaceStatus = interfaceRead;
    // KEYBOARD BEGIN
    if (lastInterfaceRead != interfaceRead) // If keyboard has changed
    {
        // add shift in handlebuttons i guess
        lastInterfaceRead = interfaceRead;
        handleButtonStateChange();
    }
}

void interfaceClk()
{
    digitalWrite(interfaceClockPin, LOW);
    digitalWrite(interfaceClockPin, HIGH);
    // shift registers are really quick so we dont need any additional delays here - not on my  74hct at least
}

void debugFlash()
{
    statusLed = statusLed ^ LED_AUX_1;
    // debugLedCounter2=10;
}

void handleButtonStateChange()
{
    /// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  STRETCH BUTTONS BEGIN
    ///lcdw
     Serial.write("zeroacin   ");
    if (interfaceStatus & BUTTON_MENU_UP)
    {
        //   handleSubScreenChange(-1);
        activePageIndex--;

        if (activePageIndex < 0)
        {
            Serial.write("zeroacin   ");
            Serial.write(activePageIndex);
            activePageIndex = 0;
        }

        activePage =& pages[activePageIndex];
        udpateDisplayFlag = true;
    }
    if (interfaceStatus & BUTTON_MENU_DOWN)
    {

        //  handleSubScreenChange(1);
        activePageIndex++;
        if (activePageIndex >= pageCount)
            activePageIndex = pageCount - 1;

        activePage = &pages[activePageIndex];
        udpateDisplayFlag = true;
        Serial.write("\n activePageIndex ");
        Serial.write('0' + activePageIndex);
        Serial.write("   subpage ");
        Serial.write('0' + activePage->activeSubPageIndex);
    }
    if (interfaceStatus & BUTTON_MENU_LEFT)

    {

        udpateDisplayFlag = true;
        Serial.write(" \n activePageIndex ");
        Serial.write('0' + activePageIndex);
        Serial.write("   ");
        Serial.write("   subpage ");
        Serial.write('0' + activePage->activeSubPageIndex);
        Serial.write("  \n");
        activePage->handlePrev();
        //  handleParamChange(-1);
    }
    if (interfaceStatus & BUTTON_MENU_RIGHT)
    {
        (*activePage).handleNext();
        udpateDisplayFlag = true;
        Serial.write(" \n ->>activePageIndex is ");
        Serial.write('0' + activePageIndex);
        Serial.write(activePage->activeSubpage->GetLabel());
        Serial.write("   subpage ");
        Serial.write('0' + activePage->activeSubPageIndex);
        Serial.write("  \n");
        //  handleParamChange(1);
    }
    if (interfaceStatus & BUTTON_TEMPO_UP)
    {
        //   handleTempoChange(-1);
    }
    if (interfaceStatus & BUTTON_TEMPO_DOWN)
    {
        //  handleTempoChange(1);
    }
    if (interfaceStatus & BUTTON_TEMPO_PLAY)
    {
        //    handlePlay();
    }
    if (interfaceStatus & BUTTON_TEMPO_STOP)
    {
        //   handleStop();
    }
}