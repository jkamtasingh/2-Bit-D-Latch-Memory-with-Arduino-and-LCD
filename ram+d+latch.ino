#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

const int LED1_Q  = 8;
const int LED2_Q  = 7;

const int EN_PIN_0 = 10;
const int EN_PIN_1 = 9;

const int D_PIN_0  = A0;
const int D_PIN_1  = A1;

bool q[2]       = {false, false};
bool enabled[2] = {false, false};

void updateLatch(int idx, int enPin, int dPin) {
  bool en = (digitalRead(enPin) == LOW);

  if (en) {
    q[idx]       = (digitalRead(dPin) == HIGH);
    enabled[idx] = true;
  } else {
    enabled[idx] = false;
  }
}

void updateLCD() {
  lcd_1.clear();
  for (int i = 0; i < 2; i++) {
    lcd_1.setCursor(0, i);
    lcd_1.print("L"); lcd_1.print(i);
    lcd_1.print(" Q="); lcd_1.print(q[i] ? "1" : "0");
    lcd_1.print(" /Q="); lcd_1.print(q[i] ? "0" : "1");
    lcd_1.print(enabled[i] ? " EDT" : " LCH");
  }
}

void writeLEDs() {
  if (q[0] == true) {
    digitalWrite(LED1_Q, HIGH);
  } else {
    digitalWrite(LED1_Q, LOW);
  }

  if (q[1] == true) {
    digitalWrite(LED2_Q, HIGH);
  } else {
    digitalWrite(LED2_Q, LOW);
  }
}

void setup() {
  pinMode(LED1_Q, OUTPUT);
  pinMode(LED2_Q, OUTPUT);

  pinMode(EN_PIN_0, INPUT_PULLUP);
  pinMode(EN_PIN_1, INPUT_PULLUP);

  pinMode(D_PIN_0, INPUT);
  pinMode(D_PIN_1, INPUT);

  Serial.begin(9600);

  lcd_1.begin(16, 2);
  lcd_1.clear();
  lcd_1.print("RAM D-Latch x2");
  delay(1200);
}

void loop() {
  updateLatch(0, EN_PIN_0, D_PIN_0);
  updateLatch(1, EN_PIN_1, D_PIN_1);

  writeLEDs();

  Serial.print("EN1="); Serial.print(digitalRead(EN_PIN_1));
  Serial.print(" D1="); Serial.print(digitalRead(D_PIN_1));
  Serial.print(" q1="); Serial.print(q[1]);
  Serial.print(" LED="); Serial.println(digitalRead(LED2_Q));

  updateLCD();
  delay(50);
}
