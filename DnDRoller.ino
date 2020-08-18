#include <ArduinoSort.h>
#include <PrintStream.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Varaiables for 3 button menu
int button_add = 7; //  Connect to NO
int red_led_button_add = 6; // Connect to red GND wire
int button_confirm = 5; // Connect to NO
int red_led_button_confirm = 4; // Connect to red GND wire
int button_sub = 3; // Connect to NO
int red_led_button_sub = 2; // Connect to red GND wire

// Variables for main program
int dice_number, dice_sides, low_sub;
// This program will calculate character stats for dungeons and dragons
// Translated from Python into C/C++ by Chandler Dionne
// ** Original Python Code By Matt Schwenger **


//Notes for later
// 1. All serial outputs will have to be changed to lcd outputs in final version
// 2. can use green led on new buttons for yes, and red for no. Like wise green for increase, red for decrease for values.

// Struct to create a class to hold stats for each run of the loop
struct stats{
  int Str, Con, Dex, Int, Wis, Chr;
};

// Splash screen to run at first boot of board
void first_boot(){
  //Serial << "** Original Python code written by Matthew Schwenger **\n";
  delay(2000);
  //Serial << "** Translated from Python into C/C++ by Chandler Dionne **\n";
  delay(2000);
  //Serial << "** To Matt, with love. <3 **\n";
  delay(2000);
}

void menu_setup(){
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

// Fucntion to use the three buttons to get an int
int get_number(){
  digitalWrite(red_led_button_add, HIGH); // Setting red led pin to high so it cant ground
  digitalWrite(red_led_button_sub, HIGH); // Setting red led pin to high so it cant ground
  digitalWrite(red_led_button_confirm, LOW); // Setting red led pin to high so it cant ground
  int Counter = 0;
  int x = 1;
  while (x == 1) {
    
    if (digitalRead(button_confirm) == LOW) {
        digitalWrite(red_led_button_confirm, HIGH); // Setting red led pin to low so it can ground
        Serial.print("Confirmed\n");
        return Counter;
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
}
// Function for getting all three data points from the user
void get_dice_data(){

  Serial << "What type of dice would you like to roll (6 for d6, 8 for d8, etc.)\n";
  dice_sides = get_number();
  delay(1000);
  Serial << "How many dice would you like to roll?\n";
  dice_number = get_number();
  delay(1000);
  Serial << "How many rolls should we subtract?\n";
  low_sub = get_number();
  delay(1000);
}

// Stat rolling function that will make each set of rolls and return the final number
int rollstat(int dice_number, int dice_sides, int low_sub){
  int x, stat_total;


  int rolls[dice_number];

  // For loop to get a roll for the number of dice
  for (int i = 0; i < (dice_number); i++) {
    x = random(1, (dice_sides + 1));
    rolls[i] = x;
    }
   sortArrayReverse(rolls, (dice_number)); // Sort function
  
   // For loop to print out each roll
  int rollsum = 0;
  for (int i = 0; i < (dice_number - low_sub); i++){
    rollsum += rolls[i];
    //Serial << " " << rolls[i];
  }
  return rollsum;
}



void setup() {
  lcd.init();
  lcd.backlight();
  menu_setup();
  Serial.begin(9600); // Serial Port for inital building
  first_boot(); // Runs once for creator info
}

void loop() {
  get_dice_data();
  Serial << "Str: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
  Serial << "Con: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
  Serial << "Dex: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
  Serial << "Int: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
  Serial << "Wis: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
  Serial << "Chr: " << rollstat(dice_number, dice_sides, low_sub) << "\n";
}
