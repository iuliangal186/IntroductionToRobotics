const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int antennaPin = A0;
const int buzzerPin = 12;
const int buzzerTone = 50;
const int buzzerDuration = 700;

int antennaVal = 0; 
const int antennaValMax = 300; 
const int antennaValMin = 1;
const int maxDigit = 9;
const int minDigit = 0;

const int refreshDuration = 100; 

int index = 0;

const int samples = 15;
int readings[samples];  
int total = 0;                                                     
int number = -1;

const int segSize = 8;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

const int noOfDigits = 10;
//matrix
bool digitMatrix [noOfDigits][segSize-1]={
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber (byte digit, bool decimalPoint){
  for (int i = 0; i < segSize - 1; i++){
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(pinDP, decimalPoint);
}

void setup() {
  for (int i = 0; i< segSize ; i++){
    pinMode(segments[i], OUTPUT);
  }

  for (int i = 0; i < samples; i++)
    readings[i] = 0;                      
    
  Serial.begin(9600);
}

int averageValue(){
    //constrain antenna Value in 1 - 300 range
    antennaVal = constrain(antennaVal, antennaValMin, antennaValMax);
    // mapped antenna value in 1 - 1023 range  
    antennaVal = map(antennaVal, antennaValMin, antennaValMax, 1, 1023);  

    
    total -= readings[index];               
    readings[index] = antennaVal; 
    total += readings[index];               
    index += 1;                    

    if (index >= samples) {
      index = 0;
    }
    // make an average for every new data
    return total / samples;
}

void loop() {
  antennaVal = analogRead(antennaPin);  
  
  if(antennaVal >= 1){
    
    int average = averageValue();

    // mapped average value in 1 to 9 digit
    number = map(average, 1, 1023, minDigit, maxDigit);

    Serial.println(average);
    
    displayNumber(number, HIGH);
    // if EMF dosen't exist -> noTone
    if (number == 0) {
      noTone(buzzerPin);
    }
    else {
      // if EMF exist amplify tone depending on number
      tone(buzzerPin, number * buzzerTone, buzzerDuration);
    }   
     
    delay(refreshDuration);
    
    noTone(buzzerPin);
    displayNumber(number, LOW);
  }
}
