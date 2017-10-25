/*  RCTiming_capacitance_meter
     Paul Badger 2008
    Demonstrates use of RC time constants to measure the value of a capacitor

   Theory   A capcitor will charge, through a resistor, in one time constant, defined as T seconds where
      TC = R * C

      TC = time constant period in seconds
      R = resistance in ohms
      C = capacitance in farads (1 microfarad (ufd) = .0000001 farad = 10^-6 farads )

      The capacitor's voltage at one time constant is defined as 63.2% of the charging voltage.

    Hardware setup:
    Test Capacitor between common point and ground (positive side of an electrolytic capacitor  to common)
    Test Resistor between chargePin and common point
    220 ohm resistor between dischargePin and common point
    Wire between common point and analogPin (A/D input)
*/

#define analogPin      A0         // analog pin for measuring capacitor voltage
#define dischargePin   8         // pin to discharge the capacitor
#define resistorValue  1182.0   // change this to whatever resistor value you are using

char charge_pin = 9;
float resistor  = resistorValue;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;
float milliFarads;
float farads;
void discharge(char pin);
unsigned long charge(char pin);

void setup() {
  pinMode(charge_pin, OUTPUT);
  digitalWrite(charge_pin, LOW);


  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.println("Capacitance Sensor");
}

void loop() {
  /* dicharge the capacitor  */
  discharge(charge_pin);

  unsigned long elapsedTime = charge(charge_pin);
  if (elapsedTime == 0) return;

  //  if (elapsedTime < 5e3) {
  //    Serial.print("auto scaling! ");
  //    selector = constrain(selector + 1, 1, sizeof(charge_pin));
  //    Serial.print(resistor[selector],0); Serial.println("ohms");
  //    return;
  //  }
  //  else if (elapsedTime > 10e3) {
  //    Serial.println("auto scaling! ");
  //    selector = constrain(selector - 1, 1, sizeof(charge_pin));
  //    Serial.print(resistor[selector],0); Serial.println("ohms");
  //    return;
  //  }

  // convert milliseconds to seconds ( 10^-3 ) and Farads to microFarads ( 10^6 ),  net 10^3 (1000)
  farads = ((float)elapsedTime) * 1e-6 / resistor;
  Serial.print(elapsedTime);       // print the value to serial port
  Serial.print("uS\t");         // print units and carriage return

  if (elapsedTime <= 2) Serial.println("Not connected");
  else if (farads >= 1.0) {
    Serial.print(farads, 1);      // print the value to serial port
    Serial.println("F");         // print units and carriage return
  }
  else if (farads > 10e-3) {
    milliFarads = farads * 1e3;
    Serial.print(milliFarads, 1);      // print the value to serial port
    Serial.println("mF");         // print units and carriage return
  }
  else if (farads > 10e-6) {
    microFarads = farads * 1e6;
    Serial.print(microFarads, 1);      // print the value to serial port
    Serial.println("uF");         // print units and carriage return
  }
  else
  {
    nanoFarads = farads * 1e9;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
    Serial.print(nanoFarads, 1);        // print the value to serial port
    Serial.println("nF");          // print units and carriage return
  }
}


unsigned long charge(char pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);  // set chargePin HIGH and capacitor charging
  unsigned long startTime = micros();
  Serial.print("Charging...");
  while (analogRead(analogPin) < 648) {     // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    continue;
  }
  return micros() - startTime;
}

void discharge(char pin) {
  Serial.print("Discharging...");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  while (analogRead(analogPin) > 0) {       // wait until capacitor is completely discharge
    continue;
  }
  Serial.println("done!");
  pinMode(pin, INPUT);
  return;
}

