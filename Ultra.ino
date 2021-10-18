#define trig 6
#define echo 7

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2); // make a delay 2us
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);// make a delay 10us
  digitalWrite(trig, LOW);
  

 const unsigned long duration= pulseIn(echo, HIGH);
 int distance= duration/29/2;
 Serial.println(distance);
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } 
  else{
      
      if (distance <= 20){
        Serial.println("Parking is Full");
      }
      else {
        Serial.println("No car is here");
        
        }
  }
  
 delay(500);
 }
