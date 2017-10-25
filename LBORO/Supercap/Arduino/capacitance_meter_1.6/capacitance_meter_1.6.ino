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
#define VERSION 1.6
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

#define RESISTOR_VAL      6000.0   // change this to whatever resistor value you are using
#define DISCHARGE_TIMER   10 // uS
bool discharge_flag = false;


//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

void discharge();
void discharge(unsigned long);
unsigned long charge();
void lcd_print(LiquidCrystal my_display, String in_buf, int line);
String time_to_farads(unsigned long dt, float R);

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

  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.println("\n\nCapacitance Sensor");

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
  String disp = "";

  // State machine //
  if (gpio.get_bit(GPIO_SW_SAFE)) {
    // Make safe
    discharge();
    disp += "SAFE";
  }
  else if (gpio.get_bit(GPIO_SW_NO_FET)) {
    // Rebound timer
    if (!discharge_flag) {
      charge();
      discharge(DISCHARGE_TIMER);
      discharge_flag = true;
    }
    float v_rebound = (float)analogRead(PIN_ANALOG) / 1023.0 * 5.0;
    disp += "Rebound: ";
    disp += String(v_rebound,2);
    disp += "V";
  }
  else {
    // Normal capacitance meter
    discharge(); discharge_flag = false;
    disp += time_to_farads(charge(), RESISTOR_VAL);
  }

  Serial.println(disp);
  lcd_print(lcd, disp.substring(disp.indexOf('\t') + 1), 1);
}

String time_to_farads(unsigned long dt, float R) {
  // convert microseconds to seconds ( 10^-6 )
  float farads = (double)dt * 1e-6 / R;
  String my_string = String(dt);       // print the value to serial port
  my_string += "uS\t";         // print units and carriage return

  if (dt <= 10) {
    my_string += "Not connected";
  }
  else if (farads >= 1.0) {
    my_string += (String(farads, 1) + "F");      // print the value to serial port
  }
  else if (farads > 10e-3) {
    my_string += (String(farads * 1e3, 1) + "mF");      // print the value to serial port
  }
  else if (farads > 10e-6) {
    my_string += (String(farads * 1e6, 1) + "uF");      // print the value to serial port
  }
  else
  {
    my_string += (String(farads * 1e9, 1) + "nF");      // print the value to serial port
  }
  return my_string;
}

void lcd_print(LiquidCrystal my_display, String in_buf, int line) {
  for (int x = 0 ; x = in_buf.length() - 16 ; x++) in_buf += " ";
  my_display.setCursor(0, line);
  my_display.print(in_buf);
}

unsigned long charge() {
  gpio.set_bit(GPIO_LED_DANGER, true);
  gpio.set_bit(GPIO_LED_SAFE, false);
  gpio.set_bit(GPIO_FET_DIS, false);
  bool x[4] = {true, true, true, true};
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  unsigned long startTime = micros();
  Serial.print("Charging...");
  while (analogRead(PIN_ANALOG) < (0.63 * 1023)) {     // 647 is 63.2% of 1023, which corresponds to full-scale voltage
  }
  unsigned long dt = micros() - startTime;
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, !x, 4);
  return dt;
}

void discharge() {
  if (analogRead(PIN_ANALOG) <= 1) return;
  Serial.print("Discharging...");
  bool x[4] = {false, false, false, false};
  gpio.set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  gpio.set_bit(GPIO_FET_3V3, false);
  gpio.set_bit(GPIO_3V3_100R, false);
  gpio.set_bit(GPIO_3V3_68R, false);
  gpio.set_bit(GPIO_FET_5V, false);
  gpio.set_bit(GPIO_5V_150R, false);
  gpio.set_bit(GPIO_5V_68R, false);

  while (true) {       // wait until capacitor is completely discharged
    gpio.set_bit(GPIO_FET_DIS, true);
    delay(100);
    if (analogRead(PIN_ANALOG) <= 0) {
      gpio.set_bit(GPIO_FET_DIS, false);
      delay(100);
      if (analogRead(PIN_ANALOG) <= 0) {
        Serial.println("done!");
        gpio.set_bit(GPIO_LED_DANGER, false);
        gpio.set_bit(GPIO_LED_SAFE, true);
        break;
      }
    }
  }
  return;
}

void discharge(unsigned long short_time) {
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

  return; //(float)analogRead(PIN_ANALOG) / 1023.0 * 5.0;
}

