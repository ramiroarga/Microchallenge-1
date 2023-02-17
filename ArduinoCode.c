// PUMP: Give a name to digital pin 2, which has a pushbutton attached
int pushButton = 2;

// PUMP: The transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;

// PH METER SETUP
#define SensorPin A0  //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00   //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth 40     //times of collection
int pHArray[ArrayLenth];  //Store the average value of the sensor feedback
int pHArrayIndex = 0;
const int ledPin = 13;      // pin that the LED is attached to
#define RGB_GREEN 3
#define RGB_BLUE 5
#define RGB_RED 6


void setup() {

  Serial.begin(9600);
  delay(1000);
  //PH Sensor Leds
  pinMode (RGB_RED, OUTPUT);
  pinMode (RGB_GREEN, OUTPUT);
  pinMode (RGB_BLUE, OUTPUT);

  digitalWrite(RGB_RED, LOW);
  digitalWrite(RGB_BLUE, LOW);
  digitalWrite(RGB_GREEN, LOW);

  // PUMP make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  // PUMP make the transistor's pin an output:
  pinMode(motorControl, OUTPUT); 
  //Serial communication starts
  Serial.println("Ardi: I'm napping here, hit me if you need me!");
  delay(1000);
}
void loop() {

  if (digitalRead(pushButton) == LOW){
    Serial.println("Ardi: Zzzzz"); 
    //analogRead(SensorPin);
    //float voltage2= SensorPin * (5.0 / 1023.0);
    //Serial.println(voltage2);
    returnPh(); // Start to return the Ph value
    delay(1000);
  }
  else {
    Serial.println("Button");
    //Serial.println("Arduino: Ups, someone pressed the button. I'm starting the pump!!! Beware the water, it can splash!");
    delay(1000);
    // ramp up the motor speed    
    for(int x = 0; x <= 255; x++){
      analogWrite(motorControl, x);
      delay(50);
    }
    // ramp down the motor speed
    for(int x = 255; x >= 0; x--){
      analogWrite(motorControl, x);
      delay(50);
    } 
    Serial.println("Ardi: Done running the pump. Hope it was enough water to freshen your spirits!");
    Serial.println("Pumped");
    //delay(1000);

    Serial.println("Let's now see what the quality is like");
    //delay(1000);

    // Function to Read PH
    Serial.println("Measuring Ph and other sensors");
    Serial.println(returnPh());
    delay(1000);
    Serial.println("I guess the quality is all right");
  }

}

// Function to collect a number of pH readings and then return the pH value by averaging the collected values.
float returnPh() {
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;
  
  if (millis() - samplingTime > samplingInterval) {
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLenth) pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
  }

  if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    //Serial.print("Voltage:");
    //Serial.print(voltage, 2);
    Serial.print(" pH value: ");
    Serial.println(pHValue, 2);
    //digitalWrite(LED, digitalRead(LED) ^ 1);
    // if the analog value is high enough, turn on the LED:
    
    if (pHValue <= 6.00) {
      digitalWrite(RGB_RED, HIGH);
      digitalWrite(RGB_BLUE, LOW);
      digitalWrite(RGB_GREEN, LOW);
    } else if (pHValue >= 7.50 ){
      digitalWrite(RGB_BLUE, LOW);
      digitalWrite(RGB_RED, LOW);
      digitalWrite(RGB_GREEN, HIGH);
    }
    
    else {
      digitalWrite(RGB_BLUE, HIGH);
      digitalWrite(RGB_RED, LOW);
      digitalWrite(RGB_GREEN, LOW);
    }

  //Serial.println(pHValue);
  return pHValue;
  }
}

// Function to average sensor readings
double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) {  //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0];
      max = arr[1];
    } else {
      min = arr[1];
      max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;  //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i];  //min<=arr<=max
        }
      }  //if
    }    //for
    avg = (double)amount / (number - 2);
  }  //if
  return avg;
}
