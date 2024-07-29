/*
  ModbusRTUSlave


  Circuit:
  - The center pin of a potentiometer to pin A0, and the outside pins of the potentiometer to your board's logic level voltage (5V or 3.3V) and GND
  - The center pin of a potentiometer to pin A1, and the outside pins of the potentiometer to your board's logic level voltage (5V or 3.3V) and GND
  - A pushbutton switch from pin 2 to GND
  - A pushbutton switch from pin 3 to GND
  - A LED from pin 5 to GND with a 1K ohm series resistor
  - A LED from pin 6 to GND with a 1K ohm series resistor
  - A LED from pin 7 to GND with a 1K ohm series resistor
  - A LED from pin 8 to GND with a 1K ohm series resistor
  - RX pin (typically pin 0 or pin 10 if using SoftwareSerial) to TX pin of the master/client board
  - TX pin (typically pin 1 or pin 11 if using SoftwareSerial) to RX pin of the master/client board
  - GND to GND of the master/client board
  - Pin 13 is set up as the driver enable pin. This pin will be HIGH whenever the board is transmitting.

  Library Created: 2023-07-22
  By: C. M. Bulliner
  Last Modified: 2024-06-29
  By: C. M. Bulliner

*/


#include <ModbusRTUSlave.h>
#include "HX711.h"
#include <TimerOne.h>
#include <Adafruit_MAX31865.h>



// level sensors
// pressure sensors
// HX711 circuit wiring
const int LOADCELL_1_DOUT_PIN = 30;//2;
const int LOADCELL_1_SCK_PIN = 32;//3;
const int LOADCELL_2_DOUT_PIN = 34;//"4;
const int LOADCELL_2_SCK_PIN = 36;//5;
const int LOADCELL_3_DOUT_PIN = 38;// 6;
const int LOADCELL_3_SCK_PIN = 40;//7;
const int LOADCELL_4_DOUT_PIN = 42;//8;
const int LOADCELL_4_SCK_PIN = 44;//9;
HX711 press_1;
HX711 press_2;
HX711 press_3;
HX711 press_4;



#define START_MSG 2
#define END_MSG 3
byte start = START_MSG;
byte end = END_MSG;
int timerCount = 0;




//*************************************************
// temperature sensors
#define  T1CS 53
#define  T2CS 49
#define  T3CS 47
#define  T4CS 45


Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(T1CS);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(T2CS);
Adafruit_MAX31865 thermo3 = Adafruit_MAX31865(47);
Adafruit_MAX31865 thermo4 = Adafruit_MAX31865(45);
#define RREF     2200.0 // 430.0 //1000.0
#define RNOMINAL  1000.0


//*************************************************
// full fill sensors
#define TOPSENS0  A0
#define TOPSENS1  A1
#define TOPSENS2  A2
#define TOPSENS3  A3


//*************************************************
// poard Id
byte modbusID; //  20 +  ADD0 + ADD1 *2
// Modbus node addres = 20 + ADD0*1 +ADD1*2
// booth pins are INPUT_PULLUP it means  value 1
// default address = 20 + 1 + 2 = 23.
// short pins to ground, when change address. ground is pin 14.

byte ADD0 = A13;  // Modbus node addres = 20 + ADD0*1 +ADD1*2
byte ADD1 = A14;
byte ADDGND = A15;
// pin A14 ground


//#define Rx 10
//#define Tx 11

const byte topSensPins[4] = {A0, A1, A2, A3};





//const byte potPins[2] = {A3, A4};

const byte buttonPins[2] = {2, 3};
//const byte ledPins[4] = {5, 6, 7, 8};
const byte dePin = 29;    // Di pin  Hi when Tx,  Lo when Rx outputs in hight impedance
const byte rePin = 31;// !Re  Lo  receive enable , must be low



ModbusRTUSlave modbus(Serial1, dePin); // serial port, driver enable pin for rs-485




bool coils[2];
bool discreteInputs[2];
uint16_t holdingRegisters[12];
uint16_t inputRegisters[8];

void setup() {

  Serial.begin(115200);

  pinMode(LOADCELL_1_DOUT_PIN, INPUT);
  pinMode(LOADCELL_1_SCK_PIN, OUTPUT);
  pinMode(LOADCELL_2_DOUT_PIN, INPUT);
  pinMode(LOADCELL_2_SCK_PIN, OUTPUT);
  
  press_4.begin(LOADCELL_1_DOUT_PIN, LOADCELL_1_SCK_PIN);
  press_3.begin(LOADCELL_2_DOUT_PIN, LOADCELL_2_SCK_PIN);
  press_2.begin(LOADCELL_3_DOUT_PIN, LOADCELL_3_SCK_PIN);
  press_1.begin(LOADCELL_4_DOUT_PIN, LOADCELL_4_SCK_PIN);

  thermo1.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo2.begin(MAX31865_3WIRE);
  thermo3.begin(MAX31865_3WIRE);
  thermo4.begin(MAX31865_3WIRE);

  pinMode(T1CS, OUTPUT);
  pinMode(T2CS, OUTPUT);
  pinMode(T3CS, OUTPUT);
  pinMode(T4CS, OUTPUT);


  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rePin, OUTPUT);
  digitalWrite(rePin, LOW);

  pinMode(ADD0, INPUT);
  pinMode(ADD1, INPUT);
  pinMode(ADD0, INPUT_PULLUP);
  pinMode(ADD1, INPUT_PULLUP);
  pinMode(ADDGND, OUTPUT);
  digitalWrite(ADDGND, LOW);

  modbusID = 20 + digitalRead(ADD0) + digitalRead(ADD1) * 2;



  modbus.configureCoils(coils, 2);                       // bool array of coil values, number of coils
  modbus.configureDiscreteInputs(discreteInputs, 2);     // bool array of discrete input values, number of discrete inputs
  modbus.configureHoldingRegisters(holdingRegisters, 12); // unsigned 16 bit integer array of holding register values, number of holding registers
  modbus.configureInputRegisters(inputRegisters, 8);     // unsigned 16 bit integer array of input register values, number of input registers
  modbus.begin(modbusID, 38400, SERIAL_8E1);

  //   modbus.begin(MODBUS_ID, 9600,SERIAL_8E1);
  //modbus.begin(MODBUS_ID, 38400);
  // modbus.begin(MODBUS_ID, 9600);
  // Serial1.begin(9600);

  //#if defined USE_SOFTWARE_SERIAL
  //  modbus.begin(MODBUS_ID, 38400, SERIAL_8E1);
  //#endif

  Serial.print("ModbusRTUSlave Id = ");
  Serial.println(modbusID);
  //  Serial1.println("ModbusRTUSlave");

  delay(1000);
}

void loop() {
  /*
     if (Serial1.available() > 0) {
      int incomingByte = Serial.read();

    // say what you got:
     Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
     }
  */
  int t1 = 0;
  int t2 = 0;
  int t3 = 0;
  int t4 = 0;

  uint16_t rtd1 = thermo1.readRTD();
  float ratio = rtd1 / 32768;
  t1 = thermo1.temperature(RNOMINAL, RREF) * 100; // t1 = (int) temp*100
  Serial.print("Temperature1 = ");
  Serial.print(t1);
  Serial.print("  raw = ");
  Serial.println(rtd1);
  int fcode = thermo1.readFault();
  if (fcode) {
    Serial.print("faults in 1.termometer code: ");
    Serial.println(fcode, HEX);
    faults(fcode);
    thermo1.clearFault();
    t1 = 0x19999;
  }


  uint16_t rtd2 = thermo2.readRTD();
  ratio = rtd2 / 32768;
  t2 = thermo2.temperature(RNOMINAL, RREF) * 100; // t12 = (int) temp*100
  Serial.print("Temperature2 = ");
  Serial.print(t2);
  Serial.print("  raw = ");
  Serial.println(rtd2);
  fcode = thermo2.readFault();
  if (fcode) {
    Serial.print("faults in 2.termometer code: ");
    Serial.println(fcode, HEX);
    faults(fcode);
    thermo2.clearFault();
    t2 = 0x19999;
  }

  uint16_t rtd3 = thermo3.readRTD();
  ratio = rtd3 / 32768;
  t3 = thermo3.temperature(RNOMINAL, RREF) * 100; // t12 = (int) temp*100
  Serial.print("Temperature3 = ");
  Serial.print(t3);
  Serial.print("  raw = ");
  Serial.println(rtd3);
  fcode = thermo3.readFault();
  if (fcode) {
    Serial.print("faults in 3.termometer code: ");
    Serial.println(fcode, HEX);
    faults(fcode);
    thermo3.clearFault();
    t3 = 0x19999;
  }

  uint16_t rtd4 = thermo4.readRTD();
  ratio = rtd4 / 32768;
  t4 = thermo4.temperature(RNOMINAL, RREF) * 100; // t12 = (int) temp*100
  Serial.print("Temperature4 = ");
  Serial.print(t4);
  Serial.print("  raw = ");
  Serial.println(rtd4);
  fcode = thermo4.readFault();
  if (fcode) {
    Serial.print("faults in 4.termometer code: ");
    Serial.println(fcode, HEX);
    faults(fcode);
    thermo4.clearFault();
    t4 = 0x19999;
  }

  modbus.poll();

  long reading_1 ;
  long reading_2 ;
  long reading_3 ;
  long reading_4 ;

  if (press_1.is_ready()) {
    reading_1 = press_1.read();
    Serial.print("Pres1=");
    Serial.print(reading_1);

  }
  //delay(50);
  //-----------------------------------


  if (press_2.is_ready()) {
    reading_2 = press_2.read();
    Serial.print(",  Pres2=");
    Serial.print(reading_2);
  }
  //delay(50);
  //------------------------------------------

  if (press_3.is_ready()) {
    reading_3 = press_3.read();
    Serial.print(",  Pres3=");
    Serial.print(reading_3);
  }
  //delay(50);
  //----------------------------------------------

  if (press_4.is_ready()) {
    reading_4 = press_4.read();
    Serial.print(",  Pres4=");
    Serial.println(reading_4);
  }
  //delay(50);
  //----------------------------------------------


  int top1 = analogRead (topSensPins[0]); // if <> 900 trigered
  int top2 = analogRead (topSensPins[1]);
  int top3 = analogRead (topSensPins[2]);
  int top4 = analogRead (topSensPins[3]);


  Serial.print("Top sensor raw: ");
  Serial.print(top1);
  Serial.print("  ");
  Serial.print(top2);
  Serial.print("  ");
  Serial.print(top3);
  Serial.print("  ");
  Serial.println(top4);

  /* inputRegisters[0] = (int)reading_1;
    inputRegisters[1] = (int)reading_2;
    inputRegisters[2] = (int)reading_3;
    inputRegisters[3] = (int)reading_4;
    inputRegisters[4] = (int)top1;
    inputRegisters[5] = (int)top2;
    inputRegisters[6] = (int)top3;
    inputRegisters[7] = (int)top4;
  */

  holdingRegisters[0] = (int)reading_1;
  holdingRegisters[1] = (int)reading_2;
  holdingRegisters[2] = (int)reading_3;
  holdingRegisters[3] = (int)reading_4;
  holdingRegisters[4] = (int)top1;
  holdingRegisters[5] = (int)top2;
  holdingRegisters[6] = (int)top3;
  holdingRegisters[7] = (int)top4;
  holdingRegisters[8] = (int)t1;
  holdingRegisters[9] = (int)t2;
  holdingRegisters[10] = (int)t3;
  holdingRegisters[11] = (int)t4;




  discreteInputs[0] = 1;// !digitalRead(buttonPins[0]);
  discreteInputs[1] = 0; //!digitalRead(buttonPins[1]);


  //modbus.poll();

  //analogWrite(ledPins[0], holdingRegisters[0]);
  //analogWrite(ledPins[1], holdingRegisters[1]);
  //digitalWrite(ledPins[2], coils[0]);
  //digitalWrite(ledPins[3], coils[1]);





  timerCount++;
  if (timerCount & 1) {
    digitalWrite(LED_BUILTIN, HIGH);

  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(100);
}
void faults(int code) {
  return;
  // Check and print any faults
  //uint8_t code = thermo1.readFault();
  if (code) {
    Serial.print("Fault 0x"); Serial.println(code, HEX);
    if (code & MAX31865_FAULT_HIGHTHRESH) {
    }
    if (code & MAX31865_FAULT_LOWTHRESH) {
    }
    if (code & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (code & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (code & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (code & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    // thermo1.clearFault();
  }

}
