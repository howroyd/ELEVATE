#include "Cap_Sensor.h"

/*
   CONSTRUCTORS
*/
bool Capacitance_Sensor::begin(void) {
  pinMode(PIN_ANALOG, INPUT);
  Gpio::begin(0b1110000000000000);
  Capacitance_Sensor::stop_all();
  Capacitance_Sensor::set_supply("INTERNAL");
  Capacitance_Sensor::set_resistor("INTERNAL");
  return true;
}


/*
   MAIN RUN METHOD
*/
bool Capacitance_Sensor::run(bool running) {
  //Serial.print(Gpio::get_bitmask(), BIN); Serial.print(' '); Serial.println(Capacitance_Sensor::get_state());
  if (!Capacitance_Sensor::_check_switches()) {
    if (Capacitance_Sensor::__state != 1) Capacitance_Sensor::_change_state(2);
    Serial.println("State override");
    running = false;
  }

  // State machine
  switch (Capacitance_Sensor::__state) {
    case 3: // Charging
      Gpio::set_bit(GPIO_LED_SAFE, false); Gpio::set_bit(GPIO_LED_DANGER, true);
      if (!running) Capacitance_Sensor::_change_state(2);
      Capacitance_Sensor::_charge();
      break;
    case 2: // Discharging
      Gpio::set_bit(GPIO_LED_SAFE, false); Gpio::set_bit(GPIO_LED_DANGER, true);
      Capacitance_Sensor::_discharge();
      break;
    case 1: // Safe
      if (running) Capacitance_Sensor::_change_state(3);
      else Gpio::set_bit(GPIO_LED_SAFE, true); Gpio::set_bit(GPIO_LED_DANGER, false);
      break;
    default:
      Serial.println("State error");
      running = false;
      break;
  }
  return running;
}

bool Capacitance_Sensor::_check_switches(void) {
  if (Gpio::get_bit(GPIO_SW_SAFE) == true) {
    //Serial.println("MAKE_SAFE");
    //Capacitance_Sensor::_discharge();//Capacitance_Sensor::stop_all();
    Capacitance_Sensor::__charging = false;
    return false;
  }
  else if (Gpio::get_bit(GPIO_SW_NO_FET) == true) {
    if (Capacitance_Sensor::__charge_supply != -1) {
      //Serial.println("NO_FET");
      //Capacitance_Sensor::stop_all();
      Capacitance_Sensor::set_supply("INTERNAL");
      Capacitance_Sensor::set_resistor("INTERNAL");
      Capacitance_Sensor::__charging = false;
    }
  }
  else if (Gpio::get_bit(GPIO_SW_5V_3V3) == true) {
    //Serial.println("5V");
    if (Capacitance_Sensor::__charge_supply != 5) {
      //Capacitance_Sensor::stop_all();
      Capacitance_Sensor::set_supply("5V");
      Capacitance_Sensor::set_resistor("150R");
      Capacitance_Sensor::__charging = false;
    }
  }
  else if (Capacitance_Sensor::__charge_supply != 3) {
    //Serial.println("3V3");
    //Capacitance_Sensor::stop_all();
    Capacitance_Sensor::set_supply("3V3");
    Capacitance_Sensor::set_resistor("100R");
    Capacitance_Sensor::__charging = false;
  }
  //else Serial.println("3V3");

  return true;
}

void Capacitance_Sensor::set_supply(String input) {
  input.toUpperCase();
  if (input.startsWith("INTERNAL") == 0 && Capacitance_Sensor::__charge_supply != -1) {
    Capacitance_Sensor::__charge_supply = -1;
    if (Capacitance_Sensor::__charge_resistor.startsWith("INTERNAL") != 0) {
      Capacitance_Sensor::set_resistor("INTERNAL");
    }
  }
  else if (input.startsWith("5V") == 0 && Capacitance_Sensor::__charge_supply != 5)  {
    Capacitance_Sensor::__charge_supply = 5;
    if (Capacitance_Sensor::__charge_resistor.startsWith("47R") != 0 || Capacitance_Sensor::__charge_resistor.startsWith("68R") != 0 || Capacitance_Sensor::__charge_resistor.compareTo("150R") != 0) {
      Capacitance_Sensor::set_resistor("150R");
    }
  }
  else if (input.startsWith("3V3") == 0 && Capacitance_Sensor::__charge_supply != 3)  {
    Capacitance_Sensor::__charge_supply = 3;
    if (Capacitance_Sensor::__charge_resistor.startsWith("40R") != 0 || Capacitance_Sensor::__charge_resistor.startsWith("68R") != 0 || Capacitance_Sensor::__charge_resistor.compareTo("100R") != 0) {
      Capacitance_Sensor::set_resistor("100R");
    }
  }
  else Serial.println("ValueError1: " + input);
}

void Capacitance_Sensor::set_resistor(String input) {
  input.toUpperCase();
  if (input.startsWith(Capacitance_Sensor::__charge_resistor) == 0) return; // Already set
  else if (input.startsWith("INTERNAL") == 0) {
    Serial.println("Setting INTERNAL");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != -1) Capacitance_Sensor::set_supply("INTERNAL");
  }
  else if (input.startsWith("40R") == 0) {
    Serial.println("Setting 3V3 40R");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != 3) Capacitance_Sensor::set_supply("3V3");
  }
  else if (input.startsWith("47R") == 0) {
    Serial.println("Setting 5V 47R");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != 5) Capacitance_Sensor::set_supply("5V");
  }
  else if (input.startsWith("68R") == 0) {
    Serial.println("Setting 68R");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != 3 || Capacitance_Sensor::__charge_supply != 5) Capacitance_Sensor::set_supply("3V3");
  }
  else if (input.startsWith("100R") == 0) {
    Serial.println("Setting 3V3 100R");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != 3) Capacitance_Sensor::set_supply("3V3");
  }
  else if (input.startsWith("150R") == 0) {
    Serial.println("Setting 5V 150R");
    Capacitance_Sensor::__charge_resistor = input;
    if (Capacitance_Sensor::__charge_supply != 5) Capacitance_Sensor::set_supply("5V");
  }
  else Serial.println("ValueError2: " + input + ' ' + String(Capacitance_Sensor::__charge_supply));
}

void Capacitance_Sensor::_trigger_charge_fet(bool state) {
  Serial.print("Trigger\t");
  if (Capacitance_Sensor::__charge_resistor.startsWith("INTERNAL") == 0) {
    Serial.println("INTERNAL");
    bool x[4] = {state, state, state, state};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    Gpio::set_bit(GPIO_FET_3V3, false);
    Gpio::set_bit(GPIO_3V3_100R, false);
    Gpio::set_bit(GPIO_3V3_68R, false);
    Gpio::set_bit(GPIO_FET_5V, false);
    Gpio::set_bit(GPIO_5V_150R, false);
    Gpio::set_bit(GPIO_5V_68R, false);
  }
  else if (Capacitance_Sensor::__charge_resistor.startsWith("40R") == 0) {
    Serial.println("3V3 40R");
    Gpio::set_bit(GPIO_FET_3V3, state);
    Gpio::set_bit(GPIO_3V3_100R, state);
    Gpio::set_bit(GPIO_3V3_68R, state);
    bool x[4] = {false, false, false, false};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    Gpio::set_bit(GPIO_FET_5V, false);
    Gpio::set_bit(GPIO_5V_150R, false);
    Gpio::set_bit(GPIO_5V_68R, false);
  }
  else if (Capacitance_Sensor::__charge_resistor.startsWith("47R") == 0) {
    Serial.println("5V 47R");
    Gpio::set_bit(GPIO_FET_5V, state);
    Gpio::set_bit(GPIO_5V_150R, state);
    Gpio::set_bit(GPIO_5V_68R, state);
    bool x[4] = {false, false, false, false};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    Gpio::set_bit(GPIO_FET_3V3, false);
    Gpio::set_bit(GPIO_3V3_100R, false);
    Gpio::set_bit(GPIO_3V3_68R, false);
  }
  else if (Capacitance_Sensor::__charge_resistor.startsWith("68R") == 0) {
    bool x[4] = {false, false, false, false};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    if (Capacitance_Sensor::__charge_supply == 5) {
      Serial.println("5V 68R");
      Gpio::set_bit(GPIO_FET_5V, state);
      Gpio::set_bit(GPIO_5V_68R, state);
      Gpio::set_bit(GPIO_FET_3V3, false);
      Gpio::set_bit(GPIO_3V3_68R, false);
    }
    else if (Capacitance_Sensor::__charge_supply == 3) {
      Serial.println("3V3 68R");
      Gpio::set_bit(GPIO_FET_3V3, state);
      Gpio::set_bit(GPIO_3V3_68R, state);
      Gpio::set_bit(GPIO_3V3_100R, false);
      Gpio::set_bit(GPIO_FET_5V, false);
      Gpio::set_bit(GPIO_5V_150R, false);
      Gpio::set_bit(GPIO_5V_68R, false);
    }
    else Serial.println("ValueError3: " + Capacitance_Sensor::__charge_resistor);
  }
  else if (Capacitance_Sensor::__charge_resistor.startsWith("100R") == 0) {
    Serial.println("3V3 100R");
    Gpio::set_bit(GPIO_FET_3V3, state);
    Gpio::set_bit(GPIO_3V3_100R, state);
    bool x[4] = {false, false, false, false};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    Gpio::set_bit(GPIO_3V3_68R, false);
    Gpio::set_bit(GPIO_FET_5V, false);
    Gpio::set_bit(GPIO_5V_150R, false);
    Gpio::set_bit(GPIO_5V_68R, false);
  }
  else if (Capacitance_Sensor::__charge_resistor.startsWith("150R") == 0) {
    Serial.println("5V 150R");
    Gpio::set_bit(GPIO_FET_5V, state);
    Gpio::set_bit(GPIO_5V_150R, state);
    bool x[4] = {false, false, false, false};
    Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
    Gpio::set_bit(GPIO_FET_3V3, false);
    Gpio::set_bit(GPIO_3V3_100R, false);
    Gpio::set_bit(GPIO_3V3_68R, false);
    Gpio::set_bit(GPIO_5V_68R, false);
  }
  else Serial.println("ValueError4: " + Capacitance_Sensor::__charge_resistor);
}

void Capacitance_Sensor::_trigger_discharge_fet(bool state) {
  Gpio::set_bit(GPIO_FET_DIS, state);
}

/*
   CHARGE ROUTINE
*/
void Capacitance_Sensor::_charge(void) {
  // Start charging if not already
  if (!Capacitance_Sensor::__charging) {
    Capacitance_Sensor::_trigger_charge_fet(true);
    Capacitance_Sensor::__time_start = micros();
    Capacitance_Sensor::__charging = true;
  }

  // Read in capacitor voltage & calculate charge time so far
  Capacitance_Sensor::__raw = analogRead(PIN_ANALOG);
  float time_charge = (float)(micros() - Capacitance_Sensor::__time_start) * 1e-6; // Seconds

  // What happens if not charged yet
  if (Capacitance_Sensor::__raw < 648) {  // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    return;
  }
  // What happens if charged
  else {
    float resistor = 0.0;
    if (Capacitance_Sensor::__charge_resistor.startsWith("INTERNAL")) {
      resistor = 470.0;
      Serial.println("Resistor: " + 470);
    }
    else if (Capacitance_Sensor::__charge_resistor.startsWith("40R")) {
      resistor = 40.0;
      Serial.println("Resistor: " + 40);
    }
    else if (Capacitance_Sensor::__charge_resistor.startsWith("47R")) {
      resistor = 47.0;
      Serial.println("Resistor: " + 47);
    }
    else if (Capacitance_Sensor::__charge_resistor.startsWith("68R")) {
      resistor = 68.0;
      Serial.println("Resistor: " + 68);
    }
    else if (Capacitance_Sensor::__charge_resistor.startsWith("100R")) {
      resistor = 100.0;
      Serial.println("Resistor: " + 100);
    }
    else if (Capacitance_Sensor::__charge_resistor == "150R") {
      resistor = 150.0;
      Serial.println("Resistor: " + 150);
    }
    else Serial.println("ValueError5: " + Capacitance_Sensor::__charge_resistor);
    Serial.println("Resistor: *" + Capacitance_Sensor::__charge_resistor + '*');


    Capacitance_Sensor::__farads = time_charge / resistor;
    Capacitance_Sensor::__farads = Capacitance_Sensor::__farads < MINIMUM_F ? 0.0 : Capacitance_Sensor::__farads;
    Capacitance_Sensor::new_data = true;
    Capacitance_Sensor::_change_state(2);
  }
}

/*
   DISCHARGE ROUTINE
*/
void Capacitance_Sensor::_discharge(void) {
  // Start discharging if not already
  if (!Capacitance_Sensor::__discharging) {
    Capacitance_Sensor::_trigger_charge_fet(false);
    Capacitance_Sensor::__time_start_discharge = micros();
    Capacitance_Sensor::__discharging = true;
  }
  Capacitance_Sensor::__raw = analogRead(PIN_ANALOG);
  if (Capacitance_Sensor::__raw > DISCHARGE_RAW_VOLTAGE) {
    Capacitance_Sensor::_trigger_discharge_fet(true);
  }
  else {
    Capacitance_Sensor::_trigger_discharge_fet(false);
    delay(REBOUND_DELAY_MS); // TODO delay for rebound
    Capacitance_Sensor::__raw = analogRead(PIN_ANALOG);
    if (Capacitance_Sensor::__raw < DISCHARGE_RAW_VOLTAGE) {
      Capacitance_Sensor::__discharge = (float)(micros() - Capacitance_Sensor::__time_start_discharge); // microSeconds
      Capacitance_Sensor::new_data = true;
      Capacitance_Sensor::_change_state(1);
    }
    else Capacitance_Sensor::_trigger_discharge_fet(true);;
  }
}

/*
   CHANGE STATE INTERNAL METHOD
*/
bool Capacitance_Sensor::_change_state(int state) {
  switch (state) {
    case 3:
      if (Capacitance_Sensor::__state != 3) {
        Capacitance_Sensor::__charging = false;
        Capacitance_Sensor::__state = 3;
        Capacitance_Sensor::new_state = true;
      }
      return true;
      break;
    case 2:
      if (Capacitance_Sensor::__state != 2) {
        Capacitance_Sensor::__discharging = false;
        Capacitance_Sensor::__state = 2;
        Capacitance_Sensor::new_state = true;
      }
      return true;
      break;
    case 1:
      if (Capacitance_Sensor::__state != 1) {
        Capacitance_Sensor::__state = 1;
        Capacitance_Sensor::new_state = true;
      }
      return true;
      break;
    default:
      Serial.println("State change error");
      Capacitance_Sensor::__state = 2;
      return false;
      break;
  }
}

/*
   STOP ALL ROUTINE
*/
void Capacitance_Sensor::stop_all(void) {
  //Gpio::set_bit(GPIO_LED_DANGER, true);
  Capacitance_Sensor::__charging = false;
  Capacitance_Sensor::_change_state(2);
  Serial.println("Stop all");
  bool x[4] = {false, false, false, false};
  Gpio::set_multiple_bits(GPIO_INTERNAL_5V, x, 4);
  Gpio::set_bit(GPIO_FET_3V3, false);
  Gpio::set_bit(GPIO_3V3_100R, false);
  Gpio::set_bit(GPIO_3V3_68R, false);
  Gpio::set_bit(GPIO_FET_5V, false);
  Gpio::set_bit(GPIO_5V_150R, false);
  Gpio::set_bit(GPIO_5V_68R, false);

  while (Capacitance_Sensor::__state != 1) Capacitance_Sensor::_discharge();
}


/* Get Capacitance */
float Capacitance_Sensor::get_capacitance(void) {
  Capacitance_Sensor::new_data = false;
  return Capacitance_Sensor::__farads;
}

/* Get Discharge Time */
float Capacitance_Sensor::get_discharge(void) {
  Capacitance_Sensor::new_data = false;
  return Capacitance_Sensor::__discharge;
}

/* Get State */
String Capacitance_Sensor::get_state(void) {
  Capacitance_Sensor::new_state = false;
  switch (Capacitance_Sensor::__state) {
    case 3: // Charging
      Capacitance_Sensor::state_string = "CHG";
      break;
    case 2: // Discharging
      Capacitance_Sensor::state_string = "DIS";
      break;
    case 1: // Safe
      Capacitance_Sensor::state_string = "SAFE";
      break;
  }
  return Capacitance_Sensor::state_string;
}

