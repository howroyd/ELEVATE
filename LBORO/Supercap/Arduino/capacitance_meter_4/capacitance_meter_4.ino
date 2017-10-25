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

#include <LiquidCrystal.h>
#include <DFR_Key.h>

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";

#define analogPin      A7         // analog pin for measuring capacitor voltage
#define dischargePin   6         // pin to discharge the capacitor
//#define resistorValue  99.2   // change this to whatever resistor value you are using
#define resistorValue  100.0   // change this to whatever resistor value you are using
#define num_pins 3

char charge_pin[num_pins] = {A5, A4, A3};
float resistor[1]  = {resistorValue};
char selector = 1;
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;
float milliFarads;
float farads;
void discharge(char* pin);
long charge(char* pin);
int Vtau;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitance V1.4");
  //keypad.setRate(10);


  // Setup pin modes
  for (int i = 0; i < num_pins; i++) {
    pinMode(charge_pin[i], OUTPUT);
    digitalWrite(charge_pin[i], LOW);
  }
  pinMode(dischargePin, OUTPUT);
  pinMode(analogPin, INPUT);

  // Set charge pins hig, read in the voltage and calculate 63%. Allows for changing potential without needing to reprogramme
  //pinMode(A1, OUTPUT); digitalWrite(A1, HIGH);
  //delay(1000);
  /*
    analogReference(EXTERNAL);
    for (int i = 0; i < num_pins; i++) {
    pinMode(charge_pin[i], OUTPUT);
    digitalWrite(charge_pin[i], HIGH);
    }
    delay(100);
    Vtau = 0.63 * analogRead(analogPin);
    for (int i = 0; i < num_pins; i++) {
    pinMode(charge_pin[i], OUTPUT);
    digitalWrite(charge_pin[i], LOW);
    }
  */
  Vtau = 0.63 * 1023;
  Serial.begin(115200);             // initialize serial transmission for debugging
  Serial.print("\n\nCapacitance Sensor at ");
  Serial.print((float)Vtau * 0.00488 / 0.63, 2);
  Serial.println("V\n\n");
}

void loop() {
  /* dicharge the capacitor  */
  discharge(charge_pin);

  elapsedTime = charge(charge_pin);

  String verbose2 = "";
  String disp = "";

  // convert microseconds to seconds ( 10^-6 )
  farads = (float)elapsedTime * 1e-6 / resistor[0];
  verbose2 += elapsedTime;       // print the value to serial port
  verbose2 += "uS\t";         // print units and carriage return

  if (elapsedTime <= 2) {
    verbose2 += "Not connected";
    disp += "NC";
  }
  else if (farads >= 1.0) {
    verbose2 += (String(farads, 1) + "F");      // print the value to serial port
    disp += (String(farads, 1) + "F");         // print units and carriage return
    selector = 0;
  }
  else if (farads > 10e-3) {
    milliFarads = farads * 1e3;
    verbose2 += (String(milliFarads, 1) + "mF");      // print the value to serial port
    disp += (String(milliFarads, 1) + "mF");         // print units and carriage return
    selector = 1;
  }
  else if (farads > 10e-6) {
    microFarads = farads * 1e6;
    verbose2 += (String(microFarads, 1) + (char)228 + "F");      // print the value to serial port
    disp += (String(microFarads, 1) + (char)228 + "F");         // print units and carriage return
    selector = 2;
  }
  else
  {
    nanoFarads = farads * 1e9;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
    verbose2 += (String(nanoFarads, 1) + "nF");      // print the value to serial port
    disp += (String(nanoFarads, 1) + "nF");         // print units and carriage return
    selector = 3;
  }

  Serial.println(verbose2);
  lcd.setCursor(0, 1);
  lcd.print(disp);
}


long charge(char* pin) {
  for (int i = 0 ; i < num_pins ; i++) {
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], HIGH);  // set chargePin HIGH and capacitor charging
  }
  startTime = micros();
  Serial.print("Charging...");
  while (analogRead(analogPin) < Vtau) {     // 647 is 63.2% of 1023, which corresponds to full-scale voltage
  }
  return micros() - startTime;
}

void discharge(char* pin) {
  Serial.print("Discharging...");
  for (int i = 0; i < num_pins; i++) {
    pinMode(pin[i], INPUT);
  }
  while (true) {       // wait until capacitor is completely discharge
    digitalWrite(dischargePin, HIGH);
    delay(100);
    if (analogRead(analogPin) <= 0) {
      digitalWrite(dischargePin, LOW);
      delay(100);
      if (analogRead(analogPin) <= 0) break;
    }
  }
  return;
}

