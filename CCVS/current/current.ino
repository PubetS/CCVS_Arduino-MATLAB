#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // SDA >> A4, SCL >> A5
/*
Measuring Current Using ACS712
*/
const int analogIn = A1;
double mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
double ACSoffset = (512/1023.0)*5000; 
double Voltage = 0;
double Amps = 0;
double V=0;

void setup(){ 
 Serial.begin(9600);
 lcd.begin();
}

void loop(){
 
 RawValue = analogRead(analogIn);
 Voltage = (RawValue/1023.0)*5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);

 lcd.clear();
 lcd.setCursor(0,0);
 //lcd.print("Raw=");
  //lcd.print(RawValue);
  lcd.print("Vin = ");
  lcd.print(Voltage/1000,5);
  lcd.setCursor(0,1);
 lcd.print("Amps = ");
  lcd.print(Amps,5);
 Serial.print("Raw Value = " ); // shows pre-scaled value 
 Serial.print(RawValue); 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,5); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t ACSoffset = "); 
 Serial.println(ACSoffset,5);
 Serial.print("\t mVperAmp = "); 
 Serial.println(mVperAmp,5);
 
 
 delay(2500); 
 
}
