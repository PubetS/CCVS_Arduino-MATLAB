#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // SDA >> A4, SCL >> A5

int IanalogIn = A0;
int VanalogIn = A1;
int out = 9;

int IRawValue = 0;
int VRawValue = 0;

int SW_up = 3;
int SW_down = 4;
int SW_start = 5;
int Buzzer = 10;

int Xmax = 10;
int Xmin = 0;
int X_value = 0;
int increase = 1;
int X_up = 1;
int X_down = 1;
int Start = 1;
int Stop = 1;

double Isensor = 0;
double Vsensor = 0;
double filI = 0;
double filV = 0;
double mAmps = 0;
double V_out_cal = 0;
double V_real = 0;
double mV_out_cal = 0;
double mV_real = 0;
int pluse =  0;
int pluseinitial = 0; // initial start PWM
double linear;

void Up()
{
  X_up = digitalRead(SW_up);
  if (X_up == 0)
  {
    X_value = X_value + 1;
    if (X_value >= 10)
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
    if (X_value <= 0)
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

void setup() {
  pinMode(IanalogIn, INPUT);
  pinMode(VanalogIn, INPUT);
  pinMode(SW_up, INPUT);
  pinMode(SW_down, INPUT);
  pinMode(SW_start, INPUT);

  pinMode(Buzzer, OUTPUT);
  pinMode(out, OUTPUT);


  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Controlled");
  lcd.setCursor(0, 1);
  lcd.print(" Voltage Source");
  delay(2000);

}

void loop()
{

  while (digitalRead(SW_start) == HIGH)
  {

    lcd.setCursor(0, 0);
    lcd.print("  X value = ");
    lcd.print("     ");
    lcd.setCursor(12, 0);
    lcd.print(X_value);
    lcd.setCursor(0, 1);
    lcd.print("  Vout = X*Iin  ");


    Up();
    Down();
    delay(100);
    //Start = 1;
    //Stop = 0;
  }
  lcd.clear();
  while (1)
  {

    IRawValue = analogRead(IanalogIn);
    Isensor = (IRawValue / 1024.0) * 5000; // Gets you mV from mA
    VRawValue = analogRead(VanalogIn);
    Vsensor = (VRawValue / 1024.0) * 5000; // Gets you mV

    for (int i = 1; i < 100; i++)
    {
      IRawValue = analogRead(IanalogIn);
      Isensor = (IRawValue / 1024.0) * 5000;
      filI = 0.9691 * filI + 0.03093 * Isensor;

      VRawValue = analogRead(VanalogIn);
      Vsensor = (VRawValue / 1024.0) * 5000; // Gets you mV
      filV = 0.9691 * filV + 0.03093 * Vsensor;
    }

    mAmps = filI;
    mV_out_cal = mAmps * X_value;

    Vsensor = filV;
    // eq1 mV_real = Vsensor * 3;
    mV_real = (Vsensor * 12.31) / 4.1;

    V_real = mV_real / 1000;
    V_out_cal = mV_out_cal / 1000;

    double p11 =       6.617;
    double p12 =       6.527;

    double V_out = (double)V_out_cal;

        linear =  p11*V_out + p12;
        
    pluse = map( linear, 0, 100, 0, 255);

    analogWrite(out, pluse);
    
    
    if (mV_real > mV_out_cal + 5)
    {
      pluse = pluse - 1;
      if (pluse <= 0) pluse = 0;
    }

    if (mV_real < mV_out_cal - 5)
    {
      pluse = pluse + 1;
      if (pluse >= 255) pluse = 255;
    }

    if (mV_real <= mV_out_cal + 5 | mV_real >= mV_out_cal - 5)
    {
      pluse = pluse;
    }
    //}




    lcd.setCursor(0, 0);
    lcd.print("Ic=");
    lcd.print(mAmps, 2);
    lcd.setCursor(10, 0);
    lcd.print(" X=");
    lcd.print(X_value);

    lcd.setCursor(0, 1);
    lcd.print("Vc=");
    lcd.print(V_out_cal);
    lcd.setCursor(8, 1);
    lcd.print(" Vo=");
    lcd.print(V_real);
    Serial.print("\t mV from Isensor = "); // shows the voltage measured
    Serial.print(Isensor, 3); // the '3' after voltage allows you to display 3 digits after decimal point
    Serial.print("\t mAmps filter and convest = "); // shows the voltage measured
    Serial.println(mAmps, 3); // the '3' after voltage allows you to display 3 digits after decimal point
    Serial.print("\t mV from Vsensor = ");
    Serial.print(Vsensor, 3);
    Serial.print("\t mV real = ");
    Serial.print(V_real, 3);
    Serial.print("\t pluse = "); //
    Serial.println(pluse);
    Serial.print("\t pluse init = "); //
    Serial.println(pluseinitial);
    Serial.print("\t V_out cal = "); //
    Serial.println(V_out_cal, 3);

  }
}
