#include <LiquidCrystal.h>
#include <Keypad.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte row_Pins[rows] = {4, 3, 2, 1}; //connect to the row pinouts of the keypad
byte col_Pins[cols] = {7, 6, 5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), row_Pins, col_Pins, rows, cols);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int SensorPin=A5;
const int TempSensor=A0;

int FAN=A1;
int heater=A2;
int water=A3;

long inputInt;
byte value=0;

void setup() {
  // set up LCD's number of columns and rows
  lcd.begin(20,4);
  // Print a massage to the LCD
  lcd.setCursor(0,0);
  lcd.print("----INFORMATION----");
  lcd.setCursor(0,1);
  lcd.print("---Moisture & Temp---");
  lcd.setCursor(0,2);
  lcd.print("Ideal Temp: ");
  lcd.setCursor(0,3);
  lcd.print("Moisture: ");
  
  pinMode(FAN,OUTPUT);
  pinMode(heater,OUTPUT);
  pinMode(water,OUTPUT);

}

void loop() {
  int a;
  char key = keypad.getKey();

if (key != NO_KEY)
   {
    if ( (key >= '0') && (key<= '9') )
      {
       value = value *10;
       value = value + key -'0';
      }
    if ( key == '#' )
     {
      //do stuff with value
      //for demonstration purposes, for now we'll just print it
      lcd.setCursor(12,2);
      lcd.print(value);

      inputInt=static_cast<int>(value);
      value=0;//Now reset ready for next input
     }
   }

  int SensorValue = analogRead(SensorPin);
  float SensorVolts = analogRead(SensorPin)*0.0048828125;
  int vout=analogRead(TempSensor);
  float mv = ( vout/1024.0)*5000;
  float cel = mv/10;
  int tempc=cel;
  
  lcd.setCursor(11,3);
  lcd.print(SensorVolts);
  lcd.print("V");
  
  if(tempc<(inputInt-3))
  {
    digitalWrite(heater,HIGH);
    digitalWrite(FAN,LOW);
   }
   if(tempc>(inputInt+3))
   {
    digitalWrite(heater,LOW);
    digitalWrite(FAN,HIGH);
    }
    if(tempc>=(inputInt-3) && tempc<=(inputInt+3))
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
 // delay(50);
}
