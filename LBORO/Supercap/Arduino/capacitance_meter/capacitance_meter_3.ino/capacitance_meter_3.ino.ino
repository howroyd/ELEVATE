#include <LiquidCrystal.h>
#include <DFR_Key.h>

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

const int   sense_pin     = A7;
const int   charge_pin[] = {
  A5, A4, A3
};
const int   discharge_pin = A6;
const float resistors[]  = {
  100.0
};

class Capacitance_Sensor {
  public:
    void   run(bool running);
    float  get_data(void);
    String get_state(void);
    int    get_raw(void);
    bool   new_data;
    bool   new_state;
    Capacitance_Sensor(void);
    int    set_sense_pin(const int pin);
    float  set_charge_voltage(const float voltage);
    int    set_discharge_pin(const int pin, int size);
    int*   set_discharge_pin(const int* pin, int size);
    int    set_charge_pin(const int pin, int size);
    int*   set_charge_pin(const int* pin, int size);
    float  set_charge_resistor(const float r, int size);
    float* set_charge_resistor(const float* r, int size);
    float  v_max;
    float delta;
  protected:
    void   charge(void);
    void   discharge(void);
    int    state;
    void   stop_all(void);
  private:
    int    pin_sense;
    int*   pin_discharge;
    int*   pin_charge;
    float* r_val;
    float  farads;

    int    raw;
    unsigned long   time_start; // microseconds (overflow at 70mins)
    int    selector;
    bool   charging;
    int    total_charge_pins;
    int    total_discharge_pins;
    int    fail_count;
};

Capacitance_Sensor   sensor;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitance V1.4");
  //keypad.setRate(10);

  Serial.begin(115200);
  sensor.set_sense_pin(sense_pin);
  sensor.set_discharge_pin(discharge_pin, sizeof(discharge_pin));
  sensor.set_charge_pin(charge_pin, sizeof(charge_pin));
  sensor.set_charge_resistor(resistors, sizeof(resistors));
  //analogReference(EXTERNAL);
  Serial.println("\n\nCapacitance Sensor 2016\n\n");
}

void loop() {
  sensor.run(true);
  String cout = "";
  if (sensor.new_state) cout += sensor.get_state() + '\t';
  if (sensor.new_data) {
    float data = sensor.get_data();
    lcd.setCursor(1, 0);
    if (data >= 1.0) {
      cout = cout + data + "F";
      lcd.print(String(data,1) + "F");
    }
    else if (data >= 1e-3) {
      cout = cout + data * 1e3 + "mF";
      lcd.print(String(data,1) + "mF");
    }
    else if (data >= 1e-6) {
      cout = cout + data * 1e6 + "uF";
      lcd.print(String(data,1) + (char)228);
    }
    else {
      cout = cout + data * 1e9 + "nF";
      lcd.print(String(data,1) + "nF");
    }
    cout += '\t';
    cout += sensor.v_max;
    cout += 'V';
    cout += '\t';
    cout += sensor.delta;
    cout += 's';
  }
  if (!cout.equals("")) Serial.println(cout);
}

/* Class Constructor */
Capacitance_Sensor::Capacitance_Sensor(void) {
  Capacitance_Sensor::state     = 0;
  Capacitance_Sensor::charging  = false;
  Capacitance_Sensor::selector  = 0;
  Capacitance_Sensor::new_data  = false;
  Capacitance_Sensor::new_state = false;
}

/* Get Capacitance */
float Capacitance_Sensor::get_data(void) {
  Capacitance_Sensor::new_data = false;
  return Capacitance_Sensor::farads;
}

/* Get State */
String Capacitance_Sensor::get_state(void) {
  Capacitance_Sensor::new_state = false;
  switch (Capacitance_Sensor::state) {
    case 3:
      return "Charging";
    case 2:
      return "Discharging";
    case 1:
      return "Safe";
    case 0:
      return "Unsafe";
  }
}

/* Get Raw ADC Value */
int Capacitance_Sensor::get_raw(void) {
  return Capacitance_Sensor::raw;
}

/* Main run run method */
void Capacitance_Sensor::run(bool running) {
  // State machine
  switch (Capacitance_Sensor::state) {
    case 3: // Charging
      Capacitance_Sensor::charge();
      break;
    case 2: // Discharging
      Capacitance_Sensor::discharge();
      break;
    case 1: // Safe
      if (running) {
        Capacitance_Sensor::state = 3;
        Capacitance_Sensor::new_state = true;
      }
      break;
    case 0: // Unsafe
      if (analogRead(Capacitance_Sensor::pin_sense) <= 2) {
        Capacitance_Sensor::state = 1;
        //Capacitance_Sensor::new_state = true;
      }
      else if (running) {
        Capacitance_Sensor::state = 2;
        //Capacitance_Sensor::new_state = true;
      }
      break;
  }
}

/* Charge Routine */
void Capacitance_Sensor::charge(void) {

  // Start charging if not already
  if (!Capacitance_Sensor::charging) {
    for (int i = 0; i < Capacitance_Sensor::total_charge_pins; i++) {
      pinMode(Capacitance_Sensor::pin_charge[i], OUTPUT);
      digitalWrite(Capacitance_Sensor::pin_charge[i], HIGH);
    }
    Capacitance_Sensor::time_start = micros();
    Capacitance_Sensor::charging = true;
  }

  // Read in capacitor voltage & calculate charge time so far
  Capacitance_Sensor::raw = analogRead(Capacitance_Sensor::pin_sense);
  float time_charge = (float)(micros() - Capacitance_Sensor::time_start) * 1e-6; // Seconds

  // What happens if not charged yet
  if (Capacitance_Sensor::raw < 648) {  // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    Serial.println(Capacitance_Sensor::raw);
    // Restart at lower resistance if taking too long
    if (time_charge > 3.0 && Capacitance_Sensor::selector > 0) {
      String out = "Restarting lower: ";
      out += Capacitance_Sensor::selector;
      out += " of ";
      out += Capacitance_Sensor::total_charge_pins;
      out += ". ";
      out += time_charge;
      out += "s";
      Serial.println(out);
      Capacitance_Sensor::stop_all();
      Capacitance_Sensor::selector--;
      Capacitance_Sensor::fail_count++;

    }
  }

  // What happens if charged
  else {

    // Restart at higher resistance if too fast
    if (time_charge < 1.0 && Capacitance_Sensor::selector < (Capacitance_Sensor::total_charge_pins - 1) && Capacitance_Sensor::fail_count < 2) {
      String out = "Restarting higher: ";
      out += Capacitance_Sensor::selector;
      out += " of ";
      out += Capacitance_Sensor::total_charge_pins;
      out += ". ";
      out += time_charge;
      out += "s";
      Serial.println(out);
      Capacitance_Sensor::selector++;
      Capacitance_Sensor::fail_count++;
      Capacitance_Sensor::stop_all();

    }

    // Measurement successful
    else {
      digitalWrite(Capacitance_Sensor::pin_charge[Capacitance_Sensor::selector], LOW);
      Capacitance_Sensor::farads = time_charge / (Capacitance_Sensor::r_val[0]);
      Capacitance_Sensor::v_max =  (float)Capacitance_Sensor::raw / 1023.0 * 5.0;
      Capacitance_Sensor::new_data = true;
      Capacitance_Sensor::delta = time_charge;
      Capacitance_Sensor::fail_count = 0;
      Capacitance_Sensor::stop_all();
    }
  }
}

/* Disharge Routine */
void Capacitance_Sensor::discharge(void) {
  Capacitance_Sensor::raw = analogRead(Capacitance_Sensor::pin_sense);
  if (Capacitance_Sensor::raw > 0) {
    for (int i = 0; i < Capacitance_Sensor::total_discharge_pins; i++) {
      digitalWrite(Capacitance_Sensor::pin_discharge[i], HIGH);
    }
  }
  else {
    Capacitance_Sensor::stop_all();
  }
}

/* Stop All Charging and Discharging */
void Capacitance_Sensor::stop_all(void) {
  Capacitance_Sensor::charging = false;
  Capacitance_Sensor::state = 0;
  //Capacitance_Sensor::new_state = true;

  // Reset all charge pins
  for (int i = 0; i < Capacitance_Sensor::total_charge_pins; i++) {
    pinMode(Capacitance_Sensor::pin_charge[i], INPUT);
  }

  // Reset all discharge pins
  for (int i = 0; i < Capacitance_Sensor::total_discharge_pins; i++) {
    digitalWrite(Capacitance_Sensor::pin_discharge[i], LOW);
  }
}

/* Set Sense Pin */
int Capacitance_Sensor::set_sense_pin(const int pin) {
  Capacitance_Sensor::pin_sense = pin;
  pinMode(Capacitance_Sensor::pin_sense, INPUT);
  return Capacitance_Sensor::pin_sense;
}

/* Set Discharge Pin or Pins */
int Capacitance_Sensor::set_discharge_pin(const int pin, int size) {
  Capacitance_Sensor::pin_discharge = (int*)malloc(size);
  Capacitance_Sensor::pin_discharge[0] = pin;
  Capacitance_Sensor::total_discharge_pins = size / sizeof(int);
  pinMode(Capacitance_Sensor::pin_discharge[0], OUTPUT);
  return Capacitance_Sensor::pin_discharge[0];
}
int* Capacitance_Sensor::set_discharge_pin(const int* pin, int size) {
  Capacitance_Sensor::pin_discharge = (int*)malloc(size);
  memcpy(Capacitance_Sensor::pin_discharge, pin, size);
  Capacitance_Sensor::total_discharge_pins = size / sizeof(int);
  for (int i = 0; i < Capacitance_Sensor::total_discharge_pins; i++) {
    pinMode(Capacitance_Sensor::pin_discharge[0], OUTPUT);
    digitalWrite(Capacitance_Sensor::pin_discharge[i], LOW);
  }
  return Capacitance_Sensor::pin_discharge;
}

/* Set Charge Pin or Pins */
int Capacitance_Sensor::set_charge_pin(const int pin, int size) {
  Capacitance_Sensor::pin_charge = (int*)malloc(size);
  Capacitance_Sensor::pin_charge[0] = pin;
  Capacitance_Sensor::total_charge_pins = size / sizeof(int);
  return Capacitance_Sensor::pin_charge[0];
}
int* Capacitance_Sensor::set_charge_pin(const int* pin, int size) {
  Capacitance_Sensor::pin_charge = (int*)malloc(size);
  memcpy(Capacitance_Sensor::pin_charge, pin, size);
  Capacitance_Sensor::total_charge_pins = size / sizeof(int);
  return Capacitance_Sensor::pin_charge;
}

/* Set Resistor Value or Values */
float Capacitance_Sensor::set_charge_resistor(const float r, int size) {
  Capacitance_Sensor::r_val = (float*)malloc(size);
  Capacitance_Sensor::r_val[0] = r;
  return Capacitance_Sensor::r_val[0];
}
float* Capacitance_Sensor::set_charge_resistor(const float* r, int size) {
  Capacitance_Sensor::r_val = (float*)malloc(size);
  memcpy(Capacitance_Sensor::r_val, r, size);
  return Capacitance_Sensor::r_val;
}

