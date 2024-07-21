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



// level sensors

// HX711 circuit wiring
const int LOADCELL_1_DOUT_PIN = 2;
const int LOADCELL_1_SCK_PIN = 3;
const int LOADCELL_2_DOUT_PIN = 4;
const int LOADCELL_2_SCK_PIN = 5;
const int LOADCELL_3_DOUT_PIN = 6;
const int LOADCELL_3_SCK_PIN = 7;
HX711 press_1;
HX711 press_2;
HX711 press_3;

#define START_MSG 2
#define END_MSG 3
byte start = START_MSG;
byte end = END_MSG;
int timerCount = 0;

#define MODBUS_ID 20
#define TOPSENS0  A0
#define TOPSENS0  A1
#define TOPSENS0  A2

const byte topSensPins[3] = {A0, A1, A2};





const byte potPins[2] = {A3, A4};

const byte buttonPins[2] = {2, 3};
const byte ledPins[4] = {5, 6, 7, 8};
const byte dePin = 29;


ModbusRTUSlave modbus(Serial1, dePin); // serial port, driver enable pin for rs-485




bool coils[2];
bool discreteInputs[2];
uint16_t holdingRegisters[2];
uint16_t inputRegisters[8];

void setup() {

  Serial.begin(115200);
  press_1.begin(LOADCELL_1_DOUT_PIN, LOADCELL_1_SCK_PIN);
  press_2.begin(LOADCELL_2_DOUT_PIN, LOADCELL_2_SCK_PIN);
  press_3.begin(LOADCELL_3_DOUT_PIN, LOADCELL_3_SCK_PIN);
  pinMode(LED_BUILTIN, OUTPUT);

/*
  pinMode(potPins[0], INPUT);
  pinMode(potPins[1], INPUT);
  pinMode(buttonPins[0], INPUT_PULLUP);
  pinMode(buttonPins[1], INPUT_PULLUP);
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);
*/


  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(dePin, OUTPUT);

  modbus.configureCoils(coils, 2);                       // bool array of coil values, number of coils
  modbus.configureDiscreteInputs(discreteInputs, 2);     // bool array of discrete input values, number of discrete inputs
  modbus.configureHoldingRegisters(holdingRegisters, 2); // unsigned 16 bit integer array of holding register values, number of holding registers
  modbus.configureInputRegisters(inputRegisters, 8);     // unsigned 16 bit integer array of input register values, number of input registers
 // Serial1.begin(38400,SERIAL_8E1); even parity
  modbus.begin(1, 38400,SERIAL_8E1);

  //#if defined USE_SOFTWARE_SERIAL
  //serial.begin(MODBUS_ID, 38400);
  //#endif

  Serial.begin(115200);

  Serial.println("ModbusRTUSlave");

  delay(1000);
}

void loop() {

  long reading_1 ;
  long reading_2 ;
  long reading_3 ;
  modbus.poll();
  if (press_1.is_ready()) {
    reading_1 = press_1.read();
    //  Serial.print("$0 ");
    //  Serial.println(reading_1);

  }
  //delay(50);
  //-----------------------------------


  if (press_2.is_ready()) {
    reading_2 = press_2.read();
    //  Serial.print("$1 ");
    //  Serial.println(reading_2);
  }
  //delay(50);
  //------------------------------------------

  if (press_3.is_ready()) {
    reading_3 = press_3.read();
    //  Serial.print("$2 ");
    //  Serial.println(reading_3);
  }
  //delay(50);
  //----------------------------------------------


  int top1 = analogRead (topSensPins[0]); // if <> 900 trigered
  int top2 = analogRead (topSensPins[1]);
  int top3 = analogRead (topSensPins[2]);


  //Serial.print(top1);
  //Serial.print("  ");
  //Serial.print(top2);
  //Serial.print("  ");
  //Serial.println(top3);

  inputRegisters[0] = (int)reading_1;
  inputRegisters[1] = (int)reading_2;
  inputRegisters[2] = (int)reading_3;
  inputRegisters[3] = 1234;
  inputRegisters[4] = (int)top1;
  inputRegisters[5] = (int)top2;
  inputRegisters[6] = (int)top3;
  inputRegisters[7] = 5678;


  discreteInputs[0] = 1;// !digitalRead(buttonPins[0]);
  discreteInputs[1] = 0; //!digitalRead(buttonPins[1]);

  holdingRegisters[0] = 4321;
  holdingRegisters[1] = 8765;

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
  //delay(100);
}
