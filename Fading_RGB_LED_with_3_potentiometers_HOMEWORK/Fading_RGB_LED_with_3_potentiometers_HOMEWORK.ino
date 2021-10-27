//initialized input pins
const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

//initialized output pins
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

//initialized input values
int potRedValue = 0;
int potGreenValue = 0;
int potBlueValue = 0;

//initialized output values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

//initialized min and max values for potentiometers and leds
const int minPotentiometerValue = 0;
const int maxPotentiometerValue = 1023;
const int minLedValue = 0;
const int maxLedValue = 255;

void setup() {
  //pin mode for each initialized pin (INPUT / OUTPUT)
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //read values from potentiometers, interval [0, 1023]
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  //mapping potentiometers values to leds values, interval [0, 255]
  redValue = map(potRedValue, minPotentiometerValue, maxPotentiometerValue, minLedValue, maxLedValue);
  greenValue = map(potGreenValue, minPotentiometerValue, maxPotentiometerValue, minLedValue, maxLedValue);
  blueValue = map(potBlueValue, minPotentiometerValue, maxPotentiometerValue, minLedValue, maxLedValue);

  Serial.println(potRedValue);
  Serial.println(potGreenValue);
  Serial.println(potBlueValue);

  //send analog data to the digital pins with ~ (3, 5, 6, 9, 10 or 11)
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
