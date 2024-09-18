#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // Setting LCD address 0x27 for a 20 chars and 4 line display

int buzzer = 2;
int green = 11;
int red = 12;
int pirSensor = 13;  //Pin that is attached to The PIR sensor
int state = LOW;  // By default no motion is detected
int var = 0;      //Variable that is storing the sensor status

uint8_t pacman[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b11011,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};

uint8_t pacmanOpen[] = {
  0b00000,
  0b00000,
  0b01110,
  0b11011,
  0b11100,
  0b01110,
  0b00000,
  0b00000
};

uint8_t dot[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00110,
  0b00110,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  // put your setup code here, to run once:

  pinMode(buzzer, OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  lcd.begin(20, 4); 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2,1);
	lcd.print("WELCOME TO HOME");
  lcd.setCursor(2,2);
  lcd.print("SECURITY SYSTEM");
  delay(1000);



}

void loop() {
  // put your main code here, to run repeatedly:
  var = digitalRead(pirSensor);   // read sensor value
  if (var == HIGH) {           // check if the sensor is HIGH (When object is detected)
    digitalWrite(red, HIGH);   // turn LED ON
    digitalWrite(green, LOW);
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Motion detected!"); 
      lcd.setCursor(3, 1);
      lcd.print("SETTING ALARM");
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(1000);        // ...for 1 sec
      lcd.setCursor(6, 2);
      lcd.print("LOADING");
        for (int i = 3; i < 16; i++) {
          lcd.setCursor(i, 3);
          lcd.print("\1");
          for (int j = i + 1; j < 16; j++) {
            lcd.setCursor(j, 3);
            lcd.print("\2");
          }
          lcd.createChar(1, pacman);
          delay(200);
          lcd.createChar(1, pacmanOpen);
          delay(200);
          lcd.setCursor(i, 3);
          lcd.print(" ");
      }
      state = HIGH;       // update variable state to HIGH
      noTone(buzzer);     // Stop sound...
    }
  } 
  else {
      digitalWrite(red, LOW); // turn LED OFF
      digitalWrite(green, HIGH);
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }

}
