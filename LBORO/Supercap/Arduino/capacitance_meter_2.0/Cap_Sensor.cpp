#include "Cap_Sensor.h"

/*
   CONSTRUCTORS
 */
Capacitance_Sensor::Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t charge_pin, float r_val) {
  Capacitance_Sensor::pin_sense = sense_pin;
  Capacitance_Sensor::pin_discharge = discharge_pin;
  Capacitance_Sensor::pin_charge = (uint8_t*)malloc(1 * sizeof(uint8_t));
  memcpy(Capacitance_Sensor::pin_charge, &charge_pin, 1 * sizeof(uint8_t));
  Capacitance_Sensor::r_val = (float*)malloc(1 * sizeof(float));
  memcpy(Capacitance_Sensor::r_val, &r_val, 1 * sizeof(float));
  Capacitance_Sensor::total_resistors = 1;
  Capacitance_Sensor::total_charge_pins = 1;
  Capacitance_Sensor::total_discharge_pins = 1;
  Capacitance_Sensor::state = 2;
  Capacitance_Sensor::MCP = new MCP3424(I2C_MCP3424_ADDR);
}
Capacitance_Sensor::Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t* charge_pin, float r_val, int num_charge_pins) {
  Capacitance_Sensor::pin_sense = sense_pin;
  Capacitance_Sensor::pin_discharge = discharge_pin;
  Capacitance_Sensor::pin_charge = (uint8_t*)malloc(num_charge_pins * sizeof(uint8_t));
  memcpy(Capacitance_Sensor::pin_charge, charge_pin, num_charge_pins * sizeof(uint8_t));
  Capacitance_Sensor::r_val = (float*)malloc(1 * sizeof(float));
  memcpy(Capacitance_Sensor::r_val, &r_val, 1 * sizeof(float));
  Capacitance_Sensor::total_resistors = 1;
  Capacitance_Sensor::total_charge_pins = num_charge_pins;
  Capacitance_Sensor::total_discharge_pins = 1;
  Capacitance_Sensor::state = 2;
  Capacitance_Sensor::MCP = new MCP3424(I2C_MCP3424_ADDR);
}
Capacitance_Sensor::Capacitance_Sensor(const uint8_t sense_pin, const uint8_t discharge_pin, const uint8_t* charge_pin, float* r_val, int num_charge_pins) {
  Capacitance_Sensor::pin_sense = sense_pin;
  Capacitance_Sensor::pin_discharge = discharge_pin;
  Capacitance_Sensor::pin_charge = (uint8_t*)malloc(num_charge_pins * sizeof(uint8_t));
  memcpy(Capacitance_Sensor::pin_charge, charge_pin, num_charge_pins * sizeof(uint8_t));
  Capacitance_Sensor::r_val = (float*)malloc(num_charge_pins * sizeof(float));
  memcpy(Capacitance_Sensor::r_val, r_val, num_charge_pins * sizeof(float));
  Capacitance_Sensor::total_resistors = num_charge_pins;
  Capacitance_Sensor::total_charge_pins = num_charge_pins;
  Capacitance_Sensor::total_discharge_pins = 1;
  Capacitance_Sensor::state = 2;
  Capacitance_Sensor::MCP = new MCP3424(I2C_MCP3424_ADDR);
}

Capacitance_Sensor::~Capacitance_Sensor() {
  delete Capacitance_Sensor::MCP;
}


/*
   MAIN RUN METHOD
 */
void Capacitance_Sensor::run(bool running) {
  // State machine
  switch (Capacitance_Sensor::state) {
  case 3: // Charging
    Capacitance_Sensor::charge();
    if (!running) Capacitance_Sensor::change_state(2);
    break;
  case 2: // Discharging
    Capacitance_Sensor::discharge();
    break;
  case 1: // Safe
    if (running) {
      Capacitance_Sensor::change_state(3);
    }
    else {
      Capacitance_Sensor::raw = analogRead(Capacitance_Sensor::pin_sense);
      if (Capacitance_Sensor::raw > SAFE_RAW_VOLTAGE) Capacitance_Sensor::change_state(2);
    }
    break;
  }
}


/*
   CHARGE ROUTINE
 */
void Capacitance_Sensor::charge(void) {
  // Start charging if not already
  if (!Capacitance_Sensor::charging) {
    if (Capacitance_Sensor::total_resistors > 1) {
      for (int i = 0; i < Capacitance_Sensor::total_charge_pins; i++) {
        if (i == Capacitance_Sensor::selector) {
          pinMode(Capacitance_Sensor::pin_charge[Capacitance_Sensor::selector], OUTPUT);
          digitalWrite(Capacitance_Sensor::pin_charge[Capacitance_Sensor::selector], HIGH);
        }
        else pinMode(Capacitance_Sensor::pin_charge[i], INPUT);
      }
    }
    else {
      for (int i = 0; i < Capacitance_Sensor::total_charge_pins; i++) {
        pinMode(Capacitance_Sensor::pin_charge[i], OUTPUT);
        digitalWrite(Capacitance_Sensor::pin_charge[i], HIGH);
      }
    }
    Capacitance_Sensor::time_start = micros();
    Capacitance_Sensor::charging = true;
  }

  // Read in capacitor voltage & calculate charge time so far
  Capacitance_Sensor::raw = analogRead(Capacitance_Sensor::pin_sense);
  float time_charge = (float)(micros() - Capacitance_Sensor::time_start) * 1e-6; // Seconds

  // What happens if not charged yet
  if (Capacitance_Sensor::raw < 648) {  // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    // Restart at lower resistance if taking too long
    if (time_charge > 3.0 && Capacitance_Sensor::selector > 0 && Capacitance_Sensor::total_resistors > 1) {
      Capacitance_Sensor::stop_all();
      Capacitance_Sensor::selector--;
      Capacitance_Sensor::fail_count++;
    }
  }
  // What happens if charged
  else {
    // Restart at higher resistance if too fast
    if (time_charge < 1.0 && Capacitance_Sensor::selector < (Capacitance_Sensor::total_charge_pins - 1) && Capacitance_Sensor::fail_count < 2 && Capacitance_Sensor::total_resistors > 1) {
      Capacitance_Sensor::selector++;
      Capacitance_Sensor::fail_count++;
      Capacitance_Sensor::stop_all();
    }
    // Measurement successful
    else {
      Capacitance_Sensor::stop_all();
      Capacitance_Sensor::farads = time_charge / (Capacitance_Sensor::r_val[Capacitance_Sensor::selector]);
      Capacitance_Sensor::farads = Capacitance_Sensor::farads > 1300e-9 ? Capacitance_Sensor::farads : 0.0;
      Capacitance_Sensor::v_max =  (float)Capacitance_Sensor::raw / 1023.0 * 5.0;
      Capacitance_Sensor::new_data = true;
      Capacitance_Sensor::delta = time_charge;
      Capacitance_Sensor::fail_count = 0;
      Capacitance_Sensor::change_state(2);
    }
  }
}

/*
   DISCHARGE ROUTINE
 */
void Capacitance_Sensor::discharge(void) {
  Capacitance_Sensor::raw = analogRead(Capacitance_Sensor::pin_sense);
  if (Capacitance_Sensor::raw > DISCHARGE_RAW_VOLTAGE) {
    digitalWrite(Capacitance_Sensor::pin_discharge, HIGH);
  }
  else {
    Capacitance_Sensor::change_state(1);
  }
}

/*
   CHANGE STATE INTERNAL METHOD
 */
bool Capacitance_Sensor::change_state(int state) {
  switch (state) {
  case 3:
    if (Capacitance_Sensor::state != 3) {
      Capacitance_Sensor::state = 3;
      Capacitance_Sensor::new_state = true;
    }
    return true;
    break;
  case 2:
    if (Capacitance_Sensor::state != 2) {
      Capacitance_Sensor::state = 2;
      Capacitance_Sensor::new_state = true;
    }
    return true;
    break;
  case 1:
    if (Capacitance_Sensor::state != 1) {
      delay(100); // Wait for rebound TODO
      if (analogRead(Capacitance_Sensor::pin_sense) <= DISCHARGE_RAW_VOLTAGE) {
        Capacitance_Sensor::stop_all();
        Capacitance_Sensor::state = 1;
        Capacitance_Sensor::new_state = true;
      }
      else {
        Capacitance_Sensor::state = 2;
        return false;
      }
    }
    return true;
    break;
  }
}

/*
   STOP ALL ROUTINE
 */
void Capacitance_Sensor::stop_all(void) {
  Capacitance_Sensor::charging = false;
  Capacitance_Sensor::change_state(2);

  // Reset all charge pins
  for (int i = 0; i < Capacitance_Sensor::total_charge_pins; i++) {
    pinMode(Capacitance_Sensor::pin_charge[i], INPUT);
  }
  // Reset all discharge pins
  digitalWrite(Capacitance_Sensor::pin_discharge, LOW);
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
  case 3: // Charging
    Capacitance_Sensor::state_string = " CHG";
    break;
  case 2: // Discharging
    Capacitance_Sensor::state_string = " DIS";
    break;
  case 1: // Safe
    Capacitance_Sensor::state_string = "SAFE";
    break;
  }
  return Capacitance_Sensor::state_string;
}

/* Get Current */
float* Capacitance_Sensor::get_current(void) {
  for(int i=1;i<=4;i++){
    // MCP3424 is configured to channel i with 18 bits resolution, continous mode and gain defined to 8 
    Capacitance_Sensor::MCP->Configuration(i,16,1,8); 
    // Measure is stocked in array Voltage, note that the library will wait for a completed conversion that takes around 200 ms@18bits
    Capacitance_Sensor::current[i-1] = Capacitance_Sensor::MCP->Measure(); 
  }
  return Capacitance_Sensor::current;
}


