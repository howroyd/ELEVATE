#include "gpio.h"

Gpio::Gpio(byte addr) {
  Gpio::addr = addr;
}
void Gpio::begin(unsigned int dir) {
  Gpio::bitmask = dir;
  Wire.begin();
  Wire.beginTransmission(Gpio::addr);
  Wire.write(byte(Gpio::bitmask));  // outputs high for input
  Wire.write(byte(Gpio::bitmask >> 8)); // outputs high for input
  Wire.endTransmission();
}

unsigned int Gpio::get_bitmask(void) {
  return Gpio::bitmask;
}

unsigned int Gpio::read(const byte addr) {
  Wire.requestFrom(addr, 4);
  int available = Wire.available();
  if (available) {
    unsigned int val1 = (unsigned int)(Wire.read());
    unsigned int val2 = (unsigned int)(Wire.read());
    unsigned int val = val1 | (val2 << 8);
    return val;
  }
  else {
    return 0;
    Serial.println("No data!");
  }
}

unsigned int Gpio::write(const byte addr, const unsigned int data) {
  Wire.beginTransmission(addr);
  Wire.write(byte(data));
  Wire.write(byte(data >> 8));
  Wire.endTransmission();
}

bool Gpio::get_bit(int this_bit) {
  unsigned int val = Gpio::read(Gpio::addr);
  //Serial.println(val,BIN);
  if (val == -1) {
    return val;
  }
  else {
    if (this_bit > 7) this_bit -= 2;
    return bitRead(val, this_bit);
  }
}

void Gpio::set_bit(const int this_bit, const bool value) {
  int corrected_bit = this_bit >= 10 ? this_bit - 2 : this_bit;
  bitWrite(Gpio::bitmask, corrected_bit, value);
  Gpio::write(Gpio::addr, Gpio::bitmask);
}

void Gpio::set_multiple_bits(const int* this_bit, const bool* value, const int num_bits) {
  for (int x = 0 ; x < num_bits ; x++) {
    int corrected_bit = this_bit[x] >= 10 ? this_bit[x] - 2 : this_bit[x];
    bitWrite(Gpio::bitmask, corrected_bit, value[x]);
  }

  Gpio::write(Gpio::addr, Gpio::bitmask);
}
