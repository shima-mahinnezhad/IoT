#define trig 6
#define echo 7
#define buzzer 8
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define MQ135 A0
#define relay 10
int sensorValue;
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2); // make a delay 2us
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);// make a delay 10us
  digitalWrite(trig, LOW);
  

 const unsigned long duration= pulseIn(echo, HIGH);
 int distance= duration/29/2;
  display.setCursor(20,0);
  display.println("DIS= ");
  display.setCursor(80,0);
  display.println(distance);
 
  if (distance <= 50 && distance >= 0) {
   digitalWrite(buzzer, HIGH);
} else {
   digitalWrite(buzzer, LOW);
}
   delay(60);
    

  // -----------------------------MQ135------------------------------------------
sensorValue = analogRead(MQ135); // read analog input pin 0
  display.setCursor(20,17);
  display.println("GAS= ");
  display.setCursor(80,17);
  display.println(sensorValue); 
if(sensorValue>70)
{
digitalWrite(relay, HIGH);
}
else
digitalWrite(relay, LOW);
Serial.println(sensorValue, DEC); // prints the value read
  display.display();
  delay(500);
  display.clearDisplay();

 

 }
