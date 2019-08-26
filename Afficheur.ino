int PIN_SCK = 12;
int PIN_SDA = 11;
int PIN_INT = 10;

const int delayvalue = 70;
const int pause = 20;

int cpt = 0;

void setup() {

  pinMode(PIN_SCK, OUTPUT);
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_INT, OUTPUT);


  digitalWrite(PIN_SDA, 1);
  digitalWrite(PIN_SCK, 1);
  digitalWrite(PIN_INT, 1);

  delay(1000);
}

int convert(int v) {
  int ret;
  if (v == 32) {
    ret = 36;
  } else if (v >= 48 && v <= 57) {
    ret = v - 48;
  } else {
    ret = (v - 99) + 12;
  }
  return ret;
}

void loop() {
  cpt++;
  String message = String(100 - cpt) + " v " + String(cpt) + "     ";
  char charBuf[9];
  message.toCharArray(charBuf, 9);

  digitalWrite(PIN_INT, 0);
  delayMicroseconds(delayvalue * 8);

  digitalWrite(PIN_SDA, 0); // start bit
  delayMicroseconds(delayvalue);
  digitalWrite(PIN_SCK, 0);
  delayMicroseconds(delayvalue);

  shift_out(PIN_SDA, PIN_SCK, B01000110, false);

  for (int i = 0; i < 8; i++) {
    int v = charBuf[i];
    shift_out(PIN_SDA, PIN_SCK, convert(v), false);
  }

  shift_out(PIN_SDA, PIN_SCK, 36, false);
  shift_out(PIN_SDA, PIN_SCK, 128, false);
  shift_out(PIN_SDA, PIN_SCK, 0, false);
  shift_out(PIN_SDA, PIN_SCK, 64, true); // 19 64 65 66 ..89 ..127

  digitalWrite(PIN_SCK, 1);
  delayMicroseconds(delayvalue);
  digitalWrite(PIN_SDA, 1);
  delayMicroseconds(delayvalue*4);
  digitalWrite(PIN_INT, 1);


  delay(200);
}
// uint8_t is the same as 8 bits aka one byte
void shift_out(uint8_t datapin, uint8_t clockpin, uint8_t val, boolean fin) {
  uint8_t i;

  for (i = 0; i < 8; i++)  {
    digitalWrite(datapin, !!(val & (1 << (7 - i))));
    delayMicroseconds(pause);

    digitalWrite(clockpin, 1);
    delayMicroseconds(delayvalue / 2);
    digitalWrite(clockpin, 0);
    delayMicroseconds(delayvalue);
  }

  digitalWrite(datapin, 1);
  delayMicroseconds(pause);

  digitalWrite(clockpin, 1);
  delayMicroseconds(delayvalue);

  digitalWrite(clockpin, 0);
  delayMicroseconds(delayvalue);
    
  if (!fin) {
    digitalWrite(datapin, 1);
    delayMicroseconds(pause);
  } else {
    digitalWrite(datapin, 0);
    delayMicroseconds(delayvalue);
  }

  if (! fin) {
    digitalWrite(clockpin, 0);
    delayMicroseconds(delayvalue);

    digitalWrite(clockpin, 0);
    delayMicroseconds(delayvalue);
  }
}
