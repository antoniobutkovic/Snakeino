const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {

  char getDirection();

  Serial.print(getDirection());
  delay(500);
}

char getDirection() {
  if (analogRead(X_pin) == 1023) {
    return 'u';
  }else if (analogRead(X_pin) == 0) {
    return 'd';
  } else if (analogRead(Y_pin) == 0) {
    return 'l';
  } else if (analogRead(Y_pin) == 1023) {
    return 'r';
  }
 
}
