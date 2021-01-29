#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // SDA >> A4, SCL >> A5

const int analogIn = A0;
int SW_up = 3;
int SW_down = 4;
int SW_start = 5;
int Buzzer = 10;
int V_in = A1;
int V_out = A2;
int Xmax = 10;
int Xmin = 0;
int X_value = 0;
int increase = 1;
int X_up = 1;
int X_down = 1;
int Start = 1;
int Stop = 1;

int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = (141*5000)/1023; 
double Voltage = 0;
double Amps = 0;



void Up()
{
  X_up = digitalRead(SW_up);
  if (X_up == 0)
 {
 X_value = X_value + 1;
     if (X_value>=10)
      X_value = 10;
 delay(50);
 
 }
}

void Down ()
{
  X_down = digitalRead(SW_down);
   if (X_down == 0)
 {
 X_value = X_value - 1;
      if (X_value<=0)
      X_value = 0;
 delay(50);
 }
}

void Check_Stop()
{
 Start = digitalRead(SW_start);
 if (Start == 0)
 Stop = 1;
 delay(30);
}

void setup(){ 
  pinMode(SW_up, INPUT);
  pinMode(SW_down, INPUT);
  pinMode(SW_start, INPUT);
  pinMode(V_in, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(V_out, OUTPUT);

 
 Serial.begin(9600);
 lcd.begin();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Current Controlled");
 lcd.setCursor(0,1);
 lcd.print("Voltage Source");
 delay(2000);
  
}

void loop()
{

 while (digitalRead(SW_start) == HIGH)
{

  lcd.setCursor(0,0);
 lcd.print("  X value = ");
 lcd.print("     ");
 lcd.setCursor(12,0);
 lcd.print(X_value);
 lcd.setCursor(0,1);
 lcd.print("  Vout = X*Iin  ");


 Up();
 Down();
 delay(100); 
 //Start = 1;
 //Stop = 0;
}

 while(1)
 {
  
 RawValue = analogRead(analogIn);
 Voltage = (RawValue*5000)/1023.0; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 lcd.setCursor(0,0);
 lcd.print("Raw=");
  lcd.print(RawValue);
  lcd.print(" mV=");
  lcd.print(Voltage,3);
  lcd.setCursor(0,1);
 lcd.print("Amps = ");
  lcd.print(Amps,3);
  Check_Stop();
 Serial.print("Raw Value = " ); // shows pre-scaled value  
 Serial.print(RawValue); 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 delay(1000); 
 
}
}
