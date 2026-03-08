#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27,16,2);     // LCD STARTUP

// ALL PIN OUTS ---------------------------------------------------------
// NUMBER PAD
const int Num0 = 2;
const int Num1 = 3;
const int Num2 = 6;
const int Num3 = 7;
const int Num4 = 8;
const int Num5 = 9;
const int Num6 = 10;
const int Num7 = 11;
const int Num8 = 12;
const int Num9 = 13;


// OPERATIONS
const int Add = 14;
const int Subs = 15;
const int Divd = 16;
const int Molt = 17;
const int sqr = 18;
const int PWR = 19;
 
const int EQUAL = 20;

const int Decimal = 21;     


// SPECIAL CHARACTERS
const int DELT = 22;
const int CLR = 26;


float FirstNum = 0;
float SecNum = 0;

char Operation = 0;

String current_input = "";
String expression = "";
String pico2_input = "";

bool sqr_mode = false;
 
// END PIN OUTS -----------------------------------------------------------
void setup() {
  Serial1.begin(115200);
  Serial.begin(9600);

  // PINMODES
  pinMode(Num0, INPUT_PULLUP);
  pinMode(Num1, INPUT_PULLUP);
  pinMode(Num2, INPUT_PULLUP);
  pinMode(Num3, INPUT_PULLUP);
  pinMode(Num4, INPUT_PULLUP);
  pinMode(Num5, INPUT_PULLUP);
  pinMode(Num6, INPUT_PULLUP);
  pinMode(Num7, INPUT_PULLUP);
  pinMode(Num8, INPUT_PULLUP);
  pinMode(Num9, INPUT_PULLUP);

  pinMode(Add, INPUT_PULLUP);
  pinMode(Subs, INPUT_PULLUP);
  pinMode(Divd, INPUT_PULLUP);
  pinMode(Molt, INPUT_PULLUP);
  pinMode(sqr, INPUT_PULLUP);
  pinMode(PWR, INPUT_PULLUP);

  pinMode(EQUAL, INPUT_PULLUP);
  pinMode(Decimal, INPUT_PULLUP);

  pinMode(CLR, INPUT_PULLUP);
  pinMode(DELT, INPUT_PULLUP);

  lcd.init();         //LCD START
  lcd.backlight();    //LCD BACKLIGHT START

  Calculator_Setup();     // WELCOME SCREEN -------------------------------------------------------
  lcd.clear();
}

void loop() {

  CheckNumberPad();

  Check_DEL_CLR(); 

  CheckDecimal();

  HandleOperators();
  
  Perform_SQR();

  CheckEqualPress();


}

// Begining of all functions (Are made outside of void loop)

void CheckNumberPad() {
  if(digitalRead(Num0) == LOW)  AddNumber("0");
  if(digitalRead(Num1) == LOW)  AddNumber("1"); 
  if(digitalRead(Num2) == LOW)  AddNumber("2");
  if(digitalRead(Num3) == LOW)  AddNumber("3");
  if(digitalRead(Num4) == LOW)  AddNumber("4");
    
  if(digitalRead(Num5) == LOW)  AddNumber("5");
  if(digitalRead(Num6) == LOW)  AddNumber("6");
  if(digitalRead(Num7) == LOW)  AddNumber("7");
  if(digitalRead(Num8) == LOW)  AddNumber("8");
  if(digitalRead(Num9) == LOW)  AddNumber("9");
}


void AddNumber(String n)  {

  current_input += n;
  updatedisplay();
  delay(100);

}

void updatedisplay()  {

  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,0);

  lcd.print(expression);
  lcd.print(current_input);
}


void Check_DEL_CLR()  {

  if(digitalRead(DELT) == LOW) {
    delay(100);

    if(current_input.length() > 0)  {
      current_input.remove(current_input.length() - 1);
      updatedisplay();
    }
  }

  if(digitalRead(CLR) == LOW) {

    delay(100);
    lcd.clear();

    current_input = "";
    expression = "";

    pico2_input = "";
    FirstNum = 0;
    SecNum = 0;
    sqr_mode = false;

  }
}


void CheckDecimal() {

  if(digitalRead(Decimal) == LOW) {

    delay(100);

    if (current_input.indexOf(".") == -1) {
      
      if(current_input == "") current_input = "0.";
      else current_input += ".";

      updatedisplay();
    }
  }
}


void HandleOperators()  {

  if(current_input > "") {

    if(digitalRead(Add) == LOW) ChoosenOP('+');
    if(digitalRead(Subs) == LOW) ChoosenOP('-');
    if(digitalRead(Divd) == LOW) ChoosenOP('/');
    if(digitalRead(Molt) == LOW) ChoosenOP('*');
    if(digitalRead(PWR) == LOW) ChoosenOP('^');

  }  
}


void ChoosenOP(char op)  {

  delay(100);

  Operation = op;
  FirstNum = current_input.toFloat();

  expression = current_input + op;
  current_input = "";

  updatedisplay();
  delay(100);
}


void Perform_SQR()  {

  if(digitalRead(sqr) == LOW) {

    delay(100);

    sqr_mode = true;

    expression = "sqr";
    current_input = "";

    updatedisplay();
  }

}


void CheckEqualPress()  {

  if(digitalRead(EQUAL) == LOW) {

    delay(100);

    if(sqr_mode)  {
      float value = current_input.toFloat();
      float results = sqrt(value);
      showResults(results);
      sqr_mode = false;
      return;
    }

    SecNum = current_input.toFloat();

    float results = CalculatorBrains(FirstNum, SecNum, Operation);

    showResults(results);
    CheckNumberPad();
  }
}


float CalculatorBrains(float a, float b, char oper)  {

  switch(oper) {

    case '+': return a + b;
    case '-': return a - b;
    case '*': return a*b;

    case '/':
      
      if(b == 0)  {
        ShowError("DIV 0");
        return 0;
      }
      return a/b;
    
    case '^': return pow(a, b);
  }

  return 0;

}


void showResults(float r)  {

  lcd.clear();

  if (r == (int)r) {
    lcd.print((int)r);     
    current_input = String((int)r);
  } 
  else {
    lcd.print(r, 3);       
    current_input = String(r, 3);
  }

  expression = "";
}


void ShowError(String msg)  {

  lcd.clear();
  lcd.print("ERROR");
  lcd.setCursor(0,1);
  lcd.print(msg);

  delay(3000);
  lcd.clear();
}



void Calculator_Setup() {       // WELCOME SCREEN FUNCTION
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("CASINO");
  delay(2000);

  lcd.setCursor(0,1);
  lcd.print("-");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("--");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("---");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("----");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("-----");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("------");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("-------");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("--------");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("---------");
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("----------");
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("-----------");
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("------------");
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("-------------");
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("--------------");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("---------------");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("----------------");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("-----------------");
}


