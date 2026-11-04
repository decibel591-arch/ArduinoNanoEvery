#include <DS1302.h>
int rlyPIN=6; 
int Pse=40; 
// CREEK switch Agst 01a has to be tested 11/21
//DS1302 rtc(7, 8, 9); 
DS1302 rtc(2, 4, 8); 
Time t; // Init a Time-data structure

void setup() {
  // Open serial communications and wait for port to open:
//   Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.halt(false);
  rtc.writeProtect(false);
  //Serial.print(" Void Starting \n    Seeded   ");
  
  randomSeed(analogRead(0));  // CHECK THAT this is     NOT     commented out
  
  //Serial.println(random(1000));

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rlyPIN, OUTPUT); 
}

void loop() {
  int dfa,dfb,cnSt,dfWt,tme,ifl,prgbss; 
  static int icnt=0;
  float dyr,phs;
  icnt++; 
   //Serial.println("\n\n  START- get_time times are in Minutes 12hrs 720");
   //Serial.print(icnt);
   ///-comment, Get data from the DS1302
  t=rtc.getTime();
  //Serial.print(" TIME  "); //Serial.print(t.hour); //Serial.print(" ");  //Serial.println(t.min); 
     dyr=OrdDt(t); 
     dfa=dyr-(91.4-1); dfb=dyr-(302.60-0); 

    prgbss=30;   //was -30
    if(dfa*dfb<0)prgbss=-30; //was 30  
   tme=t.hour*60+t.min-prgbss;
   
//   tme=random(20,10); ///-comment, for testing 
  //Serial.print(" time wait ");//Serial.println(tme); 
                                                                      //start -typical short interval 
   cnSt=1.0*60+random(0,Pse); dfWt=3+random(0,6); 
   if(tme<cnSt) 
    {
     //Serial.print(cnSt); //Serial.print(" >>after midnight 1  "); 
     dfa=cnSt-tme; //Serial.println(dfa); 
     wait(dfa); 
     ifl=random(1,6); 
     //Serial.print("  "); //Serial.println(ifl); 
     if(ifl>2) 
      {on(); wait(dfWt); off();} 
     tme+=dfa+dfWt;
    }
                                                                      //finish -typical short interval
   cnSt=3.0*60+random(0,3*Pse/2); dfWt=3+random(0,6); 
   if(tme<cnSt)
    {
     //Serial.print(cnSt); //Serial.print(" >>after midnight 2  "); 
     dfa=cnSt-tme; //Serial.println(dfa); 
     wait(dfa); 
     ifl=random(1,6); 
     //Serial.print("  "); //Serial.println(ifl); 
     if(ifl>2) 
      {on(); wait(dfWt); off();} 
     tme+=dfa+dfWt;
    }
   cnSt=12*60;
   dfa=cnSt-tme;  
   wait(dfa); //Serial.println(" ");
   t = rtc.getTime();
   //Serial.print(" TIME  "); //Serial.print(t.hour); //Serial.print(" ");  //Serial.println(t.min); 
     dyr=OrdDt(t); phs=2*3.141592653589793*(dyr-168.2)/375.03; phs=cos(phs); phs=2.127*60*phs;
     dfa=dyr-(91.4-1); dfb=dyr-(302.60-0);  // Serial.println(dfa);  Serial.println(dfb); 

    prgbss=30;   //was -30
    if(dfa*dfb<0)prgbss=-30; //was 30  
   tme=t.hour*60+t.min-prgbss;

//    tme=random(710,750); ///-comment, for testing 
     cnSt=(18.136*60+phs-30)+60;
      if(cnSt<(19.5*60))cnSt=19.5*60; //Creek
      if(prgbss>0)cnSt=cnSt-30; // 60; //added 7/11 changed 23
     cnSt=cnSt+(-Pse/2+random(0,Pse)); 
     dfWt=23*60-cnSt+(-Pse/2+random(0,Pse));  //set time for on and off //Lndng
    //change above, either a "constant"or a set time; two types
     dfa=cnSt-tme; //Serial.println(dfa); 
     dfb=dfa+dfWt;  //Serial.println(dfb); 
    if(dfa>0)
     {
      //Serial.print(cnSt); //Serial.print(" >>Main  "); 
      wait(dfa);
      on(); wait(dfWt); off(); 
      tme+=dfa+dfWt;
     }
    if(dfa<0)
     {
      if(dfb>0)
       {
        dfWt=dfb;
        on(); wait(dfWt); off(); 
        tme+=dfWt;
       }
     }
/*
   cnSt=23*60+random(0,40); dfWt=3+random(0,6); 
   if(tme<cnSt)
    {
     //Serial.print(cnSt); //Serial.print(" >>before midnight  "); 
     dfa=cnSt-tme; //Serial.println(dfa); 
     wait(dfa); 
     ifl=random(1,6); 
     //Serial.print("  "); //Serial.println(ifl); 
     if(ifl>2) 
      {on(); wait(dfWt); off();} 
     tme+=dfa+dfWt;
    }
*/
   dfa=24.2*60-tme; 
   //Serial.println(" AFTER midnite"); 
   wait(dfa);  //waits too 00:12
}

void wait(int dfa) {
  int ia;
  //Serial.print(" wait "); //Serial.print(dfa);
  for(ia=0; ia<dfa; ia++)
   {
    delay(60000); //delay(10); // delay(1000);// delay(60000);
   }
//   //Serial.print(" IA "); //Serial.println(ia); 
}

void on() {
  //Serial.print(" ON");
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rlyPIN, HIGH);   // turn the relay on (HIGH is the voltage level)
}

void off() {
  //Serial.println(" OFF");
//  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rlyPIN, LOW);   // turn the relay on (HIGH is the voltage level)
}


float OrdDt(Time dtTm) {
  float tgn;
  if(dtTm.mon<3){
     tgn=30.6*(dtTm.mon+9)+0.4+dtTm.date-305.8;
    }
   else
    {
     tgn=30.6*(dtTm.mon-3)+0.4+dtTm.date+59; 
    }
  return tgn;
}
