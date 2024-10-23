const int RXLED = 17;  // The RX LED has a defined Arduino pin
const int switchPin = 16;

int count = 0;
int buttonState = LOW;

void setup(){
    pinMode(RXLED, OUTPUT); 
    pinMode(switchPin, INPUT);  

    Serial.begin(9600); //This pipes to the serial monitor
    Serial.println("Initialize Serial Monitor");
}

void loop(){
    count = count + 1;

    buttonState = digitalRead(switchPin);
    Serial.print("Blink! ");  
    Serial.println(buttonState);

    digitalWrite(RXLED, LOW);   // set the RX LED ON
    delay(200);              // wait for a second

    digitalWrite(RXLED, HIGH);    // set the RX LED OFF
    delay(200);              // wait for a second
}

// Note: The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too – RXLED1,
//  and RXLED0.)