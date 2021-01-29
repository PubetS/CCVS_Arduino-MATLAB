#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // SDA >> A4, SCL >> A5

int IanalogIn = A0;
int VanalogIn = A1;
int out = A2;

int SW_up = 3;
int SW_down = 4;
int SW_start = 5;
int Buzzer = 10;

int Xmax = 10;
int Xmin = 0;
int X_value = 0;
int increase = 1;
int X_up = 1; //check SW up LOW
int X_down = 1; //check SW down LOW
int Start = 1; //check SW start LOW
int Stop = 1; //check SW stop LOW
int pluse =  0; // initial start PWM 

//double mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
//double ACSoffset = (512/1024.0)*5000;
int IRawValue= 0;
int VRawValue= 0; 
double Isensor = 0;
double Vsensor = 0;
double filV = 0;
double filI = 0;
double Amps = 0;
double V_out = 0;


void Up()
{
  X_up = digitalRead(SW_up);
  if (X_up == 0)
 {
 X_value = X_value + increase;
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
 X_value = X_value - increase;
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
  pinMode(IanalogIn, INPUT);
  pinMode(VanalogIn, INPUT);
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
  
 lcd.clear();
  lcd.setCursor(0,0);
 lcd.print("  X value = ");
 lcd.print("     ");
 lcd.setCursor(12,0);
 lcd.print(X_value);
 lcd.setCursor(0,1);
 lcd.print("  Vo = X*Ic  ");


 Up();
 Down();
 delay(100); 
 //Start = 1;
 //Stop = 0;
}

 while(1)
 {
  
 IRawValue = analogRead(IanalogIn);
 Isensor = (IRawValue/1024.0)*5000; // Gets you mV


 VRawValue = analogRead(VanalogIn);
 Vsensor = (VRawValue/1024.0)*5000; // Gets you mV

 
 // digital filter 0.5Hz with sambling frequency 0.01
 for (int i=1;i<100;i++)
 {
 Isensor = (IRawValue/1024.0)*5000;
 filI=0.9691*filI+0.03093*Isensor;
 }

 //converst Voltage to Current with cure fitting
 
 Amps = filI;

 // calculated output voltage from eq Voc = Ic*X
 V_out = Amps*X_value; 

// compairing output voltage and calculated voltage
if(Vsensor > V_out+10)
{
  pluse = pluse +1; 
  if (pluse >=255) pluse=255;
}
 
 if(Vsensor < V_out-10)
{
  pluse = pluse -1; 
  if (pluse >=255) pluse=255;
}

if(Vsensor<=V_out+10|Vsensor>=V_out-10)
{
  pluse=pluse;
}
analogWrite(out, pluse);
 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Is = ");
  lcd.print(Isensor,3);
  lcd.print("Vo = ");
  lcd.print(V_out,3);
  lcd.setCursor(0,1);
 lcd.print("Amps = ");
  lcd.print(Amps,3);
  Check_Stop();
 Serial.print("Raw Value = " ); // shows pre-scaled value  
 Serial.print(IRawValue); 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Vsensor,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 delay(1000); 
 
}
}
