#ifndef CAP_SENSOR
#define CAP_SENSOR

#include <Arduino.h>
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

#define PIN_ANALOG        A0

#define MINIMUM_F         1300e-9

#define REBOUND_DELAY_MS  10

#define SAFE_RAW_VOLTAGE 100
#define DISCHARGE_RAW_VOLTAGE 10

const int GPIO_INTERNAL_5V[4] = {0, 1, 2, 3};

class Capacitance_Sensor : protected Gpio {
  public:
    Capacitance_Sensor(byte addr) : Gpio(addr) {};
    bool   begin(void);
    bool   run(bool running); // Returns true if in operation, false if safe && stopped
    void   stop_all(void);
    float  get_capacitance(void);
    float  get_discharge(void);
    String get_state(void);
    int    get_raw(void);
    bool   new_data;
    bool   new_state;
    void   set_supply(String input);
    void   set_resistor(String input);
  protected:
    void   _charge(void);
    void   _discharge(void);
    void   _trigger_charge_fet(bool state);
    void   _trigger_discharge_fet(bool state);
    String state_string;

    bool   _change_state(int state);
  private:
    bool   _check_switches(void);
    String __charge_resistor;
    int    __charge_supply;
    float  __farads;
    float  __discharge;
    int    __state;
    int    __raw;
    unsigned long   __time_start; // microseconds (overflow at 70mins)
    unsigned long   __time_start_discharge; // microseconds (overflow at 70mins)
    int    __selector;
    bool   __charging;
    bool   __discharging;
    int    __fail_count;
};

#endif

