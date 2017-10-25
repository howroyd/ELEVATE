/*  RCTiming_capacitance_meter
     Paul Badger 2008
    Demonstrates use of RC time constants to measure the value of a capacitor

   Theory   A capcitor will charge, through a resistor, in one time constant, defined as T seconds where
      TC = R * C

      TC = time constant period in seconds
      R = resistance in ohms
      C = capacitance in farads (1 microfarad (ufd) = .0000001 farad = 10^-6 farads )

      The capacitor's voltage at one time constant is defined as 63.2% of the charging voltage.

    Hardware setup:
    Test Capacitor between common point and ground (positive side of an electrolytic capacitor  to common)
    Test Resistor between chargePin and common point
    220 ohm resistor between dischargePin and common point
    Wire between common point and analogPin (A/D input)
*/
#define VERSION 1.5
#define BETA

#include <LiquidCrystal.h>
#include <DFR_Key.h>
#include <Wire.h>
#include "gpio.h"
#define GPIO_ADDR         0x20
#define GPIO_LED_SAFE     13
#define GPIO_LED_DANGER   14
#define GPIO_SW_SAFE      15
#define GPIO_SW_5V_3V3    16
#define GPIO_SW_NO_FET    17
#define GPIO_FET_DIS      4
#define GPIO_FET_5V       11
#define GPIO_5V_150R      6
#define GPIO_5V_68R       5
#define GPIO_FET_3V3      12
#define GPIO_3V3_100R     10
#define GPIO_3V3_68R      7
const int GPIO_INTERNAL_5V[4] = {0, 1, 2, 3};
#define PIN_ANALOG        A0

Gpio    gpio(GPIO_ADDR);

#define DISCHARGE_TIMER   10 // uS
bool discharge_flag = false;


//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

#define resistorValue  6000.0   // change this to whatever resistor value you are using

char selector = 1;
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;
float milliFarads;
float farads;
float discharge();
float discharge(unsigned long);
long charge();
int Vtau;
void lcd_print(LiquidCrystal my_display, String in_buf, int line);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  String intro = "Capacitance " + String(VERSION, 1);
#ifdef BETA
  intro += "b";
#endif
  lcd_print(lcd, intro, 0);
  //keypad.setRate(10);


  // Setup pin modes
  pinMode(PIN_ANALOG, INPUT);

  Vtau = 0.63 * 1023;
  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.print("\n\nCapacitance Sensor at ");
  Serial.print((float)Vtau * 0.00488 / 0.63, 2);
  Serial.println("V\n\n");

  gpio.begin(0b1110000000000000);
  bool x[4] = {false, false, false, false};
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  gpio.set_bit(GPIO_FET_3V3, false);
  gpio.set_bit(GPIO_3V3_100R, false);
  gpio.set_bit(GPIO_3V3_68R, false);
  gpio.set_bit(GPIO_FET_5V, false);
  gpio.set_bit(GPIO_5V_150R, false);
  gpio.set_bit(GPIO_5V_68R, false);
  gpio.set_bit(GPIO_FET_DIS, false);

  gpio.set_bit(GPIO_LED_DANGER, true);
  gpio.set_bit(GPIO_LED_SAFE, true);

  Serial.println("Begin...");
}

void loop() {
  String verbose2 = "";
  String disp = "";

  /* dicharge the capacitor  */
  if (gpio.get_bit(GPIO_SW_SAFE)) {
    verbose2 += "Make safe";
    disp += "SAFE            ";
    discharge();
    Serial.println(verbose2);
    lcd_print(lcd, disp, 1);
    return;
  }
  else {
    if (gpio.get_bit(GPIO_SW_NO_FET)) { // Discharge timer
      float rebound_voltage = discharge(DISCHARGE_TIMER);
      verbose2 += "V_dis: "; verbose2 += String(rebound_voltage, 2);
      disp += "Rebound to ";
      disp += String(rebound_voltage, 2);
      disp += "V";
      Serial.println(verbose2);
      lcd_print(lcd, disp, 1);
      return; // Back to top
    }
    else {
      discharge();
    }
  }

  elapsedTime = charge();
  discharge_flag = false;

  // convert microseconds to seconds ( 10^-6 )
  farads = (double)elapsedTime * 1e-6 / resistorValue;
  verbose2 += elapsedTime;       // print the value to serial port
  verbose2 += "uS\t";         // print units and carriage return

  if (elapsedTime <= 2) {
    verbose2 += "Not connected";
    disp += "NC";
  }
  else if (farads >= 1.0) {
    verbose2 += (String(farads, 1) + "F");      // print the value to serial port
    disp += (String(farads, 1) + "F");         // print units and carriage return
    selector = 0;
  }
  else if (farads > 10e-3) {
    milliFarads = farads * 1e3;
    verbose2 += (String(milliFarads, 1) + "mF");      // print the value to serial port
    disp += (String(milliFarads, 1) + "mF");         // print units and carriage return
    selector = 1;
  }
  else if (farads > 10e-6) {
    microFarads = farads * 1e6;
    verbose2 += (String(microFarads, 1) + "uF");      // print the value to serial port
    disp += (String(microFarads, 1) + (char)228 + "F");         // print units and carriage return
    selector = 2;
  }
  else
  {
    nanoFarads = farads * 1e9;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
    verbose2 += (String(nanoFarads, 1) + "nF");      // print the value to serial port
    disp += (String(nanoFarads, 1) + "nF");         // print units and carriage return
    selector = 3;
  }

  Serial.println(verbose2);
  lcd_print(lcd, disp, 1);
}

void lcd_print(LiquidCrystal my_display, String in_buf, int line) {
  for (int x = 0 ; x = in_buf.length() - 16 ; x++) in_buf += " ";
  my_display.setCursor(0, line);
  my_display.print(in_buf);
}

long charge() {
  gpio.set_bit(GPIO_LED_DANGER, true);
  gpio.set_bit(GPIO_FET_DIS, false);
  bool x[4] = {true, true, true, true};
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  startTime = micros();
  Serial.print("Charging...");
  while (analogRead(PIN_ANALOG) < Vtau) {     // 647 is 63.2% of 1023, which corresponds to full-scale voltage
  }
  return micros() - startTime;
}

float discharge() {
  if (analogRead(PIN_ANALOG) <= 1) return 0.0;
  Serial.print("Discharging...");
  bool x[4] = {false, false, false, false};
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  gpio.set_bit(GPIO_FET_3V3, false);
  gpio.set_bit(GPIO_3V3_100R, false);
  gpio.set_bit(GPIO_3V3_68R, false);
  gpio.set_bit(GPIO_FET_5V, false);
  gpio.set_bit(GPIO_5V_150R, false);
  gpio.set_bit(GPIO_5V_68R, false);

  while (true) {       // wait until capacitor is completely discharge
    gpio.set_bit(GPIO_FET_DIS, true);
    delay(100);
    if (analogRead(PIN_ANALOG) <= 0) {
      gpio.set_bit(GPIO_FET_DIS, false);
      delay(100);
      if (analogRead(PIN_ANALOG) <= 0) {
        Serial.println("done!");
        gpio.set_bit(GPIO_LED_DANGER, false);
        break;
      }
    }
  }
  return 0.0;
}

float discharge(unsigned long short_time) {
  if (!discharge_flag) {
    Serial.print("Discharging..."); Serial.print(short_time); Serial.println("uS");
    bool x[4] = {false, false, false, false};
    gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    gpio.set_bit(GPIO_FET_3V3, false);
    gpio.set_bit(GPIO_3V3_100R, false);
    gpio.set_bit(GPIO_3V3_68R, false);
    gpio.set_bit(GPIO_FET_5V, false);
    gpio.set_bit(GPIO_5V_150R, false);
    gpio.set_bit(GPIO_5V_68R, false);

    gpio.set_bit(GPIO_FET_DIS, true);
    delayMicroseconds(short_time);
    gpio.set_bit(GPIO_FET_DIS, false);

    discharge_flag = true;
  }
  else gpio.set_bit(GPIO_FET_DIS, false);

  return (float)analogRead(PIN_ANALOG) / 1023.0 * 5.0;
}

