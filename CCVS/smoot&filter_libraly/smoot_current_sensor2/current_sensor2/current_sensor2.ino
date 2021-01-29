#include <AnalogSmooth.h>

const int CurrentSensor = A0;

//int RawValue= 0;
float Current = 0;
float Voltage = 0;
float Voltagesmoot10 = 0;
float Voltagesmoot100 = 0;
float RawValue = 0;
float SmootRawValue10 = 0;
float SmootRawValue100 = 0;
// Defaults to window size 10
AnalogSmooth as = AnalogSmooth();
// Window size can range from 1 - 100
AnalogSmooth as100 = AnalogSmooth(100);

void setup(){  
  pinMode(CurrentSensor, INPUT);
  Serial.begin(9600);
}

void loop(){ 
   
  RawValue = analogRead(CurrentSensor); //No smooting

for (int i=0;i<100;i++){
  
  SmootRawValue10 = as.analogReadSmooth(CurrentSensor); // Smoothing with window size 10

  SmootRawValue100 = as100.analogReadSmooth(CurrentSensor);  // Smoothing with window size 100
 
  Voltage = (RawValue * 5.0 )/ 1024.0; // scale the ADC  
  Voltagesmoot10 = (SmootRawValue10 * 5.0 )/ 1024.0; // scale the ADC  
  Voltagesmoot100 = (SmootRawValue100 * 5.0 )/ 1024.0; // scale the ADC
  delay(20); 
}
  
   Serial.print("RawValue = "); // shows the voltage measured     
  Serial.print(RawValue); 
    Serial.print("    "); 
   Serial.print("Voltage = "); // shows the voltage measured  
 Serial.print(Voltage,5); //3 digits after decimal point
  Serial.println(" VDC"); //3 digits after decimal point 
  
   Serial.print("SmootRawValue10 = "); // shows the voltage measured     
  Serial.print(SmootRawValue10); //3 digits after decimal point   
  Serial.print("    ");   
  Serial.print("VoltageSmoot = "); // shows the voltage measured     
  Serial.print(Voltagesmoot10,5); //3 digits after decimal point
  Serial.println(" VDC"); //3 digits after decimal point  

  Serial.print("SmootRawValue100 = "); // shows the voltage measured     
  Serial.print(SmootRawValue100); //3 digits after decimal point   
  Serial.print("    ");   
  Serial.print("VoltageSmoot100 = "); // shows the voltage measured     
  Serial.print(Voltagesmoot100,5); //3 digits after decimal point
  Serial.println(" VDC"); //3 digits after decimal point 
  delay(1500);  
}
