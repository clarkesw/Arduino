const int RXLED = 17;  // The RX LED has a defined Arduino pin
int count = 0;

void setup(){
    pinMode(RXLED, OUTPUT);  // Set RX LED as an output
    // TX LED is set as an output behind the scenes 

    Serial.begin(9600); //This pipes to the serial monitor
    Serial.println("Initialize Serial Monitor");
}

void loop(){
    count = count + 1;
    Serial.print("Blinker ");  
    Serial.println(count);

    digitalWrite(RXLED, LOW);   // set the RX LED ON
    delay(1000);              // wait for a second

    digitalWrite(RXLED, HIGH);    // set the RX LED OFF
    delay(1000);              // wait for a second
}

// Note: The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too – RXLED1,
//  and RXLED0.)