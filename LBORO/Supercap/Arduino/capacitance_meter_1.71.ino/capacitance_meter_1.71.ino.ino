#define VERSION 1.71
//#define BETA
//#define FILTERS_ON

#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <DFR_Key.h>

#define LOW_VOLTAGE
//#define FILTERS_ON

#define PIN_ANALOG        A0
#define PIN_CHARGE        9
#define PIN_CHARGE_1V5    7
#define PIN_DISCHARGE     8
#define PIN_FET           6
#define KEYPAD_PIN        A1

#define TIME_DISCHARGE    5000   // mS at 0V to class as discharged
#define V_DISCHARGE       0.03   // Voltage to class as fully discharged (0.16V is 1 ADC step TBC???)
#define TIME_CHARGE_HOLD  2e6
#define TIME_DISCHARGE_HOLD 5000 //mS

#define RESISTOR_VAL       1182.0   // change this to whatever resistor value you are using
#define RESISTOR_VAL_LOW   1300.0   // change this to whatever resistor value you are using

//#define MODE              _rebound

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

void discharge();
void discharge(unsigned long discharge_time);
unsigned long charge(const int pin, float voltage_target);
unsigned long charge(const int pin, float voltage_target, unsigned long _time_hold);
void lcd_println(LiquidCrystal my_display, String in_buf, int line);
void lcd_update_lhs(LiquidCrystal my_display, String in_buf, int line, int len);
void lcd_update_rhs(LiquidCrystal my_display, String in_buf, int line, int len);
String time_to_farads(unsigned long dt, float R);
String time_to_string(float raw_uS);

int led_keypad_run(DFR_Key _keypad);

unsigned long time_charge_start;
unsigned long time_discharge_start;
unsigned long dt;
String farads;
String cout_top    = "                ";
String cout_bottom = "                ";

unsigned long time_charge_hold = TIME_CHARGE_HOLD;
unsigned long time_discharge_hold = TIME_DISCHARGE_HOLD;

bool mode_change_flag = true;
bool charge_hold_flag = false;
String mode_string;

float _voltage;
float _voltageLast1;
float _voltageLast2;

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
};

byte mode;

enum Menu {
  _menu_mode,
  _menu_high,
  _menu_low
} menu = _menu_mode;


// SETUP //
void setup() {
  // Setup LCD Screen
  keypad.setPin(KEYPAD_PIN);
  lcd.begin(16, 2);
  lcd.clear();
  String intro = "Capacitance " + String(VERSION, 1);
#ifdef BETA
  intro += "b";
#endif
  lcd_println(lcd, intro, 0);
  //keypad.setRate(10);

  _voltage = 0.0;
  _voltageLast1 = 0.0;
  _voltageLast1 = 0.0;

  // Setup pin modes
  pinMode(KEYPAD_PIN, INPUT);
  pinMode(PIN_ANALOG, INPUT);
  pinMode(PIN_CHARGE, INPUT);
  pinMode(PIN_CHARGE_1V5, OUTPUT);
  pinMode(PIN_FET, OUTPUT);
  digitalWrite(PIN_CHARGE_1V5, LOW);
  digitalWrite(PIN_FET, LOW);
  pinMode(PIN_DISCHARGE, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, false);
  analogReference(DEFAULT);

  switch (EEPROM.read(0)) {
    case 1:
      mode = _capacitance;
      break;
    case 2:
      mode = _rebound;
      break;
    default:
      mode = _make_safe;
      break;
  }



  // Start USB communication
  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.println(intro);
  Serial.println("Begin...");
}


// MAIN //
void loop() {/*
  while (true) {
    digitalWrite(PIN_FET, true);
    digitalWrite(13, true);
    String _voltageString = String(" ") + String(get_voltage(), 2) + String('V');
    lcd_update_rhs(lcd, _voltageString, 0, 6);
    delay(500);
    _voltageString = String(" ") + String(get_voltage(), 2) + String('V');
    lcd_update_rhs(lcd, _voltageString, 0, 6);
    delay(500);
    digitalWrite(PIN_FET, false);
    digitalWrite(13, false);
    _voltageString = String(" ") + String(get_voltage(), 2) + String('V');
    lcd_update_rhs(lcd, _voltageString, 0, 6);
    delay(500);
    _voltageString = String(" ") + String(get_voltage(), 2) + String('V');
    lcd_update_rhs(lcd, _voltageString, 0, 6);
    delay(500);
  }*/


  led_keypad_run(keypad);
  _voltage = get_voltage();

  // State machine //
  switch (mode) {
    case _capacitance:
      mode_string = "Measure";
      switch (state) {
        case _discharge:
          discharge();
          break;
        case _safe:
          state = _charge;
          break;
        case _charge:
#ifdef LOW_VOLTAGE
          dt = charge(PIN_CHARGE_1V5, 0.63 * 1.49);
#else
          dt = charge(PIN_CHARGE, 0.63 * 5.0);
#endif
          break;
        case _charged:
#ifdef LOW_VOLTAGE
          farads = time_to_farads(dt, RESISTOR_VAL_LOW);
#else
          farads = time_to_farads(dt, RESISTOR_VAL);
#endif
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
#ifdef LOW_VOLTAGE
          charge(PIN_CHARGE_1V5, 1.0, time_charge_hold) / 100;
#else
          charge(PIN_CHARGE, 4.9, time_charge_hold) / 100;
#endif
          break;
        case _charged:
          //farads = time_to_farads(dt, RESISTOR_VAL);
          //lcd_update_lhs(lcd, farads, 1, 8);
          discharge(time_discharge_hold); // Back to start
          break;
        case _done:

          break;
      }
      break;
    case _make_safe:
      mode_string = "Mk safe";
      if (state == _safe) lcd_update_lhs(lcd, "    SAFE", 1, 9);
      else lcd_update_lhs(lcd, "NOT SAFE", 1, 9);

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
  /*
    if (mode == _rebound) {
      String short_time_string = " L=" + time_to_string(time_discharge_hold);
      lcd_update_rhs(lcd, short_time_string, 1, 9);
      String charge_time_string = "H=" + time_to_string(time_charge_hold);
      lcd_update_lhs(lcd, charge_time_string, 1, 8);
    }
  */
  if (mode_change_flag) {
    lcd.clear();
    lcd_update_lhs(lcd, mode_string, 0, 10);
    mode_change_flag = false;

    switch (mode) {
      case _capacitance:
        EEPROM.write(0, 1);
        break;
      case _rebound:
        EEPROM.write(0, 2);
        break;
      case _make_safe:
      default:
        EEPROM.write(0, 3);
        break;
    }
    discharge();
  }

  String _voltageString = String(" ") + String(_voltage, 2) + String('V');
  lcd_update_rhs(lcd, _voltageString, 0, 6);

  //#ifdef FILTERS_ON
  //  _voltageLast1 = _voltageLast1 + 0.5 * (_voltage - _voltageLast1);
  //  _voltageLast2 = _voltageLast2 + 0.2 * (_voltage - _voltageLast2);
  //  Serial.println(String(micros()) + '\t' + String(_voltage, 3) + '\t' + String(_voltageLast1, 3) + '\t' + String(_voltageLast2, 3));
  //#else
  Serial.println(String(micros()) + '\t' + String(_voltage, 4));
  //#endif

  //lcd_println(lcd, cout_top, 0);
  //lcd_println(lcd, cout_bottom, 1);

}

float get_voltage() {
  static float val;
#ifdef LOW_VOLTAGE
  analogReference(EXTERNAL);
  for (int i = 0; i < 5; i++) analogRead(PIN_ANALOG); // Bin 5 readings while ADC settles
  //val = (float)analogRead(PIN_ANALOG) / 1023.0 * 1.8575; // AREF pin has 32k resistor
  val = (float)map(analogRead(PIN_ANALOG), 0, 1023, 0, 40000) / 10000.0; // AREF pin has 32k resistor

  analogReference(DEFAULT);
  for (int i = 0; i < 5; i++) analogRead(PIN_ANALOG); // Bin 5 readings while ADC settles
#else
  //val = (float)analogRead(PIN_ANALOG) / 1023.0 * 5.0;
  val = (float)map(analogRead(PIN_ANALOG), 0, 1023, 0, 50000) / 10000.0; // AREF pin has 32k resistor
#endif
  return val;
}

String time_to_farads(unsigned long dt, float R) {
  // convert microseconds to seconds ( 10^-6 )
  float farads = (float)dt * 1e-6 / R;
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

  if (raw_uS >= 1e6) {
    my_string = String(raw_uS / 1e9, 2) + "MS ";
  }
  else if (raw_uS >= 1e4) {
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

unsigned long charge(const int pin, float voltage_target, unsigned long _time_hold) {
  static unsigned long time_charge_hold;
  //pinMode(PIN_DISCHARGE, INPUT); // Should already be set
  digitalWrite(PIN_FET, LOW);
  float _voltage = get_voltage();
#ifdef LOW_VOLTAGE
  if (DDRD & _BV(7) && digitalRead(pin)) {
#else
  if (DDRB & _BV(1) && digitalRead(pin)) {
#endif
    // Already charging
    if (_voltage >= voltage_target && !charge_hold_flag) {
      //Serial.print("V: "); Serial.print(get_voltage(),2); Serial.print(" tgt:"); Serial.println(voltage_target,2);
      // Finished charging
      //Serial.println("Finished charging");
      time_charge_hold = micros();
      charge_hold_flag = true;
    }
    else if (_voltage >= voltage_target && charge_hold_flag && (micros() - time_charge_hold) >= _time_hold) {
      charge_hold_flag = false;
      digitalWrite(pin, false);
#ifndef LOW_VOLTAGE
      pinMode(pin, INPUT);
#endif
      state = _charged;
    }
  }
  else {
    // Not already charging
    if (_voltage > V_DISCHARGE) {
      // Cannot charge yet as not fully discharged
      //Serial.println("Needs discharging");
      state = _discharge;
    }
    else {
      // Ready to start charging
      //Serial.println("Start charging");
      time_charge_start = micros();
      pinMode(pin, OUTPUT);
      digitalWrite(pin, true);
    }
  }
  return micros() - time_charge_start;
}

unsigned long charge(const int pin, float voltage_target) {
  //pinMode(PIN_DISCHARGE, INPUT); // Should already be set
  digitalWrite(PIN_FET, LOW);
  float _voltage = get_voltage();
#ifdef LOW_VOLTAGE
  if (DDRD & _BV(7) && digitalRead(pin)) {
#else
  if (DDRB & _BV(1) && digitalRead(pin)) {
#endif
    // Already charging
    if (_voltage >= voltage_target) {
      //Serial.print("V: "); Serial.print(get_voltage(),2); Serial.print(" tgt:"); Serial.println(voltage_target,2);
      // Finished charging
      //Serial.println("Finished charging");
      digitalWrite(pin, false);
#ifndef LOW_VOLTAGE
      pinMode(pin, INPUT);
#endif
      state = _charged;
    }
  }
  else {
    // Not already charging
    if (_voltage > V_DISCHARGE) {
      // Cannot charge yet as not fully discharged
      //Serial.println("Needs discharging");
      state = _discharge;
    }
    else {
      // Ready to start charging
      //Serial.println("Start charging");
      pinMode(pin, OUTPUT);
      digitalWrite(pin, true);
      time_charge_start = micros();
    }
  }
  return micros() - time_charge_start;
}


void discharge() {
  float _voltage = get_voltage();
  switch (state) {
    case _discharge:
    case _safe:
      //Serial.println((micros() - time_discharge_start));
      // Already discharging
      if (_voltage > V_DISCHARGE) {
        // Still discharging
        //Serial.println("Still discharging");
        pinMode(PIN_CHARGE, INPUT);
        digitalWrite(PIN_CHARGE_1V5, LOW);
        //pinMode(PIN_DISCHARGE, OUTPUT);
        //digitalWrite(PIN_DISCHARGE, false);
        digitalWrite(PIN_FET, HIGH);
        time_discharge_start = millis();
      }
      else if ((millis() - time_discharge_start) >= TIME_DISCHARGE) {
        // Finished discharging
        //Serial.println("Finished discharging");
        //pinMode(PIN_DISCHARGE, INPUT);
        digitalWrite(PIN_FET, LOW);
        state = _safe;
      }
      break;
    default:
      // Not already discharging
      //Serial.println("Not discharging");
      pinMode(PIN_CHARGE, INPUT);
      digitalWrite(PIN_CHARGE_1V5, LOW);
      //pinMode(PIN_DISCHARGE, OUTPUT);
      //digitalWrite(PIN_DISCHARGE, false);
      digitalWrite(PIN_FET, HIGH);
      state = _discharge;
      break;
  }
}

void discharge(unsigned long discharge_time) {
  static bool _flag;
  //  if (DDRB & _BV(0)) {
  if (PORTD & _BV(6)) {
    // Already discharging
    //if ((millis() - time_discharge_start) >= discharge_time) {
    if (_flag && (millis() - time_discharge_start) >= discharge_time) {
      // Finished discharging
      //pinMode(PIN_DISCHARGE, INPUT);
      digitalWrite(PIN_FET, LOW);
      state = _done;
      digitalWrite(LED_BUILTIN, true);
      lcd_update_lhs(lcd, String(millis() - time_discharge_start) + "mS", 1, 8);
      _flag = false;
    }
    else if (get_voltage() <= 0.00 && !_flag) {
      time_discharge_start = millis();
      _flag = true;
    }
  }
  else {
    // Not already discharging
    pinMode(PIN_CHARGE, INPUT);
    digitalWrite(PIN_CHARGE_1V5, LOW);
    //pinMode(PIN_DISCHARGE, OUTPUT);
    //digitalWrite(PIN_DISCHARGE, false);
    digitalWrite(PIN_FET, HIGH);
    digitalWrite(LED_BUILTIN, false);
    _flag = false;
  }
}

/* LCD Methods */
int led_keypad_run(DFR_Key _keypad) {
  int key = _keypad.getKey();
  static bool __being_pressed;

  if (key != SAMPLE_WAIT) {
    switch (key) {
      case RIGHT_KEY: // Right
        if (!__being_pressed)  {
          //Capacitance_Display::change_menu(1);
          __being_pressed = true;
          if (menu == _menu_mode) {
            mode_change_flag = true;
            if (mode == _capacitance) mode = _rebound;
            else if (mode == _rebound) mode = _make_safe;
            else if (mode == _make_safe) mode = _capacitance;
          }
          else if (menu = _menu_high) {
            ;
          }
          else if (menu = _menu_mode) {
            ;
          }
        }
        break;
      case DOWN_KEY: // Down
        if (!__being_pressed)  {
          //Capacitance_Display::change_menu(1);
          __being_pressed = true;
          if (menu == _menu_mode) menu = _menu_high;
          else if (menu == _menu_high) menu = _menu_low;
          else if (menu = _menu_low) menu = _menu_mode;
        }
        break;
      case UP_KEY: // Up
        if (!__being_pressed)  {
          //Capacitance_Display::change_menu(-1);
          __being_pressed = true;
          if (menu == _menu_mode) menu = _menu_low;
          else if (menu == _menu_high) menu = _menu_mode;
          else if (menu == _menu_low) menu = _menu_high;
        }
        break;
      case LEFT_KEY: // Left
        if (!__being_pressed)  {
          //Capacitance_Display::change_menu(1);
          __being_pressed = true;
          if (menu == _menu_mode) {
            mode_change_flag = true;
            if (mode == _capacitance) mode = _make_safe;
            else if (mode == _rebound) mode = _capacitance;
            else if (mode == _make_safe) mode = _rebound;
          }
          else if (menu == _menu_high) {
            time_charge_hold = time_charge_hold + 0.1e6;
          }
          else if (menu == _menu_low) {
            time_discharge_hold = time_discharge_hold + 0.1e6;
          }
        }
        break;
      case SELECT_KEY: // Select
        if (!__being_pressed)  {
          __being_pressed = true;

          if (menu == _menu_mode) {
            discharge();
          }
          else if (menu == _menu_high) {
            time_charge_hold = time_charge_hold - 0.1e6;
          }
          else if (menu == _menu_low) {
            time_discharge_hold = time_discharge_hold - 0.1e6;
          }
        }
        break;
      case NO_KEY: // Nothing pressed
        __being_pressed = false;
        break;
    }
  }

  lcd.setCursor(9, 0);
  if (__being_pressed) {
    lcd.print("-");
  }
  else {
    switch (menu) {
      case _menu_mode:
        lcd.print("1");
        break;
      case _menu_high:
        lcd.print("2");
        break;
      case _menu_low:
        lcd.print("3");
        break;
    }
  }

  if (key != SAMPLE_WAIT && key != NO_KEY) return key; // Something pressed
  else return -1;
}

