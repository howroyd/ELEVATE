#include "Cap_Display.h"


void Capacitance_Display::clearLine(int line) {
  LiquidCrystal::setCursor(0, line);
  LiquidCrystal::print("                ");
  LiquidCrystal::home();
}

void Capacitance_Display::begin(void) {
  LiquidCrystal::begin(16, 2);
  Capacitance_Display::init_keypad();
  LiquidCrystal::clear();
  LiquidCrystal::setCursor(0, 0);
}
void Capacitance_Display::begin(int pin_keypad) {
  LiquidCrystal::begin(16, 2);
  Capacitance_Display::init_keypad(pin_keypad);
  LiquidCrystal::clear();
  LiquidCrystal::setCursor(0, 0);
}

int Capacitance_Display::run(void) {
  int key = Capacitance_Display::keypad->getKey();
  static bool __being_pressed;
  if (key != SAMPLE_WAIT) {
    switch (key) {
      case RIGHT_KEY: // Right
        if (!__being_pressed) break;
        break;
      case DOWN_KEY: // Down
        if (!__being_pressed)  {
          Capacitance_Display::change_menu(1);
          __being_pressed = true;
        }
        break;
      case UP_KEY: // Up
        if (!__being_pressed)  {
          Capacitance_Display::change_menu(-1);
          __being_pressed = true;
        }
        break;
      case LEFT_KEY: // Left
        if (!__being_pressed) break;
        break;
      case SELECT_KEY: // Select
        if (!__being_pressed) break;
        break;
      case NO_KEY: // Nothing pressed
        __being_pressed = false;
        break;
    }
  }

  if (key != SAMPLE_WAIT && key != NO_KEY) return key; // Something pressed
  else return -1;
}

void Capacitance_Display::init_keypad(uint8_t pin) {
  Capacitance_Display::keypad = new DFR_Key();
  Capacitance_Display::keypad->setPin(pin);
}

void Capacitance_Display::init_keypad() {
  Capacitance_Display::keypad = new DFR_Key();
}

void Capacitance_Display::change_menu(int dir) {
  int old = Capacitance_Display::menu_select;
  if (dir > 0) Capacitance_Display::menu_select++;
  else if (dir < 0) Capacitance_Display::menu_select--;
  Capacitance_Display::menu_select = constrain(Capacitance_Display::menu_select, 0, Capacitance_Display::num_menu_items - 1);
  Capacitance_Display::clearLine(0);
  LiquidCrystal::setCursor(0, 0);
  LiquidCrystal::print(Capacitance_Display::menu[Capacitance_Display::menu_select]);
  if (Capacitance_Display::menu_select != old) Capacitance_Display::menu_select_new = true;
}

const char* Capacitance_Display::menu[] = {"MAKE SAFE", "BEGIN NOW", "RESET"};
const int Capacitance_Display::num_menu_items = 3;

Capacitance_Display::~Capacitance_Display() {
  delete Capacitance_Display::keypad;
}

void Capacitance_Display::reset(void) {
  asm volatile ("  jmp 0"); // SOFTWARE RESET!
}
