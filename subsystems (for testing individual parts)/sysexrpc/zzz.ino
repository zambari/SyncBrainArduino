long nextMills;
long nextClk;

void loop() {
  
  while (Serial.available())
  {
    rpc.handleRpc(Serial.read());
  }
    if (millis()>nextMills)
  {
    
    nextMills=millis()+MIDI_ACTIVE_UPDATE_TIME;
    Serial.write(MIDI_ACTIVE_SENSE);
  }
  

}

