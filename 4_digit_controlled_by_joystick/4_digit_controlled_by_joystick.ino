//shift registers pins
const int dataPin = 12; //DS
const int latchPin = 11; // STCP
const int clockPin = 10; //SHCP

//joystick pins
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

//values for joystick
int xValue = 0;
int yValue = 0;

//check if the joystick has already moved
bool axisXMoved = false;
bool axisYMoved = false;

//limit for joystick between moved and !moved states
int minThreshold = 250;
int maxThreshold = 750;

//button values
bool dpState = false;
bool swState = LOW;
bool lastSwState = LOW;


//4 digit 7 segment display pins
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int displayCount = 4;

int digitNumber[4] = {0, 0, 0, 0};

int displayDigits[4] = {
  segD1, segD2, segD3, segD4
};

bool state = false;
int currentDisplay = 0;
unsigned long blinkTime = 0;

int digitArray[10] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

unsigned long lastInterrupt = 0;
const int interruptDelay = 200;
const int blinkDelay = 250;

void setup (){
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  //joystick axes
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  //joystick button
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), buttonPressed, CHANGE);

  //4 digit 7 segment display all LOW
  for(int i = 0; i < displayCount; i++){
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  
  Serial.begin(9600);
}

// button pressed with debounce
// ISR function for interrupt
void buttonPressed() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterrupt > interruptDelay) {
    state = !state;
  }
  lastInterrupt = interruptTime;
}

void showDigit(int displayNumber){
  for(int i = 0; i < displayCount; i++){
    digitalWrite(displayDigits[i],HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(int digit){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void writeDigit(int currentDisplay, int state){
  for(int i = 0; i < displayCount; i++){
    int digitToDisplay = 0;
    if(i == currentDisplay){
      // if we choose a display, DP will be on
      // to make the point light up we can increment the bit-value with 1
      // which is dp
      if(state){
        digitToDisplay = digitArray[digitNumber[i]] + 1;
      }
      // if we don't choose a display, DP will blink
      else{
        digitToDisplay = digitArray[digitNumber[i]];
        if(millis() - blinkTime > blinkDelay){
          digitToDisplay = digitArray[digitNumber[i]] + 1;
        }
        if(millis() - blinkTime > blinkDelay * 2){
          blinkTime = millis();
          digitToDisplay = digitArray[digitNumber[i]];
        }    
      }
    }
    // the other displays show the stored value
    else{
      digitToDisplay = digitArray[digitNumber[i]];
    }
    showDigit(i);
    writeReg(digitToDisplay);
    delay(5); 
  }
}

void loop(){
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (!state) {
    // if joystick moved to left in x axis
    // and joystick didn't move previously(we want to change values for one move, not continuous)
    // and we have at least one display left
    if (xValue < minThreshold && currentDisplay < 3 && !axisXMoved) {
      currentDisplay++;
      axisXMoved = true;
    }
    //same for right digit
    if(xValue > maxThreshold && currentDisplay > 0 && !axisXMoved){
      currentDisplay--;
      axisXMoved = true;
    }
    //reset joystick when it is close from point 0
    if(xValue >= minThreshold && xValue <= maxThreshold){
      axisXMoved = false;
    }
  } else {
    // if joystick moved down in y axis
    // and joystick didn't move previously(we want to change values for one move, no continuous)
    // and we have at least one digit up to maxDigit
    if(yValue > maxThreshold && !axisYMoved && digitNumber[currentDisplay] > 0){
      digitNumber[currentDisplay]--;
      axisYMoved = true;
    }
    
    //same for up direction
    if(yValue < minThreshold && !axisYMoved && digitNumber[currentDisplay] < 9){
      digitNumber[currentDisplay]++;
      axisYMoved = true;
    }
    
    //reset joystick when it is close from point 0
    if(yValue >= minThreshold && yValue <= maxThreshold ){
      axisYMoved = false;
    }
  }
  writeDigit(currentDisplay, state);
}
