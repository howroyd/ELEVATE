#include <LiquidCrystal.h>
#include <DFR_Key.h>
#include <MCP3424.h>
#include <Wire.h>
#include "Cap_Sensor.h"
#include "Cap_Display.h"


#define analogPin      A1         // analog pin for measuring capacitor voltage
#define dischargePin   6         // pin to discharge the capacitor
#define resistorValue  100.0   // change this to whatever resistor value you are using
#define num_pins       3

int localKey = 0;
String keyString = "";
String farads_to_string(float farads);
const uint8_t charge_pin[num_pins] = {A5, A4, A3};
const float resistor[1]  = {resistorValue};

bool run = true;

Capacitance_Sensor   sensor(analogPin, dischargePin, charge_pin, resistor[0], num_pins);
Capacitance_Display  lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.begin(16, 2);
  lcd.init_keypad(A7);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitance V2.0");
  //keypad.setRate(10); // Default 10ms

  Serial.begin(115200);
  Serial.println("\n\nCapacitance Sensor V2.0");
}

void loop() {
  sensor.run(run);
  int user_in = lcd.run();

  if (user_in == 0) run = false;
  else if (user_in == 1) run = true;

  String cout = "";
  String disp = "";

  if (sensor.new_state || sensor.new_data) {
    cout += sensor.get_state();
    cout += " ";
    cout += farads_to_string(sensor.get_data());
    Serial.println(cout);
    lcd.clearLine(1);
    lcd.setCursor(0, 1);
    lcd.print(cout);
  }
}

String farads_to_string(float farads) {
  if (farads >= 1.0) return (String(farads, 1) + "F");
  else if (farads > 10e-3) return (String(farads * 1e3, 1) + "mF");
  else if (farads > 10e-6) return (String(farads * 1e6, 1) + "uF");
  else if (farads > 10e-9) return (String(farads * 1e9, 1) + "nF");
  else return "NC";
}

