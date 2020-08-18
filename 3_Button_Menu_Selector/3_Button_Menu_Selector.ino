// Uses momentary switches with 2 leds, presence of ground operates them.

int button_add = 7; //  Connect to NO
int red_led_button_add = 6; // Connect to red GND wire
int button_confirm = 5; // Connect to NO
int red_led_button_confirm = 4; // Connect to red GND wire
int button_sub = 3; // Connect to NO
int red_led_button_sub = 2; // Connect to red GND wire
int Counter = 0;

void setup() {
    Serial.begin(9600); // For Console Output
    pinMode(button_add, INPUT);
    pinMode(red_led_button_add, OUTPUT);
    digitalWrite(button_add, HIGH); // Used in place of a pulldown resistor
 
    pinMode(button_confirm, INPUT);
    pinMode(red_led_button_confirm, OUTPUT);
    digitalWrite(button_confirm, HIGH); // Used in place of a pulldown resistor

    pinMode(button_sub, INPUT);
    pinMode(red_led_button_sub, OUTPUT);
    digitalWrite(button_sub, HIGH); // Used in place of a pulldown resistor
}

void loop() {
    digitalWrite(red_led_button_add, HIGH); // Setting red led pin to high so it cant ground
    digitalWrite(red_led_button_sub, HIGH); // Setting red led pin to high so it cant ground
    digitalWrite(red_led_button_confirm, LOW); // Setting red led pin to high so it cant ground


    if (digitalRead(button_confirm) == LOW) {
        digitalWrite(red_led_button_confirm, HIGH); // Setting red led pin to low so it can ground
        Serial.print("Confirmed\n");
        delay(1000);
    }
    else if (digitalRead(button_add) == LOW) { // Reading voltage on pin 10/NO
        Counter += 1;
        digitalWrite(red_led_button_add, LOW); // Setting red led pin to low so it can ground
        Serial.println(Counter);
        delay(200);
    }
    else if (digitalRead(button_sub) == LOW) {
        Counter -= 1;

        digitalWrite(red_led_button_sub, LOW); // Setting red led pin to low so it can ground
        Serial.println(Counter);
        delay(200);
        delay(100);
    }

}
