//declare our variables and their pin numbers
#define ledPin 2
#define pirPin 8
#define trigPin 13
#define echoPin 12

//default values for our variables
int value = 0;
int pirState = LOW;
int deviceAlarm = 0;

void setup() {
  pinMode (trigPin, OUTPUT); //triger pin will trigger the ultrasonic sound 
  pinMode (echoPin, INPUT); //echo pin produces a pulse when it received a signal
  pinMode(ledPin, OUTPUT); //set the led as OUTPUT because it will produce lights when a signal is detected
  pinMode(pirPin, INPUT); //set the Passive Infrared Sensor as INPUT
  Serial.begin(9600); //start the Serial Monitor at 9600 baud
}

void loop() {
  float duration, cmdistance, mdistance; //declare these variables we need
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  cmdistance = (duration/2)/29.1;
  mdistance = cmdistance/100;
  
  value = digitalRead(pirPin);

  //checks if someone/something is one meter or less near the sensor
  if(mdistance<=1){
    //PIR sensor will check if it is an object or a person
      if (value == HIGH) {
        digitalWrite(ledPin, HIGH);
        
        //if the PIR sensor detects that it is a person
        if (pirState == LOW) {
          Serial.println("person detected");
          Serial.print(mdistance);
          Serial.println(" meters. KEEP ATLEAST 1METER DISTANCE!");
          delay(500);
          deviceAlarm = 1;
          pirState = HIGH;
        }
      }
      //if the PIR sensor detects that it is an object
      else{
        digitalWrite(ledPin, LOW);
        if(pirState == HIGH){
          Serial.println("safe");
          deviceAlarm = 0;
          pirState = LOW;
          }
        }
      }
  //if nothing or no one is near the sensors    
  else{
    Serial.print(mdistance);
    Serial.println(" meters");
    delay(500);
  }
}

void distance(){
  float duration, cmdistance, mdistance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  cmdistance = (duration/2)/29.1;
  mdistance = cmdistance/100;

  if(mdistance<=1){
    Serial.print(mdistance);
    Serial.println(" meters. KEEP ATLEAST 1METER DISTANCE!");
    delay(500);
  }
  else{
    Serial.print(mdistance);
    Serial.println(" meters");
    delay(500);
  }
  
}
