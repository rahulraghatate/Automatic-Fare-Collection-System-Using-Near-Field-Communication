#include<SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
int i,incomingByte;

void setup(){
  mySerial.begin(19200);
  Serial.print("First\n");
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  
  Serial.print("First\n");

  //Initialise module
  mySerial.write(0xAA);
  mySerial.write(0xBB);
  mySerial.write(0x06);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(0x01);
  mySerial.write(0x01);
  mySerial.write(0x03);
  mySerial.write(0x03);
  
  mySerial.print("\nInitialising module");
  for(i=0;i<10;i++){
    while(mySerial.available() == 0); 
      // read the incoming byte:
      incomingByte = mySerial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  
  mySerial.write(0xAA);
  mySerial.write(0xBB);
  mySerial.write(06);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(07);
  mySerial.write(01);
  mySerial.write((byte)0x00);
  mySerial.write(06);
  
  Serial.print("\nLED something");
  for(i=0;i<10;i++){
    while(mySerial.available() == 0); 
      // read the incoming byte:
      incomingByte = mySerial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  mySerial.write(0xAA);
  mySerial.write(0xBB);
  mySerial.write(06);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(0x0C);
  mySerial.write(01);
  mySerial.write(01);
  mySerial.write(0x0C);
  
  Serial.print("\nTurning ON antenna");
  for(i=0;i<10;i++){
    while(mySerial.available() == 0); 
      // read the incoming byte:
      incomingByte = mySerial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
      
   
  mySerial.write(0xAA);
  mySerial.write(0xBB);
  mySerial.write(0x06);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(0x01);
  mySerial.write(0x02);
  mySerial.write(0x52);
  mySerial.write(0x51);
  
  //aa bb 06 00 00 00 01 02 52 51
  
  Serial.print("\nCard request");
  for(i=0;i<12;i++){
    while(mySerial.available() == 0); 
      // read the incoming byte:
      incomingByte = mySerial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
   
  mySerial.write(0xAA);
  mySerial.write(0xBB);
  mySerial.write(0x05);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(0x02);
  mySerial.write(0x02);
  mySerial.write((byte)0x00);
  
  
  Serial.print("\nRead NUID");
  for(i=0;i<14;i++){
    while(mySerial.available() == 0); 
      // read the incoming byte:
      incomingByte = mySerial.read();

      // say what you got:
      Serial.print(" ");
      Serial.println(incomingByte, HEX);
  }
  
  mySerial.end();              
}
