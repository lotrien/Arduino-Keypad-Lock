#include <Keypad.h>
#include <Servo.h>

Servo locker;
int button = 2;
int lockerState = 0;
int k[9];
int closedPosition = 0;
int openPosition = 180;
int i = 0;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  locker.attach(10);
  attachInterrupt(digitalPinToInterrupt(button), open, RISING);
  keypad.addEventListener(keypadEvent);
}

void loop() {
  char key = keypad.getKey();
}

void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == PRESSED) {
    switch (key) {
      case '#':
        i = 0;
        if (k[0] == '1' && k[1] == '2' && k[2] == '3') {
          i = 0;
          k[0] = k[1] = k[2] = k[3] = 0;
          open();
        };
        break;
      case '*':
        i--;
        break;
      default:
        k[i] = key;
        i++;
        if (i > 4) {
          i = 0;
        }
      }
  }
}

void open() {
  if (lockerState == 0) {
    locker.write(closedPosition);
    lockerState = 1;
  } else if (lockerState == 1) {
    locker.write(openPosition);
    lockerState = 0;
  }
}
