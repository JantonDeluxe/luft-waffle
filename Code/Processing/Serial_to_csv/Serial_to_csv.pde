import processing.serial.*;
Serial myPort;

Table table;

int numReadings = 500; //keeps track of how many readings you'd like to take before writing the file. 
int readingCounter = 0; //counts each reading to compare to numReadings. 
String val;
 
String fileName;
void setup()
{
  table = new Table();
  
  String portName = Serial.list()[0]; 
  
  myPort = new Serial(this, portName, 115200); 
  
  //the following are dummy columns for each data value. Add as many columns as you have data values. Customize the names as needed. Make sure they are in the same order as the order that Arduino is sending them!
  table.addColumn("Zeit in s");
  table.addColumn("H\u00f6he in m");
  table.addColumn("Geschwindigkeit in m/s");
  table.addColumn("Beschleunigung in m/s\u00B2");
 
}
 
void serialEvent(Serial myPort){
  val = myPort.readStringUntil('\n');
  
  if (val!= null) { 
    
    println(val); //Optional, useful for debugging. If you see this, you know data is being sent. Delete if  you like. 
    float sensorVals[] = float(split(val, ',')); //parses the packet from Arduino and places the valeus into the sensorVals array. I am assuming floats. Change the data type to match the datatype coming from Arduino. 
    val = trim(val); //gets rid of any whitespace or Unicode nonbreakable space
    TableRow newRow = table.addRow(); //add a row for this new reading
    newRow.setInt("id", table.lastRowIndex());//record a unique identifier (the row's index)
    
    //record sensor information. Customize the names so they match your sensor column names. 
    newRow.setFloat("Zeit", sensorVals[0]);
    newRow.setFloat("Höhe", sensorVals[1]);
    newRow.setFloat("Geschwindigkeit", sensorVals[2]);
    newRow.setFloat("Beschleunigung", sensorVals[3]);
    
    saveTable(table, "data/new.csv");
    
   }
}
 
void draw()
{ 
   //visualize your sensor data in real time here! In the future we hope to add some cool and useful graphic displays that can be tuned to different ranges of values. 
}
