#ifndef CAP_SENSOR
#define CAP_SENSOR

#include <Arduino.h>
#include <MCP3424.h>
#include <Wire.h>

#define SAFE_RAW_VOLTAGE 100
#define DISCHARGE_RAW_VOLTAGE 10

#define I2C_MCP3424_ADDR 0x68

class Capacitance_Sensor {
public:
  Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t charge_pin, float r_val);
  Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t* charge_pin, float r_val, int num_charge_pins);
  Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t* charge_pin, float* r_val, int num_charge_pins);
  ~Capacitance_Sensor();
  void   run(bool running);
  float  get_data(void);
  String get_state(void);
  int    get_raw(void);
  float* get_current(void);
  bool   new_data;
  bool   new_state;
  float  v_max;
  float  delta;
protected:
  void   charge(void);
  void   discharge(void);

  String state_string;
  void   stop_all(void);
  bool   change_state(int state);
private:
  uint8_t   pin_sense;
  uint8_t   pin_discharge;
  uint8_t*  pin_charge;
  float*    r_val;
  float     farads;
  int    state;
  int    raw;
  unsigned long   time_start; // microseconds (overflow at 70mins)
  int    selector;
  bool   charging;
  int    total_charge_pins;
  int    total_discharge_pins;
  int    total_resistors;
  int    fail_count;
  MCP3424* MCP;
  float  current[4];
};

#endif

