#include <Filters.h>
float filterFrequency = 3.0;  
const int CurrentSensor = A0;
float Voltage = 0;
float Voltagesmoot = 0;

void setup() {
  pinMode(CurrentSensor, INPUT);
  Serial.begin(9600);

}

void loop() {

FilterOnePole lowpassFilter( HIGHPASS, filterFrequency );   

float  RawValue = analogRead(CurrentSensor);
 
 Voltage = (RawValue * 5.0 )/ 1024.0; // scale the ADC  
  Voltagesmoot = lowpassFilter.input(Voltage);
  
Serial.print("RawValue = "); // shows the voltage measured     
  Serial.println(RawValue); 
 //   Serial.print("    "); 
      Serial.print("Voltage = "); // shows the voltage measured  
 Serial.print(Voltage,5); //3 digits after decimal point
  Serial.println(" VDC"); //3 digits after decimal point
  
//Serial.print("RawValuesmoot = "); // shows the voltage measured     
 // Serial.print(RawValuesmoot); 
 //  Serial.print("    ");   
  Serial.print("VoltageSmoot = "); // shows the voltage measured     
  Serial.print(Voltagesmoot,5); //3 digits after decimal point
  Serial.println(" VDC"); //3 digits after decimal point  
     delay(1500);  
 
}
