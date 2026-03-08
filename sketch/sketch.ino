#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27,16,2);     // LCD STARTUP

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
String pico2_input = "";
 

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

       // WELCOME SCREEN -------------------------------------------------------
  lcd.clear();
}

void loop() {

  CheckNumberPad();

  Check_DEL_CLR(); 

  CheckDecimal();

  HandleOperators();


}


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
  delay(150);
  current_input += n;
  updatedisplay();
}

void updatedisplay()  {
  lcd.clear();
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

    if(current_input.length() > 0)  {

      delay(100);
      lcd.clear();
      current_input = "";
      pico2_input = "";
      FirstNum = 0;
      SecNum = 0;
    } 
  }
}


void CheckDecimal() {

  if(digitalRead(Decimal) == LOW) {

    delay(100);

    if (current_input.indexOf(".") == -1) {
      current_input += ".";
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
    if(digitalRead(sqr) == LOW) ChoosenOP('s');
    if(digitalRead(PWR) == LOW) ChoosenOP('^');
  }  
}


void ChoosenOP(char op)  {

  delay(100);

  Operation = op;
  FirstNum = current_input.toFloat();

  current_input = "";

  lcd.clear();
  lcd.print(FirstNum);
  lcd.print(op);
}











void Calculator_Setup() {       // WELCOKME SCREEN FUNCTION
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


