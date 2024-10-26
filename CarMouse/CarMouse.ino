#include "Mouse.h"

const char version[] = "build "  __DATE__ " " __TIME__;
const int RXLED = 17;  // The RX LED has a defined Arduino pin
const int highPin = 9;
const int switchPin = 5;
const int interruptPin = 7;
const int xAxisPin = A0;       // joystick X axis
const int yAxisPin = A2;       // joystick Y axis

int s_delay = 30;
int xAxis = 0;    
int yAxis = 0; 

const int range = 64;             // output range of X or Y movement
const int threshold = range / 4;  // resting threshold
const int center = range / 2;     // resting position value

int printCount = 0;
int printAfterLoops = 1;

int buttonState = LOW;
int buttonLastState = LOW;
int interruptState = LOW; 

// Note: The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too – RXLED1 and RXLED0.)

void setup(){
    pinMode(RXLED, OUTPUT);       // Set RX LED as an output
    pinMode(highPin, OUTPUT);     // Set as HIGH
    digitalWrite(highPin, HIGH);

    pinMode(switchPin, INPUT);     // the switch pin
    pinMode(interruptPin, INPUT);  // Set as HIGH
    
    Serial.begin(9600);             //This pipes to the serial monitor
    Serial.print("CarMouse Version: ");
    Serial.print(version);

    Mouse.begin();
}

void loop(){

    if(interruptState == HIGH){
      Serial.println("Interrupted State");
      s_delay = 150;
    }else{
        interruptState = digitalRead(interruptPin);
        mouseControl();        
    }

    heartBeat();
}

void mouseControl(){
    bool callMouseMove = false;
    
    xAxis = -(readAxis(xAxisPin));
    yAxis = readAxis(yAxisPin);

    if(xAxis != 0){
      callMouseMove = true;
    }else if(yAxis != 0){
      callMouseMove = true;
    }

    mousePress();
    if(callMouseMove){
        Mouse.move(xAxis, yAxis, 0);
      //  printValues();
    }
}

void mousePress(){
  buttonLastState = buttonState;
  buttonState = !digitalRead(switchPin);  

  if(buttonState != buttonLastState){
  //  Serial.print("Mouse Pressed: "); 
    if (buttonState == HIGH) {
   //     Serial.println("Yes");
        Mouse.press(MOUSE_LEFT);
    }else {
   //     Serial.println("No");
        Mouse.release(MOUSE_LEFT);
    }
    // printPressValues();
  }
}

int readAxis(int thisAxis){
    int reading = analogRead(thisAxis);
    // map the reading from the analog input range to the output range:
    reading = map(reading, 0, 1023, 0, range);
    int distance = reading - center;

    if (abs(distance) < threshold) {
      distance = 0;
    }

    // return the distance for this axis:
    return distance;
}

void printMoveValues(){
    printCount++;

    if(printCount == printAfterLoops){
        printCount = 0;
        Serial.print("A0: ");
        Serial.print(xAxis);
        Serial.print("  A1: ");
        Serial.println(yAxis);   
    }
}

void printPressValues(){
        Serial.print("  buttonState: ");
        Serial.print(buttonState);   
        Serial.print("  buttonLastState: ");
        Serial.println(buttonLastState); 
}

void heartBeat(){
    digitalWrite(RXLED, LOW);   
    delay(s_delay);              

    digitalWrite(RXLED, HIGH);    
    delay(s_delay);              
}