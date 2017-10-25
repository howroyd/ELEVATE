#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DFR_Key.h>
#include <MCP3424.h>
#include <Wire.h>
#include "Cap_Sensor.h"
#include "Cap_Display.h"
#include "gpio.h"

#define VERSION 2.2

#define KEYPAD_PIN     A7
#define GPIO_ADDR 0x20

int localKey = 0;
String keyString = "";
String farads_to_string(float farads);
bool run = true;

//Capacitance_Sensor   sensor(analogPin, dischargePin, charge_pin, resistor[0], num_pins);
Capacitance_Display  lcd(12, 11, 5, 4, 3, 2);
Capacitance_Sensor   sensor(GPIO_ADDR);

void setup() {
  lcd.begin(KEYPAD_PIN);
  lcd.print(String("Capacitance V") + String(VERSION, 1));
  lcd.setCursor(0, 1);
  lcd.print("Lboro Uni 2016");

  sensor.begin();
  sensor.set_supply("INTERNAL");
  sensor.set_resistor("INTERNAL");

  Serial.begin(115200);
  Serial.println(String("\n\nCapacitance Sensor ") + String(VERSION));

  while (lcd.run() < 0) {
    Serial.println("Waiting");
    continue;
  }
}

void loop() {
  bool override_switch = sensor.run(run);
  //return;
  int user_in = lcd.run();

  //if (user_in == 0) run = false;
  //else if (user_in == 1) run = true;

  String cout = "";
  String disp = "";
  //Serial.println(sensor.get_state());
  if (sensor.new_state || sensor.new_data) {
    cout += sensor.get_state();
    cout += " ";
    cout += farads_to_string(sensor.get_capacitance());
    cout += " ";
    cout += String(sensor.get_discharge(), 0);
    cout += String("uS");
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

