#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----------------------------------------------------------------------
// PIN OUTS
// ----------------------------------------------------------------------

const int Num0 = 20;
const int Num1 = 19;
const int Num2 = 22;
const int Num3 = 12;
const int Num4 = 18;
const int Num5 = 26;
const int Num6 = 11;
const int Num7 = 17;
const int Num8 = 15;
const int Num9 = 10;

const int Add = 3;
const int Subs = 6;
const int Divd = 7;
const int Molt = 8;
const int sqr = 16;
const int PWR = 14;

const int EQUAL = 13;
const int Decimal = 21;

const int DELT = 9;
const int CLR = 2;

// ----------------------------------------------------------------------
// BUTTON SYSTEM
// ----------------------------------------------------------------------

#define TOTAL_BUTTONS 19

int buttonPins[TOTAL_BUTTONS] = {
  Num0, Num1, Num2, Num3, Num4,
  Num5, Num6, Num7, Num8, Num9,
  Add, Subs, Divd, Molt, sqr,
  PWR, EQUAL, Decimal, DELT
};

bool buttonState[TOTAL_BUTTONS];
bool lastReading[TOTAL_BUTTONS];
unsigned long lastDebounceTime[TOTAL_BUTTONS];

const unsigned long debounceDelay = 30;

// CLR
bool clrState = HIGH;
bool clrLastReading = HIGH;
unsigned long clrLastDebounce = 0;

// ----------------------------------------------------------------------
// CURSOR
// ----------------------------------------------------------------------

unsigned long lastBlinkTime = 0;
bool cursorVisible = true;
const unsigned long blinkInterval = 500;

// ----------------------------------------------------------------------
// STATE CONTROL
// ----------------------------------------------------------------------

bool resultdisplayed = false;
bool resultLocked = false;
String displayLine1 = "";

// ----------------------------------------------------------------------
// VARIABLES
// ----------------------------------------------------------------------

float FirstNum = 0;
float SecNum = 0;
char Operation = 0;

String current_input = "";
String expression = "";
String ExpansionCommand = "";

bool sqr_mode = false;

// ----------------------------------------------------------------------
// SETUP
// ----------------------------------------------------------------------

void setup() {
  Serial1.begin(115200);
  Serial.begin(9600);

  for (int i = 0; i < TOTAL_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonState[i] = HIGH;
    lastReading[i] = HIGH;
    lastDebounceTime[i] = 0;
  }

  pinMode(CLR, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  Calculator_Setup();
  lcd.clear();
}

// ----------------------------------------------------------------------
// LOOP
// ----------------------------------------------------------------------

void loop() {
  CheckNumberPad();
  Check_DEL_CLR();
  CheckDecimal();
  HandleOperators();
  Perform_SQR();
  CheckEqualPress();
  CheckExpansionModule();

  HandleCursorBlink();
}

// ----------------------------------------------------------------------
// BUTTON INPUT
// ----------------------------------------------------------------------

bool isPressed(int pin, int index) {
  bool reading = digitalRead(pin);

  if (reading != lastReading[index]) {
    lastDebounceTime[index] = millis();
  }

  if ((millis() - lastDebounceTime[index]) > debounceDelay) {
    if (reading != buttonState[index]) {
      buttonState[index] = reading;
      if (buttonState[index] == LOW) {
        lastReading[index] = reading;
        return true;
      }
    }
  }
  lastReading[index] = reading;
  return false;
}

// ----------------------------------------------------------------------
// NUMBER INPUT
// ----------------------------------------------------------------------

void CheckNumberPad() {
  for (int i = 0; i < 10; i++) {
    if (isPressed(buttonPins[i], i)) {
      if (resultdisplayed) {
        ResetCalculator();
      }
      resultLocked = false;
      AddNumber(String(i));
    }
  }
}

void AddNumber(String n) {
  current_input += n;
  updatedisplay();
}

// ----------------------------------------------------------------------
// DISPLAY
// ----------------------------------------------------------------------

void updatedisplay() {
  String fullText;

  if (resultdisplayed)
    fullText = displayLine1;
  else
    fullText = expression + current_input;

  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);

  if (fullText.length() <= 16)
    lcd.print(fullText);
  else
    lcd.print(fullText.substring(fullText.length() - 16));
}

void HandleCursorBlink() {
  if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis();
    cursorVisible = !cursorVisible;

    String fullText;
    if (resultLocked)
      fullText = displayLine1;
    else
      fullText = expression + current_input;

    String visibleText;
    if (fullText.length() <= 16)
      visibleText = fullText;
    else
      visibleText = fullText.substring(fullText.length() - 16);

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(visibleText);

    int pos = visibleText.length();
    if (pos < 16 && !resultLocked) {
      lcd.setCursor(pos, 0);
      lcd.print(cursorVisible ? "_" : " ");
    }
  }
}

// ----------------------------------------------------------------------
// DELETE / CLEAR
// ----------------------------------------------------------------------

void Check_DEL_CLR() {
  if (isPressed(DELT, 18)) {
    if (current_input.length() > 0) {
      current_input.remove(current_input.length() - 1);
      updatedisplay();
    }
  }

  if (digitalRead(CLR) == LOW) {
    ResetCalculator();
  }
}

// ----------------------------------------------------------------------
// DECIMAL
// ----------------------------------------------------------------------

void CheckDecimal() {
  if (isPressed(Decimal, 17)) {
    if (resultdisplayed) ResetCalculator();
    resultLocked = false;

    if (current_input.indexOf(".") == -1) {
      if (current_input == "") current_input = "0.";
      else current_input += ".";
      updatedisplay();
    }
  }
}

// ----------------------------------------------------------------------
// OPERATORS (UPDATED FOR NEGATIVES)
// ----------------------------------------------------------------------

void HandleOperators() {
  // SPECIAL CASE: Negative Sign
  if (isPressed(Subs, 11)) {
    if (current_input == "" && !sqr_mode) {
      // If we just finished a calculation, a minus starts a new negative chain
      if (resultdisplayed) ResetCalculator(); 
      current_input = "-";
      updatedisplay();
    } else {
      ChoosenOP('-');
    }
  }

  if (current_input != "" && current_input != "-") {
    if (isPressed(Add, 10)) ChoosenOP('+');
    if (isPressed(Divd, 12)) ChoosenOP('/');
    if (isPressed(Molt, 13)) ChoosenOP('*');
    if (isPressed(PWR, 15)) ChoosenOP('^');
  }
}

void ChoosenOP(char op) {
  // Prevent operator being set if current_input is just a negative sign
  if (current_input == "-") return;

  Operation = op;
  FirstNum = current_input.toFloat();

  expression = current_input + op;
  current_input = "";

  resultdisplayed = false;
  resultLocked = false;

  lcd.clear(); 
  updatedisplay();
}

// ----------------------------------------------------------------------
// SQRT
// ----------------------------------------------------------------------

void Perform_SQR() {
  if (isPressed(sqr, 14)) {
    sqr_mode = true;
    expression = "sqr";
    current_input = "";
    updatedisplay();
  }
}

// ----------------------------------------------------------------------
// EQUAL
// ----------------------------------------------------------------------

void CheckEqualPress() {
  if (isPressed(EQUAL, 16)) {
    if (resultLocked || current_input == "" || current_input == "-") return; 

    if (sqr_mode) {
      float v = current_input.toFloat();
      if (v < 0) {
         lcd.setCursor(0,1);
         lcd.print("=Math Error");
         return;
      }
      showResults(sqrt(v));
      sqr_mode = false;
      return;
    }

    SecNum = current_input.toFloat();
    float result = CalculatorBrains(FirstNum, SecNum, Operation);

    if (isnan(result)) {
       lcd.setCursor(0,1);
       lcd.print("=Error");
       return;
    }

    showResults(result);
  }
}

// ----------------------------------------------------------------------
// RESULT HANDLER
// ----------------------------------------------------------------------

void showResults(float r) {
  String resultStr;

  if (r == (int)r)
    resultStr = String((int)r);
  else
    resultStr = String(r, 3);

  displayLine1 = expression + current_input;

  lcd.clear();
  lcd.setCursor(0, 0);

  if (displayLine1.length() <= 16)
    lcd.print(displayLine1);
  else
    lcd.print(displayLine1.substring(displayLine1.length() - 16));

  lcd.setCursor(0, 1);
  lcd.print("=" + resultStr);

  current_input = resultStr;
  expression = ""; 

  resultdisplayed = true;
  resultLocked = true;
}

// ----------------------------------------------------------------------
// RESET
// ----------------------------------------------------------------------

void ResetCalculator() {
  current_input = "";
  expression = "";
  displayLine1 = "";
  FirstNum = 0;
  SecNum = 0;
  Operation = 0;
  sqr_mode = false;
  resultdisplayed = false;
  resultLocked = false;
  lcd.clear();
}

// ----------------------------------------------------------------------
// EXPANSION MODULE
// ----------------------------------------------------------------------

void CheckExpansionModule() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      handleExpansioncard(ExpansionCommand);
      ExpansionCommand = "";
    } else {
      ExpansionCommand += c;
    }
  }
}

void handleExpansioncard(String cmd) {
  cmd.toUpperCase();
  float v = current_input.toFloat();

  if (cmd == "SIN") showResults(sin(radians(v)));
  if (cmd == "COS") showResults(cos(radians(v)));
  if (cmd == "TAN") showResults(tan(radians(v)));
  if (cmd == "ASIN") showResults(degrees(asin(v)));
  if (cmd == "ACOS") showResults(degrees(acos(v)));
  if (cmd == "ATAN") showResults(degrees(atan(v)));

  if (cmd == "LP") { current_input += "("; updatedisplay(); }
  if (cmd == "RP") { current_input += ")"; updatedisplay(); }
}

float CalculatorBrains(float a, float b, char oper) {
  switch (oper) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
      if (b == 0) return NAN;
      return a / b;
    case '^': return pow(a, b);
  }
  return 0;
}

void Calculator_Setup() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("CASINO");
  delay(1000);
  for (int i = 1; i <= 16; i++) {
    lcd.setCursor(0, 1);
    for (int j = 0; j < i; j++) lcd.print("-");
    delay(80);
  }
}