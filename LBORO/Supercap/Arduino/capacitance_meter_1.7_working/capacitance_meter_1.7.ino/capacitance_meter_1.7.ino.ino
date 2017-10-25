#define VERSION 1.7
//#define BETA

#include <LiquidCrystal.h>
#include <DFR_Key.h>

#define PIN_ANALOG        A0
#define PIN_CHARGE        9
#define PIN_DISCHARGE     8
#define TIME_DISCHARGE    3e6 // Time at 0V to class as discharged
#define V_DISCHARGE       0.01 // Voltage to class as fully discharged (0.16V is 1 ADC step TBC???)
#define TIME_CHARGE_HOLD  2e6

#define RESISTOR_VAL      1182.0   // change this to whatever resistor value you are using
#define DISCHARGE_TIMER   5e6 // uS

#define MODE              _rebound

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

void discharge();
void discharge(float discharge_time);
unsigned long charge(float voltage_target);
void lcd_println(LiquidCrystal my_display, String in_buf, int line);
void lcd_update_lhs(LiquidCrystal my_display, String in_buf, int line, int len);
void lcd_update_rhs(LiquidCrystal my_display, String in_buf, int line, int len);
String time_to_farads(unsigned long dt, float R);
String time_to_string(float raw_uS);

unsigned long time_charge_start;
unsigned long time_discharge_start;
unsigned long dt;
String farads;
String cout_top    = "                ";
String cout_bottom = "                ";

bool mode_change_flag = true;
bool charge_hold_flag = false;
String mode_string;

//0.63 * 1023

enum State {
  _charge,
  _charged,
  _discharge,
  _safe,
  _done
} state = _discharge;

enum Mode {
  _capacitance,
  _rebound,
  _make_safe
} mode = MODE;


// SETUP //
void setup() {
  // Setup LCD Screen
  lcd.begin(16, 2);
  lcd.clear();
  String intro = "Capacitance " + String(VERSION, 1);
#ifdef BETA
  intro += "b";
#endif
  lcd_println(lcd, intro, 0);
  //keypad.setRate(10);

  // Setup pin modes
  pinMode(PIN_ANALOG, INPUT);
  pinMode(PIN_CHARGE, OUTPUT);
  pinMode(PIN_DISCHARGE, INPUT);

  // Start USB communication
  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.println(intro);
  Serial.println("Begin...");
}


// MAIN //
void loop() {
  // State machine //
  switch (mode) {
    case _capacitance:
      mode_string = "Cap'tance";
      switch (state) {
        case _discharge:
          discharge();
          break;
        case _safe:
          state = _charge;
          break;
        case _charge:
          dt = charge(0.63 * 5.0);
          break;
        case _charged:
          farads = time_to_farads(dt, RESISTOR_VAL);
          lcd_update_lhs(lcd, farads, 1, 8);
          state = _discharge; // Back to start
          break;
      }
      break;
    case _rebound:
      mode_string = "Rebound";
      switch (state) {
        case _discharge:
          discharge();
          break;
        case _safe:
          state = _charge;
          break;
        case _charge:
          dt = charge(4.9);
          break;
        case _charged:
          //farads = time_to_farads(dt, RESISTOR_VAL);
          //lcd_update_lhs(lcd, farads, 1, 8);
          discharge(DISCHARGE_TIMER); // Back to start
          break;
        case _done:
          delay(10);
          break;
      }
      break;
    case _make_safe:
      mode_string = "Make safe";
      switch (state) {
        case _charge:
        case _charged:
          state = _discharge;
          break;
        case _discharge:
        case _safe:
          discharge();
          break;
      }
      break;/*
    default:
      switch (state) {
        case _charge:
          break;
        case _discharge:
          break;
        case _safe:
          break;
        default:
          break;
      }
      break;*/
  }

  if (mode == _rebound) {
    String short_time_string = " L=" + time_to_string(DISCHARGE_TIMER);
    lcd_update_rhs(lcd, short_time_string, 1, 9);
    String charge_time_string = "H=" + time_to_string(TIME_CHARGE_HOLD);
    lcd_update_lhs(lcd, charge_time_string, 1, 8);
  }

  if (mode_change_flag) {
    lcd_update_lhs(lcd, mode_string, 0, 10);
    mode_change_flag = false;
  }

  String voltage = String(" ") + String(get_voltage(), 2) + String('V');
  lcd_update_rhs(lcd, voltage, 0, 6);

  Serial.println(String(micros()) + '\t' + String(get_voltage(),2));
  //lcd_println(lcd, cout_top, 0);
  //lcd_println(lcd, cout_bottom, 1);
}

float get_voltage() {
  return (float)analogRead(PIN_ANALOG) / 1023.0 * 5.0;
}

String time_to_farads(unsigned long dt, float R) {
  // convert microseconds to seconds ( 10^-6 )
  float farads = (double)dt * 1e-6 / R;
  String my_string;

  if (dt <= 10) {
    my_string += "NC";
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

String time_to_string(float raw_uS) {
  String my_string;

  if (raw_uS >= 1e4) {
    my_string = String(raw_uS / 1e6, 2) + "S ";
  }
  else if (raw_uS >= 1) {
    my_string = String(raw_uS / 1e3, 2) + "mS";
  }
  else {
    my_string = String(raw_uS, 2) + "uS";
  }
  return my_string;
}

void lcd_println(LiquidCrystal my_display, String in_buf, int line) {
  for (int x = 0 ; x = in_buf.length() - 16 ; x++) in_buf += " ";
  my_display.setCursor(0, line);
  my_display.print(in_buf);
}

void lcd_update_lhs(LiquidCrystal my_display, String in_buf, int line, int len) {
  for (int x = 0 ; x = in_buf.length() - len ; x++) in_buf += " ";

  my_display.setCursor(0, line);
  my_display.print(in_buf);
}

void lcd_update_rhs(LiquidCrystal my_display, String in_buf, int line, int len) {
  String buf = "";
  for (int x = 0 ; x = in_buf.length() - len ; x++) buf += " ";
  in_buf = buf + in_buf;

  my_display.setCursor(16 - len, line);
  my_display.print(in_buf);
}

unsigned long charge(float voltage_target) {
  pinMode(PIN_DISCHARGE, INPUT); // Should already be set

  if (DDRB & _BV(1) && digitalRead(PIN_CHARGE)) {
    // Already charging
    if (get_voltage() >= voltage_target && !charge_hold_flag) {
      //Serial.print("V: "); Serial.print(get_voltage(),2); Serial.print(" tgt:"); Serial.println(voltage_target,2);
      // Finished charging
      //Serial.println("Finished charging");
      time_charge_start = micros();
      charge_hold_flag = true;
    }
    else if (get_voltage() >= voltage_target && charge_hold_flag && (micros() - time_charge_start) >= TIME_CHARGE_HOLD) {
      charge_hold_flag = false;
      digitalWrite(PIN_CHARGE, false);
      pinMode(PIN_CHARGE, INPUT);
      state = _charged;
    }
  }
  else {
    // Not already charging
    if (get_voltage() > V_DISCHARGE) {
      // Cannot charge yet as not fully discharged
      //Serial.println("Needs discharging");
      state = _discharge;
    }
    else {
      // Ready to start charging
      //Serial.println("Start charging");
      pinMode(PIN_CHARGE, OUTPUT);
      digitalWrite(PIN_CHARGE, true);
    }
  }
  return micros() - time_charge_start;
}

void discharge() {
  switch (state) {
    case _discharge:
    case _safe:
      //Serial.println((micros() - time_discharge_start));
      // Already discharging
      if (get_voltage() > V_DISCHARGE) {
        // Still discharging
        //Serial.println("Still discharging");
        pinMode(PIN_CHARGE, INPUT);
        pinMode(PIN_DISCHARGE, OUTPUT);
        digitalWrite(PIN_DISCHARGE, false);
        time_discharge_start = micros();
      }
      else if ((micros() - time_discharge_start) >= TIME_DISCHARGE) {
        // Finished discharging
        //Serial.println("Finished discharging");
        pinMode(PIN_DISCHARGE, INPUT);
        state = _safe;
      }
      break;
    default:
      // Not already discharging
      //Serial.println("Not discharging");
      pinMode(PIN_CHARGE, INPUT);
      pinMode(PIN_DISCHARGE, OUTPUT);
      digitalWrite(PIN_DISCHARGE, false);
      state = _discharge;
      break;
  }
}

void discharge(float discharge_time) {
  if (DDRB & _BV(0)) {
    // Already discharging
    if ((float)(micros() - time_discharge_start) >= discharge_time) {
      // Finished discharging
      pinMode(PIN_DISCHARGE, INPUT);
      state = _done;
    }
  }
  else {
    // Not already discharging
    pinMode(PIN_CHARGE, INPUT);
    pinMode(PIN_DISCHARGE, OUTPUT);
    digitalWrite(PIN_DISCHARGE, false);
    time_discharge_start = micros();
  }
}
