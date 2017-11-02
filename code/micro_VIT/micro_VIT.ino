#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

const int ini[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x01,0x01,0x03,0x03},
    inir[10] = {0xAA,0xBB,0x06,0x00,0x11, 0x12,0x01,0x01,0x00,0x03},
    antON[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x0C,0x01,0x01,0x0C},
    antONr[10] = {0xAA,0xBB,0x06,0x00,0x11,0x12,0x0C,0x01,0x00,0x0E}, /*0x0E = 14*/
    req[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x01,0x02,0x52,0x51},
    rNUID[9] = {0xAA,0xBB,0x05,0x00,0x00,0x00,0x02,0x02,0x00},
    redOFF[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x07,0x01,0x00,0x06},
    redON[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x07,0x01,0x01,0x07},
    redr[10] = {0xAA,0xBB,0x06,0x00,0x11,0x12,0x07,0x01,0x00,0x05},
    hlt[9] = {0xAA,0xBB,0x05,0x00,0x00,0x00,0x04,0x02,0x06},
    hltr[10] = {0xAA,0xBB,0x06,0x00,0x11,0x12,0x04,0x02,0x00,0x05},
    STN=3;
int rd[15];
volatile int mode=3, number=1;
    
    
void setup(){
  noInterrupts();
  
  attachInterrupt(3, DMode, RISING);
  attachInterrupt(2, DNumber, RISING);
  Serial.begin(19200);
  Serial1.begin(19200);
  lcd.begin(16, 2);
  //lcd.print("hello");
  int xx=0;
  while(xx == 0){
    while(Serial.available() == 0){
    }
    if(Serial.read() == 0xDD){
      Serial.write(0xDD);
      xx = 1;
    }
  }
    
  //Initialise module
  do{
    rftran(ini, 10);
  }while(check(inir, 10) == 1);
  
  //Turn ON antenna
  do{
    rftran(antON, 10);
  }while(check(antONr, 10) == 1);
  
  interrupts();
}

void loop(){
  
  //Request a card
  lcd.clear();
  lcd.print("Put tag on reader");
  lcd.setCursor(0,1);
  lcd.print(number,DEC);
  rftran(req, 10);
  int x = rfrec();
  
  if(x == 0){
    //Read NUID
    rftran(rNUID, 9);
    x = rfrec();
    if(x == 0){
      //4 cases
      noInterrupts();
      //Entry
      if(mode == 1/*(M1 == 0)&&(M0 == 0)*/){
        int head = 0x00^number;
        int info[] = {0xCC, head, STN, rd[9], rd[10], rd[11], rd[12]};
        pctran(info, 7);
        while(Serial.available() == 0);
        if(Serial.read() == 0x00){
          lcd.clear();
          lcd.print("Entry successful");
          lcd.setCursor(0,1);
          lcd.print(number,DEC);
        } //allow
        else{
          lcd.clear();
          lcd.print("Error");
        }
        //restrict
      }
      
      //Exit
      else if(mode == 2/*(M1 == 0)&&(M0 == 1)*/){
        int head = 0x50;
        int info[] = {0xCC, head, STN, rd[9], rd[10], rd[11], rd[12]};
        pctran(info, 7);
        while(Serial.available() == 0);
        int x = Serial.read();
        if((x^0xF0)==0x00){
          lcd.clear();
          lcd.print("Exit done");
          lcd.setCursor(0,1);
          lcd.print((x^0x0F),DEC);
        }//allow
        else{
          lcd.clear();
          lcd.print("Error");
        }
      }

      //Recharge-New
      if(mode == 3)/*((M1 == 1)&&(M0 == 0))*/{
        //Serial.write(0x13);
        int head = 0xA0^number;
        int info[] = {0xCC, head, STN, rd[9], rd[10], rd[11], rd[12]};
        pctran(info, 7);
        while(Serial.available() == 0);
        int x = Serial.read();
        if((x&0xF0) == 0x00){
          lcd.clear();
          lcd.print("Recharge-New done");
          lcd.setCursor(0,1);
          lcd.print((x^0x0F),DEC);
        }//allow
        else{
          lcd.clear();
          lcd.print("Error");
        }
        //restrict
      }
      
      //Initialise module
      do{
        rftran(ini, 10);
      }while(check(inir, 10) == 1);
  
      //Turn ON antenna
      do{
        rftran(antON, 10);
      }while(check(antONr, 10) == 1);
      
      interrupts();
    }
  }
}

void rftran(const int* data, int count){
  for(int i=0;i<count;i++){
    Serial1.write(data[i]);
  }
}

void pctran(int* data, int count){
  for(int i=0;i<count;i++){
    Serial.write(data[i]);
  }  
}

int check(const int* data, int count){
  int x = 0;
  for(int i=0;i<count;i++){
    while(Serial1.available() == 0); 
    if(data[i] != Serial1.read()) x = 1;
  }
  //Serial.write(0xBB);
  return(x);
}

int rfrec(){
  //Serial.write(0x30);
  while(Serial1.available() == 0);
  rd[0] = Serial1.read();
  if(rd[0] != 0xAA) return(1);
  //Serial.write(0x31);
  while(Serial1.available() == 0);
  rd[1] = Serial1.read();
  if(rd[1] != 0xBB) return(1);
  //Serial.write(0x32);
  while(Serial1.available() == 0);
  rd[2] = Serial1.read();
  int count = rd[2] + 0x04;
  //Serial.write(count);
  for(int i=3;i<count;i++){
    while(Serial1.available() == 0);
    rd[i] = Serial1.read();
    //Serial.write(rd[i]);
  }
  //Serial.write(0x34);
  int x = 0x00;
  for(int i=4;i<=(count-1);i++) x = x^rd[i];

  if((rd[count] != x) || (rd[8] != 0)){
    //Serial.write(0x35);
    return(1);
  }
  else{
    //Serial.write(0x36);
    return(int(0));
  }
}

void DMode(){
  noInterrupts();
  mode = mode + 1;
  lcd.clear();
  lcd.print("Mode ");
  lcd.print(mode,DEC);
  delay(1000);
  interrupts();
}

void DNumber(){
  noInterrupts();
  number = number + 1;
  lcd.setCursor(0,1);
  lcd.print(number,DEC);
}
