//NUID  Pay  Current_status  Passenger_count

import processing.serial.*;
Serial myPort; 
int[] rd = {0,0,0,0,0,0};
int eve=0;
Table data;

void setup() {


  // List all the available serial ports:
  println(Serial.list());

  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 19200); 
  myPort.clear(); 
  println("port detected");
  //initialise
  data = loadTable("db.csv", "header");
  //initialise comm with arduino
  for(int i=0;i<1;i++){
    for(int j=0;j<1000;j++){
      for(int k=0;k<1000;k++){
        for(int i1=0;i1<1000;i1++){
          for(int j1=0;j1<1000;j1++){}
        }
      }
    }
    println(i);
  }

  do{
    myPort.write(0xDD);
    println("Waiting");
    while(myPort.available() == 0);
    
    //print(eve);
  }while(rec() != 2);
  
  println("Initialised");
}

void draw(){
  //print("draw");
  //wait for data from arduino
  //while(myPort.available() == 0);
  if(rec() == 1){
    println("Event");
    String id = str(rd[2])+ str(rd[3])+ str(rd[4])+ str(rd[5]);
    println(id);
    if (rd[0] == 0xA0){
      //Make new account
      newAcc(id);
      myPort.write(0x00);
      println("New Acc created");
    }
    else{
      println("NUID search");
      //search for NUID
      TableRow row = data.matchRow(id, "NUID");
      if (row != null) {
        println("Match found");
        int header = rd[0]&0xF0;
        int number = rd[0]&0x0F;
        if (header == 0x00) {
          println("Entry");
          //Entry
          //store stn, number of passengers
          row.setInt("Status", rd[1]);
          row.setInt("Count", number);
          saveTable(data, "db.csv");
          //give confirmation
          myPort.write(0x00);
          println("Entry done");
        }

        else if (header == 0x50) {
          println("Exit");
          //Exit
          //find number of passengers and stn
          int stn1 = rd[1];
          int stn0 = row.getInt("Status");
          number = row.getInt("Count");
          int bal = row.getInt("Balance");
          //calculate fare and update the account
          int newbal = fare(stn1, stn0, number, bal);
          row.setInt("Balance", newbal);
          row.setInt("Status", 0x00);
          row.setInt("Count", 0x00);
          saveTable(data, "db.csv");
          //send passenger number as response
          myPort.write(number);
          println("Exit done");
        }

        else if (header == 0xA0) {
          println("Recharge");
          //Recharge
          //calculate new amount
          int amt = number*50;
          amt = amt + row.getInt("Balance");
          //update database
          row.setInt("Balance", amt);
          saveTable(data, "db.csv");
          //send confirmation
          myPort.write(0x00);
          println("Recharge done");
        }
      }
      else{
        println("No match");
        myPort.write(0xFF);
      }
    }
  }
//noLoop();
}

/*void serialEvent(Serial myPort) {
  //println("serialEvent");
  int x = myPort.read();
  if(x == 0xDD) eve = 2;
  else if(x != 0xCC) println(hex(x,2));
  else{
    println("info");
    for(int i=0;i<6;i++){
      rd[i] = myPort.read();
      println(hex(rd[i],2));
    }
    eve = 1;
  }
  //println(eve);
//  print("  serialEvent exit");
}*/


int rec() {
  int x = myPort.read();
  if(x == 0xDD) return 2;
  else if(x != 0xCC){
    //println("check");
    //println(hex(x,2));
    return 0;
  }
  println("info");
  for (int i=0;i<6;i++) {
    while (myPort.available () == 0);
    rd[i] = myPort.read();
    //println(hex(rd[i],2));
  }
  return 1;
}

int fare(int dest, int source, int pass, int amt) {
  println("fare");
  println("fare exit");
  return(amt-(5*pass*(dest - source)));
}

void newAcc(String id) {
  println("newAcc");
  //add new entry to database
  TableRow acc = data.addRow();
  //set default values
  acc.setString("NUID", id);
  acc.setInt("Balance", ((rd[0]&0x0F)*50));
  acc.setInt("Status", 0x00);
  acc.setInt("Count", 0x00);
  saveTable(data, "db.csv");
  println("Account created");
  println(id);
}

