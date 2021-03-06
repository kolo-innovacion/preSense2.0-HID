//KOLO preSense 2.0
//Authors: Eduardo Gante + Alejandro Thacker
// Date: 15/01/2019
//Arduino Nano ATmega328P + MaxBotix MaxSonar EZ1 (MB1010)
// pin D11: PWM input from ultrasonic sensor PW(M) pin output
// pin D8: left LED outputh
// pin D10: right LED output
// pin A0: input from 50KOhm trimPot output
// pin D3: normally high output (to player)
// pin D4: normally low output (to player)


/*
  TEST HERE KEYBOARD INPUT
*/


//IMPORTANT
//this code has been modified for a minimal circuit, consisting of an arduino UNO and the Maxbot sensor only.
//the only connections are three: GND, +5V, and digital pin 2 as pulse input

//constants
const int pwmPin = 2;//11 in other circuit
const int leftLed = 8;//era 2
const int rightLed = 10;//era 4
const int builtinLed = 13;//
const int trimPin = 0;//era 7
const int normHi = 3;// era 10
const int normLo = 4;// era 8

const int leftLim = 10;
const int rightLim = 500;

//vars
long pulse, distance;
int triggerVal = 0;
int delTime = 33;//30 FPS (1000ms/33ms)
int rangeTime = 200;
bool leftOut = false;
bool rightOut = false;
bool inRange = true;

bool curr = false;
bool prev = false;

//WARNING: enabling developer mode will enable serial communication, output values through the USB port and change the FPS to 3
bool developer = false;

void setup() {
  //startSerial();
  setPinModes();
  showAlive();
  //start interIC communication:
  Serial.begin(115200);
}

void loop() {
  //checkRange();
  //rangeIndicator();
  getDistance();
  printVals();
  setOutputs();

  delay(delTime);
}

void setOutputs() {

  if ((distance < triggerVal)) {
    curr = true;
    setActive();

  }
  else
  {
    curr = false;
    setNormal();
  }
  checkStatus();
  statusUpdate();
}

void statusUpdate() {

  prev = curr;
}

void checkStatus() {
  if ((curr == true) && (prev == false)) {
    //when person is present and previous state was missing (person entry)
    Serial.write('a');
  } else if ((curr == false) && (prev == true )) {
    //person exit
    Serial.write('b');
  } else {}
}

void getDistance() {
  //triggerVal = 1024 - analogRead(trimPin);
  //triggerVal = analogRead(trimPin);
  triggerVal = 60;
  pulse = pulseIn(pwmPin, HIGH);
  distance = (pulse * 2.54) / 147;
}

void printVals() {

  if (developer) {
    Serial.println("Trigger value: ");
    Serial.print(triggerVal);
    Serial.println(" ");
    Serial.println("Detected value: ");
    Serial.print(distance);
    Serial.println(" ");
  } else {}
}

void startSerial() {
  if (developer) {
    Serial.begin(9600);
    //delTime = 333;//3 FPS (1000ms/333ms)
  } else {}
}

void setPinModes() {
  pinMode(pwmPin, INPUT);
  pinMode(leftLed , OUTPUT);
  pinMode(rightLed , OUTPUT);
  pinMode(normHi , OUTPUT);
  pinMode(normLo , OUTPUT);
  pinMode(builtinLed , OUTPUT);
  setNormal();

}

void setNormal() {
  digitalWrite(builtinLed, LOW);
  //checkStatus();
}

void setActive() {
  digitalWrite(builtinLed, HIGH);

  //checkStatus();
}

void checkRange() {
  if (triggerVal < leftLim) {
    leftOut = true;
    rightOut = false;
    inRange = false;
  } else if (triggerVal > rightLim) {
    leftOut = false;
    rightOut = true;
    inRange = false;
  } else {
    leftOut = false;
    rightOut = false;
    inRange = true;
  }
}

void rangeIndicator() {
  if (leftOut) {
    digitalWrite(leftLed , HIGH);
    digitalWrite(rightLed , LOW);
    delay(rangeTime);
    digitalWrite(leftLed , LOW);
    digitalWrite(rightLed , LOW);
    delay(rangeTime);
  } else if (rightOut) {
    digitalWrite(leftLed , LOW);
    digitalWrite(rightLed , HIGH);
    delay(rangeTime);
    digitalWrite(leftLed , LOW);
    digitalWrite(rightLed , LOW);
    delay(rangeTime);
  }
}

void showAlive() {
  digitalWrite(leftLed , HIGH);
  delay(rangeTime);
  digitalWrite(rightLed , HIGH);
  delay(rangeTime);
  digitalWrite(builtinLed , HIGH);
  delay(rangeTime);
  digitalWrite(leftLed , LOW);
  digitalWrite(rightLed , LOW);
  digitalWrite(builtinLed , LOW);
}

void blinkLong() {
  digitalWrite(builtinLed, HIGH);
  delay(800);
  digitalWrite(builtinLed, HIGH);
}

void blinkShort() {
  digitalWrite(builtinLed, HIGH);
  delay(800);
  digitalWrite(builtinLed, HIGH);
}
