// DS1302_Serial_Hard 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS1302-library to 
// retrieve time- and date-date for you to manipulate.
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 2  reset
//          I/O pin   -> Arduino Digital 3  dat
//          SCLK pin  -> Arduino Digital 4  clk

#include <DS1302.h>

// Init the DS1302
// DS1302 rtc(2, 3, 4);  //changed pins; pins for tsta 2 4 8 and 6 
DS1302 rtc(2, 4, 8);  //for nanoevery

// Init a Time-data structure
Time t;

void setup()
{
    // Setup Serial connection
  Serial.begin(9600); 
//   Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
// The following lines can be commented out to use the values already stored in the DS1302
  /*  
  rtc.setDOW(TUESDAY);        // Set Day-of-Week to FRIDAY;  For UK pu tit as normal time summer shouls 0.5 forwards
  rtc.setDate(23,10,2026);   // Set the date to August 6th, 2010
  rtc.setTime(14,29,30);     // Set the time to 12:00:00 (24hr format) USE TIME
  */ 
//   wntr crk +70
//   wntr lnd +50
//  rtc.setDate(12,3,2023);   // Set the date to August 6th, 2010
//  rtc.setTime(19,44,30);     // Set the time to 12:00:00 (24hr format) USE TIME
  Serial.print("\n \n STARTING \n    Seeded   ");
  randomSeed(analogRead(0));
  Serial.println(random(1000));
}

void loop()
{
  // Get data from the DS1302
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(t.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" ");
  Serial.print(t.year, DEC);
  Serial.print(". ");
  Serial.print(t.date, DEC);  Serial.print("/");
  Serial.print(t.mon, DEC);  Serial.print("/");
  Serial.print(t.year, DEC);
  Serial.println("/ ");
  
  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(t.dow, DEC);
  Serial.print(". day of the week and ");
  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.print(t.sec, DEC);
  Serial.print(" ");
   float dyr=OrdDt(t.year,t.mon,t.date); 
  Serial.print(dyr);
  Serial.println(" ");
   int dfa,dfb,snMr,snOk;
snMr=91;  //    OrdDt(t.year,3,Sprng(t.year,1)); //snMr=91;   //
snOk=302; //    OrdDt(t.year,10,Sprng(t.year,-1));  //snOk=302;  //
   dfa=dyr-(snMr-1); dfb=dyr-(snOk-0); 
   Serial.print(dfa);Serial.print(" <dfa,dfb> "); Serial.print(dfb); Serial.print(" delay ");
   float phs=2*3.141592653589793*(dyr-162.2)/365.8; phs=cos(phs); phs=2.75*60*phs;
   if(dfa*dfb<0)Serial.print("Summer");
   else Serial.print("winter");
   Serial.println(" ");
   Serial.print(dyr);Serial.print(" phs ");Serial.println(phs);Serial.println(dfa*dfb); 
  // Send a divider for readability
  Serial.println(" "); 
  for(int ia=0; ia<20; ia++)
   {
    Serial.print(random(0,21)); Serial.print(" ");
    }
   Serial.print(" \n");
  // Wait random seconds before repeating :)
//  delay (random(60000,600000));
  delay (10000);
}

float OrdDt(int yr,int mn,int tg) {
  float tgn;
  tgn=(mn-1)*31+tg;
  if(mn>2){
     if(yr%4<.1){
      tgn=tgn-2;
     }
    else
     {
      tgn=tgn-3;
     }
    }
  if(mn>4){
     tgn=tgn-1;
    }
  if(mn>6){
     tgn=tgn-1;
    }
  if(mn>9){
     tgn=tgn-1;
    }
  if(mn>11){
     tgn=tgn-1;
    }
  return tgn;
}
 
int Sprng(int yr,int swt) {
  int spr,shf;
  spr=0;
  shf=(yr-20-yr%4)/4;
  if(swt>0){
    spr=31-(yr+3+shf)%7;
   }
  if(swt<0){
    spr=31-(yr+shf)%7;
   }
  return spr;
}
