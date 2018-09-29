#include "LedControl.h"

// pins
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
const int DIN = 12;
const int CS = 11;
const int CLK = 10;

//variables
const int screenWidth = 8;
const int screenHeight = 8;

LedControl lc = LedControl(DIN, CS, CLK, 1);

void setup() {
  setupPins();
  setupLedBoard();
  drawSnake();
}

void setupLedBoard() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void setupPins() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
}

void loop() {
  char getDirection();
}

char getDirection() {
  if (analogRead(X_pin) == 1023) {
    return 'u';
  } else if (analogRead(X_pin) == 0) {
    return 'd';
  } else if (analogRead(Y_pin) == 0) {
    return 'l';
  } else if (analogRead(Y_pin) == 1023) {
    return 'r';
  }
  return 'n';
}

void drawSnake() {
  lc.setLed(0, 2, 2, true);
}
