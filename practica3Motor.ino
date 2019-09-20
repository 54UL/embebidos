#include <Wire.h>
#include <Keypad.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <timer.h>
#include <string.h>
#include <Servo.h>

const uint16_t SCREEN_WIDTH = 128;
const uint16_t SCREEN_HEIGHT = 64;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'0', '0', '0', 'D'}};
//byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte rowPins[ROWS] = {30, 31, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {34, 35, 36,37}; //connect to the column pinouts of the keypad
//byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char g_str_buffer[32];
int getNumberFromKeypad(Keypad *ref, Adafruit_SSD1306 *screen_ref, const uint digits);
char * readStringFromKeypad(Keypad *ref, Adafruit_SSD1306 *screen_ref, const uint digits);

int Direccion,NumeroDeVuletas;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    keypad.setDebounceTime(100);
    keypad.setHoldTime(500);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("1 : izq    2: der");
    display.display();
    Direccion = getNumberFromKeypad(&keypad,&display,1); 
    display.print("numero de vueltas: ");
    display.setCursor(0,16);
    NumeroDeVuletas = getNumberFromKeypad(&keypad,&display,4); 
    delay(3000);
    display.clearDisplay();
}

void loop()
{
  
  display.setCursor(0,32);
  display.print("vueltas Actuales: ");

   
  display.clearDisplay();
  display.display();
}



int getNumberFromKeypad(Keypad *ref, Adafruit_SSD1306 *screen_ref, const uint digits)
{
  char buffer[digits];
  for (uint d_i = 0; d_i < digits; d_i++)
  {
    buffer[d_i] = ref->waitForKey();
    screen_ref->print(buffer[d_i]);
    screen_ref->display();
  }
  return (atoi(buffer));
}

char * readStringFromKeypad(Keypad *ref, Adafruit_SSD1306 *screen_ref, const uint digits)
{
   char buffer[digits];
    for (uint d_i = 0; d_i < digits; d_i++)
    {
      g_str_buffer[d_i] = ref->waitForKey();
      screen_ref->print(g_str_buffer[d_i]);
      screen_ref->display();
    }
  return buffer;
}