#include <LiquidCrystal.h>;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int SensorPin=A5;
const int TempSensor=A0;

int FAN=1;
int heater=6;
int water=7;
int button=10;


void setup() {
  // set up LCD's number of columns and rows
  lcd.begin(20,4);

  // Print a massage to the LCD
  lcd.setCursor(0,0);
  lcd.print("----INFORMATION----");
  lcd.setCursor(0,1);
  lcd.print("---Moisture & Temp---");
  lcd.setCursor(0,2);
  lcd.print("Temperature: ");
  lcd.setCursor(0,3);
  lcd.print("Moisture: ");

  pinMode(FAN,OUTPUT);
  pinMode(heater,OUTPUT);
  pinMode(water,OUTPUT);
  pinMode(button,INPUT);
 
}

void loop() {
  int SensorValue = analogRead(SensorPin);
  float SensorVolts = analogRead(SensorPin)*0.0048828125;
  int vout=analogRead(TempSensor);
  vout=(vout*4.88)/10;
  int tempc=vout;
  lcd.setCursor(13,2);
  lcd.print(tempc);
  lcd.setCursor(11,3);
  lcd.print(SensorVolts);
  lcd.print("V");
  
  if(tempc<21)
  {
    digitalWrite(heater,HIGH);
    digitalWrite(FAN,LOW);
   }
   if(tempc>25)
   {
    digitalWrite(heater,LOW);
    digitalWrite(FAN,HIGH);
    }
    if(tempc>=21 && tempc<=25)
    {
     digitalWrite(heater,LOW);
     digitalWrite(FAN,LOW);
      }
    if(SensorVolts<2)
    {
      digitalWrite(water,HIGH);
      }
      else
      {
        digitalWrite(water,LOW);
        }      
  delay(50);
}
