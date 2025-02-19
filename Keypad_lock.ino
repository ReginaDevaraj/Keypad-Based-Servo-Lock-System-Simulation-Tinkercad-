#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd(address, col, row);

Servo servo_lock; //creating object
const int servo_pin= 10;
const int buzzer_pin= 11;

const int rows= 4;
const int cols=4;

char keys[rows][cols]=
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowpins[rows]= {9,8,7,6};
byte colpins[cols]= {5,4,3,2};

Keypad keypad= Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);

const char original_password[9]="A123456B";
char entered_password[9];


void setup()
{
  Wire.begin();
  lcd.init(); //lcd,begin(cols, rows);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD");
  
  pinMode(buzzer_pin, OUTPUT);
  servo_lock.attach(servo_pin);
  servo_lock.write(0);
}

void loop()
{
  int i = 0;
  lcd.setCursor(0, 1);
  
  while (i < 8) 
  {  
    char key = keypad.getKey();
    
    if (key) 
    {
      digitalWrite(buzzer_pin, HIGH);
      delay(10);
      digitalWrite(buzzer_pin, LOW);

      entered_password[i] = key;  
      lcd.setCursor(i, 1);
      lcd.print('*');  
      
      i++;
    }
  }
 entered_password[8]='\0';
 
  if(strcmp(entered_password, original_password)==0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DOOR OPENED");
    servo_lock.write(90);
    delay(20);
    servo_lock.write(180);
    delay(3000);
    servo_lock.write(180);
    delay(20);
    servo_lock.write(90);
    delay(20);
    servo_lock.write(0);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");
  }
  
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD");
      
}