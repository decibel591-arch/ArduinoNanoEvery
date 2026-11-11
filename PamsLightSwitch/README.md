# Pams Light Switch
Repository for Pams Light switch

[Download Fritzing file](PamsLightSwitch.fzz)<img width="1250" height="940" alt="WireLayout" src="https://github.com/user-attachments/assets/67387749-d84d-4516-a04c-6cee6c3ab8bf" />
Wring Layout- Reference
<img width="1250" height="940" alt="PcbLayout" src="https://github.com/user-attachments/assets/b943bcba-f3be-4918-9187-348f06814a6e" />
PCB board- showing problems
<img width="1250" height="940" alt="CircuitDiagram" src="https://github.com/user-attachments/assets/8056053b-3c63-4265-9fcd-033fea28fb90" />
Circuit Diagram- showing problem

In trying to get rid of the problem in the Circuit Diagram deleting the connection removes the yellow wire in Wiring Layout? (it is my/the Reference).  Suspect this is a problem in EveryMan part. 


The Arduino .ino files are in a zip file. 

[Download zip.file](Pammys.zip)

RlyBlnk.ino- Simply test of Arduino and relay module.  

RTCds1302.ino- Shows time and sets by uncommenting commands between /* .... */.  


PamsLightSwitch.ino- Main routine. 


## Description of Main routine 

  Relay ON given by time for SunDown and OFF by "time for Bed".  During  the night (till 06:00) a random switch is used for toilet visit(s) (cirka 8 mins).  Sundown is given by a two Cosine fit to Light_Up times (Street Lights) plus Tophat (Summer/winter) for the Pompey (UK) area.  The 24 hour loop reads the clock twice (jede 12 hour) to synchronize. In between it uses wait function to determine action. 
  
  Strategy was to minimise switching and current usage.  The setting of the time was kept separate from the Main routine as it was "cleaner". Main refrains from Output to Serial monitor- there were problems so the printing was taken out as possible cause. 
  
  So usage Load RTCds1302.ino and read time.  Correct time if needed (Load a corrected RTCds1302.ino). Load PamsLightSwitch.ino and leave until next time.  
  
  There is a(re) bug(s) somewhere.  Couldnt find them. An exercise for the reader.  
  
  Correction for Winter and Summer time (last Sundays in March and October) tried.  
  Saw that it (had worked) was working between visits/travels. 


