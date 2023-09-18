#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// SCL A5
// SDA A4
#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  // myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(6, INPUT_PULLUP); //Switch
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
  display.display();
  display.clearDisplay();
  display.setFont( & FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.println("Ardayf.io");
  display.display();
  delay(2000);
}

int sec1 = 0;
int min1 = 0;
unsigned long msec = 0;
unsigned long mili = 0;
int press = 0;
int phase = 0;
int start = 0;
unsigned long time = 0;

void loop() {
  /*
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/

  display.clearDisplay();
  if (digitalRead(6) == 0) {
    if (press == 0) {
      phase = phase + 1;
      press = 1;
      if (phase > 2)
        phase = 0;
    }
  } else {
    press = 0;
  }
  if (phase == 0) {
    display.setFont( & FreeSans9pt7b);
    display.setFont();
    display.setCursor(0, 15);
    display.println("Ardayf.io Water Boarding Alarm Clock");
    display.setFont( & FreeSans12pt7b);
    display.setFont();
    display.setCursor(30, 35);
    display.print("Press Start");

    sec1 = 0;
    min1 = 0;
    time = 0;
    mili = 0;
    msec = 0;
    start = 0;
  } else if (phase == 1) {
    display.clearDisplay();
    display.setFont( & FreeSans12pt7b);
    display.setFont();
    display.setCursor(3, 0);
    display.print("Water Boarding Alarm");
    display.setFont( & FreeSans9pt7b);

    if (start == 0) {
      start = 1;
      time = millis();
    }
    msec = (millis() - time);

    //hour1 = (msec / 60000)/60;
    min1 = msec / 60000;

    if ((msec / 1000) > 59) {
      sec1 = (msec / 1000) - (min1 * 60);
    } else {
      sec1 = msec / 1000;
    }

    mili = (msec % 1000) / 10;

    display.setCursor(42, 30);
    if (min1 <= 9) {
      display.print("0");
      display.print(min1);
    } else {
      display.print(min1);
    }
    display.print(":");
    if (sec1 <= 9) {
      display.print("0");
      display.print(sec1);
    } else {
      display.print(sec1);
    }
    display.setFont( & FreeSans12pt7b);
    display.setCursor(50, 57);

    if (mili <= 9) {
      display.print("0");
      display.print(mili);
    } else {
      display.print(mili);
    }

    if(msec > 25200000){ // 5000 = 5 seconds
      phase = 2;
    }
  }

  if (phase == 2) {
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo.write(0);
    delay(1000);
    myservo.detach();
    Serial.println("setting it to 0");
    display.clearDisplay();
    display.setFont( & FreeSans12pt7b);
    display.setFont();
    display.setCursor(0, 0);
    display.print("Wake Up Time:");
    display.setFont( & FreeSans9pt7b);
    display.setCursor(42, 30);
    if (min1 <= 9) {
      display.print("0");
      display.print(min1);
    } else {
      display.print(min1);
    }

    display.print(":");

    if (sec1 <= 9) {
      display.print("0");
      display.print(sec1);
    } else {
      display.print(sec1);
    }
    display.setFont( & FreeSans12pt7b);
    display.setCursor(50, 57);

    if (mili <= 9) {
      display.print("0");
      display.print(mili);
    } else {
      display.print(mili);
    }
  }
  display.display();
}