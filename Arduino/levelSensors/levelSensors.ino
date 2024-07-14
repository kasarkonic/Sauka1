#include "HX711.h"
#include <TimerOne.h>
/*
  msg format:

  $0 xxxx.x   // 0. sensor pressure value
  $1 xxxx.x   // 1. pressure value
  .
  .
  .
  .
  .

  $10 xxx.x   temperature measurement T1
  $11 xxx.x   temperature measurement T2


  if error

  $0 ERROR text



*/

// temperatures sensors
#include <Adafruit_MAX31865.h>
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(10, 11, 12, 13);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(9, 11, 12, 13);
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
//#define RREF      3900.0  //430.0  thermo1 =>3905.0 Om,  thermo2 =>3975.0 Om

// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  1000.0




// level sensors

// HX711 circuit wiring
const int LOADCELL_1_DOUT_PIN = 2;
const int LOADCELL_1_SCK_PIN = 3;
const int LOADCELL_2_DOUT_PIN = 4;
const int LOADCELL_2_SCK_PIN = 5;
const int LOADCELL_3_DOUT_PIN = 6;
const int LOADCELL_3_SCK_PIN = 7;
HX711 scale_1;
HX711 scale_2;
HX711 scale_3;

//const int LOADCELL_2_DOUT_PIN 4;
//const int LOADCELL_2_SCK_PIN = 5;
//HX711 scale_2;



#define START_MSG 2
#define END_MSG 3
byte start = START_MSG;
byte end = END_MSG;

int timerCount = 0;
int rad;
int koef = 1;

void setup() {



 //    Timer1.initialize(1000000); //1000 ms,   1000000 => 1 s
 //   Timer1.attachInterrupt(timerIsr); // attach the service routine here

  Serial.begin(115200);
  scale_1.begin(LOADCELL_1_DOUT_PIN, LOADCELL_1_SCK_PIN);
  scale_2.begin(LOADCELL_2_DOUT_PIN, LOADCELL_2_SCK_PIN);
  scale_3.begin(LOADCELL_3_DOUT_PIN, LOADCELL_3_SCK_PIN);

  pinMode(LED_BUILTIN, OUTPUT);
  thermo1.begin(MAX31865_4WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo2.begin(MAX31865_4WIRE);  // set to 2WIRE or 4WIRE as necessary
  delay(1000);
}

void loop() {

  long reading_1 ;
  long reading_2 ;
  long reading_3 ;

  if (scale_1.is_ready()) {
    reading_1 = scale_1.read();
    Serial.print("$0 ");
    Serial.println(reading_1);
  }
  
  //-----------------------------------

  //  Serial.print("$1 ");
  if (scale_2.is_ready()) {
    reading_2 = scale_2.read();
    Serial.print("$1 ");
    Serial.println(reading_2);
  }

  //------------------------------------------

  if (scale_3.is_ready()) {
    reading_3 = scale_3.read();
    Serial.print("$2 ");
    Serial.println(reading_3);
  }

  //----------------------------------------------



  delay(100);

  //read temperature
  uint16_t rtd1 = thermo1.readRTD();

  uint16_t rtd2 = thermo2.readRTD();

  //Serial.print(rtd1); Serial.print("   "); Serial.println(rtd2);
  float temp1 =  thermo1.calculateTemperature(rtd1, 1000, 3893.0);
   Serial.print("$10 ");
    Serial.println(temp1);
  delay(100);
  float temp2 =  thermo2.calculateTemperature(rtd2, 1000, 3976.5);
   Serial.print("$11 ");
   Serial.println(temp2);
  // String str = "$" + String(timerCount) + (" ") + String(temp1) + (" ")  + String(temp2) + " ;" ;
  //    Serial.println(str);
  delay(100);



  timerCount++;
  if (timerCount & 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }



}



///////////////////////////////////////
void timerIsr() {
  timerCount++;
  // Serial.println(timerCount);
  if (timerCount % 2 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  //uint16_t rtd1 = thermo1.readRTD();
  //uint16_t rtd2 = thermo2.readRTD();

  //thermo1 =>3905.0 Om,  thermo2 =>3975.0 Om
  //float temp1 =  thermo1.calculateTemperature(rtd1, 1000, 3850.0);
  //float temp2 =  thermo2.calculateTemperature(rtd2, 1000, 3876.0);

  //String str = "$" + String(timerCount) + (" ") + String(temp1) + (" ")  + String(temp2) + " ;" ;
  // Serial.println(str);

}
