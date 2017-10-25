#ifndef GPIO
#define GPIO

#include <Arduino.h>
#include <Wire.h>



/*
  led_safe       13
  led_danger     14
  sw_safe        15
  sw_5v_3v3      16
  sw_no_fet      17

  int_5v         0,1,2,3

  fet_dis        4

  fet_5v         11
  ohm150         6
  ohm68          5
  fet_3v3        12
  ohm100         10
  ohm68          7
*/

class Gpio {
  public:
    byte addr;
    Gpio(byte addr);
    void begin(unsigned int dir);

    static inline unsigned int read(const byte addr);
    static inline unsigned int write(const byte addr, const unsigned int data);

    void set_bit(const int this_bit, const bool value);
    void set_multiple_bits(const int* this_bit, const bool* value, const int num_bits);
    bool get_bit(int this_bit);

    unsigned int get_bitmask(void);
  private:
    unsigned int bitmask;
};


#endif
