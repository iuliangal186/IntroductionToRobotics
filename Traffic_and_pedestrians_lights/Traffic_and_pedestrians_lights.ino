//initialized pins input / output
const int carsRedPin = 11;
const int carsYellowPin = 12;
const int carsGreenPin = 13;
const int pedestrianRedPin = 7;
const int pedestrianGreenPin = 6;
const int buttonPin = 2;
const int buzzerPin = 8;

//initialized state for pins
bool carsRedState = LOW;
bool carsYellowState = LOW;
bool carsGreenState = HIGH;
bool pedestrianRedState = HIGH;
bool pedestrianGreenState = LOW;
bool buttonState = HIGH;

//timer for entire process (state 1 + 2 + 3 + 4)
unsigned long timer = 0;

//different duration for each state
unsigned int waitState2 = 10000;
unsigned int state2Timer = 3000;
unsigned int state3Timer = 10000;
unsigned int state4Timer = 5000;

//buzzer settings
int buzzerTone = 1000;
int toneTimer = 250;

//pause buzz time for the first part of pedestrian green
int pauseSlowTones = 1000;

//pause buzz + blink for the second part of pedestrian green
int pauseFastTones = 500;

//specific moment when buzzer buzzes last time
unsigned long lastTone = 0;

void setup() {
  pinMode(carsRedPin, OUTPUT);
  pinMode(carsYellowPin, OUTPUT);
  pinMode(carsGreenPin, OUTPUT);
  pinMode(pedestrianRedPin, OUTPUT);
  pinMode(pedestrianGreenPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
//  digitalWrite(carsRedPin, carsRedState);
//  digitalWrite(carsYellowPin, carsYellowState);
//  digitalWrite(carsGreenPin, carsGreenState);
//  digitalWrite(pedestrianRedPin, pedestrianRedState);
//  digitalWrite(pedestrianGreenPin, pedestrianGreenState);

}


void loop() {
  buttonState = digitalRead(buttonPin);

  //start timer when button changes state, is red for cars end timer is 0
  if (buttonState == LOW && carsGreenState == HIGH && timer == 0) {
    timer = millis();
  }

  //wait for state 2 and when waiting is ending yellow light will be ON
  if ((millis() - timer) > waitState2 && timer && carsGreenState == HIGH) {
    carsGreenState = LOW;
    carsYellowState = HIGH;
    timer = millis();
  }

  //after timer for yellow expires, red for cars will be ON, green for pedestrian will be ON
  //and yellow for cars will be OFF
  if ((millis() - timer) > state2Timer && carsYellowState == HIGH) {
    carsYellowState = LOW;
    carsRedState = HIGH;
    pedestrianRedState = LOW;
    pedestrianGreenState = HIGH;
    timer = millis();
  }

  //in the first part of green for pedestrian buzzer buzzes slow and green light don't blinking
  if ((millis() - timer) < state3Timer && pedestrianGreenState == HIGH) {
    if ((millis() - lastTone) > pauseSlowTones) {
      tone(buzzerPin, buzzerTone, toneTimer);
      lastTone = millis();
      Serial.println(lastTone);
    }
  }

  //in the final part of green for pedestrian buzzer buzzes fast
  if ((millis() - timer) > state3Timer && (millis() - timer) < (state3Timer + state4Timer) && carsRedState == HIGH) {
    if ((millis() - lastTone) > pauseFastTones) {
      tone(buzzerPin, buzzerTone, toneTimer);
      pedestrianGreenState = HIGH;
      lastTone = millis();
      Serial.println(lastTone);
    }
  //green light blinks in the same time with buzzer sound
    if ((millis() - lastTone) > toneTimer) {
      pedestrianGreenState = LOW;
    }
  }

  //when time for pedestrian crossing is over, green for cars turns ON, red for pedestrian turns ON
  //other lights turn OFF
  if ((millis() - timer) > (state3Timer + state4Timer) && carsRedState == HIGH) {
    pedestrianGreenState = LOW;
    pedestrianRedState = HIGH;
    carsRedState = LOW;
    carsGreenState = HIGH;
    //reset timer and lastTone for the next time
    timer = 0;
    lastTone = 0;
    noTone(buzzerPin);
  }

  //at each loop we display the status of the LEDs specific to that moment
  digitalWrite(carsRedPin, carsRedState);
  digitalWrite(carsYellowPin, carsYellowState);
  digitalWrite(carsGreenPin, carsGreenState);
  digitalWrite(pedestrianRedPin, pedestrianRedState);
  digitalWrite(pedestrianGreenPin, pedestrianGreenState);
}
