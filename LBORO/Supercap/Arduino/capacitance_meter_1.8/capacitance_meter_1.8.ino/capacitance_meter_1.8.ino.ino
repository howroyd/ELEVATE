#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <DFR_Key.h>

/* VERSION */
#define VERSION 1.8
//#define BETA

/* MODES */
#define LOW_VOLTAGE
#define FILTERS_ON

/* CAPACITOR */
/* ONY DEFINE ONE!!! */
//#define NEC_10mF
//#define NEC_47mF
//#define CDE_47mF
//#define ELNA_47mF
#define PAN_470mF

/* CAPACITOR TYPES */
#ifdef NEC_10mF
#define VOLTAGE_CHARGE      4.9  // V
#define VOLTAGE_CHARGE_1V5  1.0  // V
#define TIME_CHARGE_HOLD    2000 // mS
#define TIME_DISCHARGE_HOLD 8000 // mS
#else
#ifdef NEC_47mF
#define VOLTAGE_CHARGE      4.9  // V
#define VOLTAGE_CHARGE_1V5  1.0  // V
#define TIME_CHARGE_HOLD    2000 // mS
#define TIME_DISCHARGE_HOLD 8000 // mS
#else
#ifdef CDE_47mF
#define VOLTAGE_CHARGE      4.9  // V
#define VOLTAGE_CHARGE_1V5  1.0  // V
#define TIME_CHARGE_HOLD    2000 // mS
#define TIME_DISCHARGE_HOLD 10000 // mS
#else
#ifdef ELNA_47mF
#define VOLTAGE_CHARGE      4.9  // V
#define VOLTAGE_CHARGE_1V5  1.0  // V
#define TIME_CHARGE_HOLD    2000 // mS
#define TIME_DISCHARGE_HOLD 8000 // mS
#else
#ifdef PAN_470mF
#define VOLTAGE_CHARGE      4.9  // V
#define VOLTAGE_CHARGE_1V5  0.1  // V
#define TIME_CHARGE_HOLD    2000 // mS
#define TIME_DISCHARGE_HOLD 2000 // mS
#endif
#endif
#endif
#endif
#endif

/* TIMERS */
#define TIME_DISCHARGE      5000 // mS at 0V to class as discharged
#define TIME_MENU_CHANGE    3000 // ms

/* VOLTAGES */
#define V_DISCHARGE         0.03 // Voltage to class as fully discharged

/* DATA RATES */
#define DATA_RATE_HZ        10   // Hz
#define SCREEN_REFRESH_RATE 24   // Hz

/* CHARGE RESISTOR VALUES */
#define RESISTOR_VAL        1182.0   // change this to whatever resistor value you are using
#define RESISTOR_VAL_LOW    1300.0   // change this to whatever resistor value you are using

/* HARDWARE PIN CONNECTIONS */
#define PIN_LED_DGR         A7
#define PIN_LED_SAFE        A6
#define PIN_ANALOG          A0
#define PIN_CHARGE          9
#define PIN_CHARGE_1V5      7
#define PIN_DISCHARGE       8
#define PIN_FET             6
#define KEYPAD_PIN          A1

/* SOFTWARE DECLARATIONS */
// Classes
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DFR_Key keypad;
#define SCREEN_MODE_CHAR_LOC 8

// States
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
} mode;
enum Menu {
  _menu_mode,
  _menu_high,
  _menu_low
} menu = _menu_mode;

// Functions
unsigned long charge(const int pin, const float voltage_target);
unsigned long charge(const int pin, const float voltage_target, const unsigned long time_hold); void discharge();
void discharge(const unsigned long discharge_time);
void lcd_update(LiquidCrystal my_display, const String top, const String bottom);
String lcd_update_lhs(const String out_buf, const String in_buf, const int len);
String lcd_update_rhs(const String out_buf, const String in_buf, const int len);
String lcd_println(const String out_buf, const String in_buf);
String lcd_clearln();
int led_keypad_run(DFR_Key _keypad);
String time_to_farads(const unsigned long dt, const float R);
String time_to_string(const float raw_uS);
String get_state_string(State _state);

// Variables
unsigned long _timer_loop;
unsigned long _timer_screen;
unsigned long _timer_menu;
unsigned long dt;
String farads;
String screen_top = "                ";
String screen_bottom = "                ";
bool mode_change_flag  = true;
bool mode_change_flag2 = false;
String mode_string;
float _voltage;
float _voltage_last;
int _counter;


/* INITIAL SETUP CODE */
void setup() {
  // Setup pin modes
  pinMode(PIN_LED_DGR, OUTPUT);
  pinMode(PIN_LED_SAFE, OUTPUT);
  pinMode(PIN_ANALOG, INPUT);
  pinMode(PIN_CHARGE, INPUT);
  pinMode(PIN_CHARGE_1V5, OUTPUT);
  pinMode(PIN_DISCHARGE, INPUT);
  pinMode(PIN_FET, OUTPUT);
  pinMode(KEYPAD_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogReference(DEFAULT);

  // Setup pin states
  digitalWrite(PIN_LED_DGR, HIGH);
  digitalWrite(PIN_LED_SAFE, HIGH);
  digitalWrite(PIN_CHARGE_1V5, LOW);
  digitalWrite(PIN_FET, LOW);
  digitalWrite(LED_BUILTIN, false);

  // Setup LCD Screen
  keypad.setPin(KEYPAD_PIN);
  lcd.begin(16, 2);
  lcd.clear();
  String intro = "Capacitance " + String(VERSION, 1);
#ifdef BETA
  intro += "b";
#endif
  lcd_update(lcd, intro, String("  S.Howroyd 2016"));
  keypad.setRate(10);

  // Read last state
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

  delay(3000);

  // Start USB communication
  Serial.begin(115200);
  Serial.println();
  Serial.println(intro);
  Serial.println("Time /uS\tV\tV_filtered\tFilter Freq /Hz");
  Serial.println("Time /uS\tLoop Freq /Hz\tMode\tState\tVoltage Raw\tVoltage Filtered\tCharge Hold Time /mS\tDischarge Hold Time /mS\tCharge Voltage");
}


/* MAIN */
void loop() {
  _counter++;

  // Safety
  //if (state == _safe) set_led_safe(true);
  //else set_led_safe(false);

  // Read ADC
  _voltage = get_voltage();

  // Run keypad
  led_keypad_run(keypad);

  // State machine
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
          screen_bottom = lcd_update_lhs(screen_bottom, farads, farads.length());
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
          charge(PIN_CHARGE_1V5, VOLTAGE_CHARGE_1V5, TIME_CHARGE_HOLD) / 100;
#else
          charge(PIN_CHARGE, VOLTAGE_CHARGE, TIME_CHARGE_HOLD) / 100;
#endif
          break;
        case _charged:
          discharge(TIME_DISCHARGE_HOLD); // Back to start
          break;
        case _done:
          break;
      }
      break;
    case _make_safe:
      mode_string = "Mk safe";
      if (state == _safe) {
        screen_bottom = lcd_update_lhs(screen_bottom, "    SAFE", 9);
      }
      else {
        screen_bottom = lcd_update_lhs(screen_bottom, "NOT SAFE", 9);
      }

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
      break;
  }

  // Update if there is a mode change
  if (mode_change_flag) {
    if (mode_change_flag2 && (millis() - _timer_menu) >= TIME_MENU_CHANGE) {
      mode_change_flag = mode_change_flag2 = false;
    }
    else if (!mode_change_flag2) {
      _timer_menu = millis();
      mode_change_flag2 = true;
    }

    // Update LCD screen
    lcd.clear();
    screen_top = screen_bottom = lcd_clearln();
    screen_top = lcd_update_lhs(screen_top, mode_string, mode_string.length());

    // Update EEPROM
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

    // Put into discharge state for safety
    discharge();
  }

  // Update voltage on LCD screen
  String _voltageString = " " + String(_voltage*1000.0, 0) + "mV";
  screen_top = lcd_update_rhs(screen_top, _voltageString, _voltageString.length());

  // Update filters
#ifdef FILTERS_ON
  _voltage_last = _voltage_last + 0.005 * (_voltage - _voltage_last);
#else
  _voltage_last = 0.0;
#endif

  if ((millis() - _timer_screen) >= 1000 / SCREEN_REFRESH_RATE) {
    lcd_update(lcd, screen_top, screen_bottom);
    _timer_screen = millis();
  }

  // Print to Serial at set data rate
  if ((millis() - _timer_loop) >= 1000 / DATA_RATE_HZ) {
    Serial.println(String(micros()) + '\t' + String(_counter * DATA_RATE_HZ)
                   + '\t' + mode_string + '\t' + get_state_string(state)
                   + '\t' + String(_voltage, 4) + '\t' + String(_voltage_last, 4)
                   + '\t' + TIME_CHARGE_HOLD + '\t' + TIME_DISCHARGE_HOLD
#ifdef LOW_VOLTAGE
                   + '\t' + VOLTAGE_CHARGE_1V5);
#else
                   + '\t' + VOLTAGE_CHARGE);
#endif
    _timer_loop = millis();
    _counter = 0;
  }
}

String get_state_string(State _state) {
  switch (_state) {
    case _charge:
      return "Charge";
    case _charged:
      return "Charged";
    case _discharge:
      return "Discharge";
    case _safe:
      return "Safe";
    case _done:
      return "Done";
    default:
      return "State?";
  } state = _discharge;
}

void set_led_safe(const bool safe) {
  if (safe) {
    digitalWrite(PIN_LED_DGR, LOW);
    digitalWrite(PIN_LED_SAFE, HIGH);
    Serial.println("SAFE");
  }
  else {
    digitalWrite(PIN_LED_DGR, HIGH);
    digitalWrite(PIN_LED_SAFE, LOW);
    Serial.println("UNSAFE");
  }
}

float get_voltage() {
  static float val;
#ifdef LOW_VOLTAGE
  analogReference(EXTERNAL);
  for (int i = 0; i < 5; i++) analogRead(PIN_ANALOG); // Bin 5 readings while ADC settles
  val = (float)map(analogRead(PIN_ANALOG), 0, 1023, 0, 40000) / 10000.0;
  analogReference(DEFAULT);
  for (int i = 0; i < 5; i++) analogRead(PIN_ANALOG); // Bin 5 readings while ADC settles
#else
  val = (float)map(analogRead(PIN_ANALOG), 0, 1023, 0, 50000) / 10000.0;
#endif
  return val*1.107;
}

String time_to_farads(const unsigned long dt, const float R) {
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

String time_to_string(const float raw_uS) {
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

void lcd_update(LiquidCrystal my_display, const String top, const String bottom) {
  my_display.setCursor(0, 0);
  my_display.print(top);
  my_display.setCursor(0, 1);
  my_display.print(bottom);
}

String lcd_clearln() {
  return "                ";
}

String lcd_println(const String out_buf, const String in_buf) {
  return in_buf;
}

String lcd_update_lhs(const String out_buf, const String in_buf, const int len) {
  String buf = out_buf;
  buf.remove(0, len);
  buf = in_buf + buf;
  return buf;
}

String lcd_update_rhs(const String out_buf, const String in_buf, const int len) {
  String buf = out_buf;
  buf.remove(16 - len);
  buf = buf + in_buf;
  return buf;
}

unsigned long charge(const int pin, const float voltage_target, const unsigned long time_hold) {
  static unsigned long _time_charge_start;
  static unsigned long _time_charge_hold;
  static bool _charge_hold_flag = false;
  static float _voltage;

  digitalWrite(PIN_FET, LOW);
  _voltage = get_voltage();

#ifdef LOW_VOLTAGE
  if (DDRD & _BV(7) && digitalRead(pin)) {
#else
  if (DDRB & _BV(1) && digitalRead(pin)) {
#endif
    // Already charging
    if (_voltage >= voltage_target && !_charge_hold_flag) {
      // Finished charging
      _time_charge_hold = micros();
      _charge_hold_flag = true;
    }
    else if (_voltage >= voltage_target && _charge_hold_flag && (micros() - _time_charge_hold) >= time_hold) {
      _charge_hold_flag = false;
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
      state = _discharge;
    }
    else {
      // Ready to start charging
      _time_charge_start = micros();
      pinMode(pin, OUTPUT);
      digitalWrite(pin, true);
    }
  }
  return micros() - _time_charge_start;
}

unsigned long charge(const int pin, const float voltage_target) {
  static unsigned long _time_charge_start;
  static float _voltage;

  digitalWrite(PIN_FET, LOW);
  _voltage = get_voltage();

#ifdef LOW_VOLTAGE
  if (DDRD & _BV(7) && digitalRead(pin)) {
#else
  if (DDRB & _BV(1) && digitalRead(pin)) {
#endif
    // Already charging
    if (_voltage >= voltage_target) {
      // Finished charging
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
      state = _discharge;
    }
    else {
      // Ready to start charging
      pinMode(pin, OUTPUT);
      digitalWrite(pin, true);
      _time_charge_start = micros();
    }
  }
  return micros() - _time_charge_start;
}


void discharge() {
  static unsigned long _time_discharge_start;
  static float _voltage;

  _voltage = get_voltage();

  switch (state) {
    case _discharge:
    case _safe:
      // Already discharging
      if (_voltage > V_DISCHARGE) {
        // Still discharging
        pinMode(PIN_CHARGE, INPUT);
        digitalWrite(PIN_CHARGE_1V5, LOW);
        digitalWrite(PIN_FET, HIGH);
        _time_discharge_start = millis();
      }
      else if ((millis() - _time_discharge_start) >= TIME_DISCHARGE) {
        // Finished discharging
        //pinMode(PIN_DISCHARGE, INPUT);
        digitalWrite(PIN_FET, LOW);
        state = _safe;
      }
      break;
    default:
      // Not already discharging
      pinMode(PIN_CHARGE, INPUT);
      digitalWrite(PIN_CHARGE_1V5, LOW);
      digitalWrite(PIN_FET, HIGH);
      state = _discharge;
      break;
  }
}

void discharge(const unsigned long discharge_time) {
  static bool _flag = false;
  static unsigned long _time_discharge_start;
  static float _voltage;

  _voltage = get_voltage();

  if (PORTD & _BV(6)) {
    // Already discharging
    if (_flag && ((millis() - _time_discharge_start) >= discharge_time)) {
      // Finished discharging
      digitalWrite(PIN_FET, LOW);
      state = _done;
      digitalWrite(LED_BUILTIN, true);
      String _string_discharge = String(millis() - _time_discharge_start);
      lcd_update_lhs(screen_bottom, _string_discharge, _string_discharge.length());
      _flag = false;
    }
    else if (_voltage <= 0.00 && !_flag) {
      _time_discharge_start = millis();
      _flag = true;
    }
  }
  else {
    // Not already discharging
    pinMode(PIN_CHARGE, INPUT);
    digitalWrite(PIN_CHARGE_1V5, LOW);
    digitalWrite(PIN_FET, HIGH);
    digitalWrite(LED_BUILTIN, false);
    _flag = false;
  }
}

/* LCD Methods */
int led_keypad_run(DFR_Key _keypad) {
  int key = _keypad.getKey();
  static bool __being_pressed = false;

  if (key != SAMPLE_WAIT) {
    switch (key) {
      case RIGHT_KEY: // Right
        if (!__being_pressed)  {
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
          __being_pressed = true;
          if (menu == _menu_mode) menu = _menu_high;
          else if (menu == _menu_high) menu = _menu_low;
          else if (menu = _menu_low) menu = _menu_mode;
        }
        break;
      case UP_KEY: // Up
        if (!__being_pressed)  {
          __being_pressed = true;
          if (menu == _menu_mode) menu = _menu_low;
          else if (menu == _menu_high) menu = _menu_mode;
          else if (menu == _menu_low) menu = _menu_high;
        }
        break;
      case LEFT_KEY: // Left
        if (!__being_pressed)  {
          __being_pressed = true;
          if (menu == _menu_mode) {
            mode_change_flag = true;
            if (mode == _capacitance) mode = _make_safe;
            else if (mode == _rebound) mode = _capacitance;
            else if (mode == _make_safe) mode = _rebound;
          }
          //else if (menu == _menu_high) {
          //  time_charge_hold = time_charge_hold + 0.1e6;
          //}
          //else if (menu == _menu_low) {
          //  time_discharge_hold = time_discharge_hold + 0.1e6;
          //}
        }
        break;
      case SELECT_KEY: // Select
        if (!__being_pressed)  {
          __being_pressed = true;

          if (menu == _menu_mode) {
            discharge();
          }
          //else if (menu == _menu_high) {
          //  TIME_CHARGE_HOLD = time_charge_hold - 0.1e6;
          //}
          //else if (menu == _menu_low) {
          //  time_discharge_hold = time_discharge_hold - 0.1e6;
          //}
        }
        break;
      case NO_KEY: // Nothing pressed
        __being_pressed = false;
        break;
    }
  }

  if (__being_pressed) {
    screen_top.setCharAt(SCREEN_MODE_CHAR_LOC, '-');
  }
  else {
    switch (menu) {
      case _menu_mode:
        screen_top.setCharAt(SCREEN_MODE_CHAR_LOC, '1');
        break;
      case _menu_high:
        screen_top.setCharAt(SCREEN_MODE_CHAR_LOC, '2');
        break;
      case _menu_low:
        screen_top.setCharAt(SCREEN_MODE_CHAR_LOC, '3');
        break;
    }
  }

  if (key != SAMPLE_WAIT && key != NO_KEY) return key; // Something pressed
  else return -1;
}

