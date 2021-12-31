
const int motorLeft = 6;
const int motorRight = 5;

const int trigPin = 8;
const int echoPin = 9;

const int red = 11;

int rightTurn = true;

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

float duration, distance;

void setup() {
  Serial.begin(9600);
  
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);

  //Set up the distance sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(red, OUTPUT);
  
  Serial.println("proceeding to drive straight");
  
}

void loop() {

//Compute distance of objects
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration*.0343)/2;

  if (distance < 30) { // obstacle detected, 15 was good
    digitalWrite(red, HIGH);
    halt();
    delay(1000);
    turn();
    halt();
    delay(1000);
    Serial.println("proceeding to drive straight");
  } else { // obstacle not detected
    digitalWrite(red, LOW);
    forward();
  }
  
}

void forward() {  
  analogWrite(motorRight, 255);
  analogWrite(motorLeft, 255);
}

void halt() {
  analogWrite(motorRight, 0);
  analogWrite(motorLeft, 0);
  Serial.println("Stopped movement");
}

void turn() {
  int goMotor = (rightTurn) ? 5 : 6;
  int stopMotor = (rightTurn) ? 6 : 5;

  rightTurn = !rightTurn;
  
  analogWrite(goMotor, 255);
  analogWrite(stopMotor, 0);
  
  int turnTime = 1500 + rand() % 2000;
  
  Serial.print("turning for ");
  Serial.print(turnTime);
  Serial.println(" milliseconds");
  
  delay(turnTime);
}
