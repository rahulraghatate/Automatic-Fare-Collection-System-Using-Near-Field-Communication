int i,incomingByte;

void setup(){
  Serial.begin(19200);
}

void loop(){

  //Initialise module
  Serial.write(0xAA);
  Serial.write(0xBB);
  Serial.write(06);
  Serial.write(00);
  Serial.write(00);
  Serial.write(00);
  Serial.write(01);
  Serial.write(01);
  Serial.write(03);
  Serial.write(03);
  
  Serial.print("\nInitialising module");
  for(i=0;i<10;i++){
    while(Serial.available() == 0); 
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  
  Serial.write(0xAA);
  Serial.write(0xBB);
  Serial.write(06);
  Serial.write(00);
  Serial.write(00);
  Serial.write(00);
  Serial.write(07);
  Serial.write(01);
  Serial.write(00);
  Serial.write(06);
  
  Serial.print("\nLED something");
  for(i=0;i<10;i++){
    while(Serial.available() == 0); 
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  Serial.write(0xAA);
  Serial.write(0xBB);
  Serial.write(06);
  Serial.write(00);
  Serial.write(00);
  Serial.write(00);
  Serial.write(0x0C);
  Serial.write(01);
  Serial.write(01);
  Serial.write(0x0C);
  
  Serial.print("\nTurning ON antenna");
  for(i=0;i<10;i++){
    while(Serial.available() == 0); 
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
      
   
  Serial.write(0xAA);
  Serial.write(0xBB);
  Serial.write(0x06);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x01);
  Serial.write(0x02);
  Serial.write(0x52);
  Serial.write(0x51);
  
  //aa bb 06 00 00 00 01 02 52 51
  
  Serial.print("\nCard request");
  for(i=0;i<12;i++){
    while(Serial.available() == 0); 
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
   
  Serial.write(0xAA);
  Serial.write(0xBB);
  Serial.write(0x05);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x02);
  Serial.write(0x02);
  Serial.write(0x00);
  
  
  Serial.print("\nRead NUID");
  for(i=0;i<14;i++){
    while(Serial.available() == 0); 
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  Serial.end();              
}
