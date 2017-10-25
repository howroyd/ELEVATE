#include "Cap_Display.h"

void Capacitance_Display::clearLine(int line) {
  LiquidCrystal::setCursor(0, line);
  LiquidCrystal::print("                ");
  LiquidCrystal::home();
}

int Capacitance_Display::run(void) {
  int key = Capacitance_Display::keypad->getKey();

  if (key != SAMPLE_WAIT) {
    switch (key) {
      case RIGHT_KEY: // Right
        Capacitance_Display::change_menu(1);
        break;
      case DOWN_KEY: // Down
        break;
      case UP_KEY: // Up
        break;
      case LEFT_KEY: // Left
        Capacitance_Display::change_menu(-1);
        break;
      case SELECT_KEY: // Select
        return menu_select;
        break;
      case NO_KEY: // Nothing pressed
        break;
    }
  }

  if (Capacitance_Display::menu_select_new) {
    Capacitance_Display::clearLine(0);
    LiquidCrystal::print(Capacitance_Display::menu[Capacitance_Display::menu_select]);
    Capacitance_Display::menu_select_new = false;
  }

  return -1;
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
  Capacitance_Display::menu_select = constrain(Capacitance_Display::menu_select, 0, 1);
  Serial.println(Capacitance_Display::menu_select);
  if (Capacitance_Display::menu_select != old) Capacitance_Display::menu_select_new = true;
}

const char* Capacitance_Display::menu[] = {"MAKE SAFE", "BEGIN NOW"};

Capacitance_Display::~Capacitance_Display() {
  delete Capacitance_Display::keypad;
}


