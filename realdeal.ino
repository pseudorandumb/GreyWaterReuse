// Samsung Artik Makers Against Drought Challenge
#include "HX711.h"
#define SERIAL_ARTIK Serial1 

// HX711.DOUT  - pin #A1 // Data
// HX711.PD_SCK - pin #A0 //Clock?

//HX711 scale(A1, A0);    // parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale(13, 12);    // parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
//  Serial.begin(38400);
  SERIAL_ARTIK.begin(115200);

  SERIAL_ARTIK.println("HX711 Demo");

  SERIAL_ARTIK.println("Before setting up the scale:");
  SERIAL_ARTIK.print("read: \t\t");
  SERIAL_ARTIK.println(scale.read());     // print a raw reading from the ADC

  SERIAL_ARTIK.print("read average: \t\t");
  SERIAL_ARTIK.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  SERIAL_ARTIK.print("get value: \t\t");
  SERIAL_ARTIK.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  SERIAL_ARTIK.print("get units: \t\t");
  SERIAL_ARTIK.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  SERIAL_ARTIK.println("After setting up the scale:");

  SERIAL_ARTIK.print("read: \t\t");
  SERIAL_ARTIK.println(scale.read());                 // print a raw reading from the ADC

  SERIAL_ARTIK.print("read average: \t\t");
  SERIAL_ARTIK.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  SERIAL_ARTIK.print("get value: \t\t");
  SERIAL_ARTIK.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  SERIAL_ARTIK.print("get units: \t\t");
  SERIAL_ARTIK.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
            // by the SCALE parameter set with set_scale

  SERIAL_ARTIK.println("Readings:");
}

void loop() {
  SERIAL_ARTIK.print("one reading:\t");
  SERIAL_ARTIK.print(scale.get_units(), 1);
  SERIAL_ARTIK.print("\t| average:\t");
  SERIAL_ARTIK.println(scale.get_units(10), 1);

  scale.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
