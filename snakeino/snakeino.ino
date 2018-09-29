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
int snakeX, snakeY, foodX, foodY, score = 0, snakeSize = 0;
char direction = 'u';
int tailX[100], tailY[100];

LedControl lc = LedControl(DIN, CS, CLK, 1);

void setup() {
  Serial.begin(9600);
  setupPins();
  setupLedBoard();
  setupSnakePosition();
  setupFoodPosition();
  drawSnake();
}

void setupSnakePosition() {
  snakeX = 3;
  snakeY = 5;
}

void setupFoodPosition() {
  foodX = rand() % screenWidth;
  foodY = rand() % screenHeight;
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
  changeSnakeDirection(getJoystickDirection());
  manageEatenFood();
  manageSnakeOutOfBounds();
  drawSnake();
  drawSnakeTail();
  delay(500);
}

void manageSnakeOutOfBounds() {
  if (snakeX >= screenWidth) {
    snakeX = 0;
  } else if (snakeX < 0) {
    snakeX = screenWidth - 1;
  }
  if (snakeY >= screenHeight) {
    snakeY = 0;
  } else if (snakeY < 0) {
    snakeY = screenHeight - 1;
  }
}

void drawSnakeTail() {
  int prevSnakeX = snakeX - 1;
  int prevSnakeY = snakeY;

  for (int i = 0; i < snakeSize; i++) {
    showLed(prevSnakeX, prevSnakeY);
  }
}

void manageEatenFood() {
  if (snakeX == foodX && snakeY == foodY) {
    score++;
    snakeSize++;
    setupFoodPosition();
  }
}

char getJoystickDirection() {
  if (analogRead(X_pin) == 1023) {
    direction = 'u';
  } else if (analogRead(X_pin) == 0) {
    direction = 'd';
  } else if (analogRead(Y_pin) == 1023) {
    direction = 'l';
  } else if (analogRead(Y_pin) == 0) {
    direction = 'r';
  }
  return direction;
}

void changeSnakeDirection(char direction) {
  switch (direction) {
    case 'l':
      snakeX--;
      break;
    case 'r':
      snakeX++;
      break;
    case 'u':
      snakeY--;
      break;
    case 'd':
      snakeY++;
      break;
  }
}

void showLed(int row, int column) {
  lc.setLed(0, row, column, true);
}

void hideLed(int row, int column) {
  lc.setLed(0, row, column, false);
}

void drawSnake() {
  for (int i = 0; i < screenHeight; i++) {
    for (int j = 0; j < screenWidth; j++) {
      if (i == snakeY && j == snakeX) {
        showLed(snakeX, snakeY);
      } else if (i == foodY && j == foodX) {
        showLed(foodX, foodY);
      } else {
        hideLed(j, i);
      }
    }
  }
}
