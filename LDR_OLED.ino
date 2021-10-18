#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define photocell A1
#define relay 10
int analogVal = 0 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,0);
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 0);
  display.println(F("IOT IRAN"));
  display.display();      // Show initial text
  delay(2000);
    display.clearDisplay();
}

void loop() {
  analogVal = analogRead(photocell);
  // put your main code here, to run repeatedly: 
  Serial.println("Analog Value = " + String(analogVal));
  display.setCursor(20,0);
  display.println("AVL= ");
  display.setCursor(80,0);
  display.println(analogVal);
  display.display();
  if (analogVal <= 350){
    digitalWrite(relay,1);
    Serial.println("ON");
  }
  else {
    digitalWrite(relay,0);
    Serial.println("OFF");
    
    }
   display.clearDisplay();
   delay(500);
}
