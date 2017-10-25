#ifndef CAP_DISPLAY
#define CAP_DISPLAY

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DFR_Key.h>

class Capacitance_Display : public LiquidCrystal {
  public:
    Capacitance_Display(int RS, int EN, int D4, int D5, int D6, int D7) : LiquidCrystal(RS, EN, D4, D5, D6, D7) {};
    ~Capacitance_Display();
    void begin(void);
    void begin(int pin_keypad);
    void clearLine(int line);
    int run(void);
    static const char* menu[];
    static const int num_menu_items;
    void change_menu(int dir);
    void init_keypad(uint8_t pin);
    void init_keypad();
  private:
    int menu_select;
    bool menu_select_new;
    DFR_Key* keypad;
    void reset(void);
};

#endif
