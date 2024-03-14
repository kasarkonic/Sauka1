
//#include <TimerOne.h>
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(10, 11, 12, 13);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(9, 11, 12, 13);

// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
//#define RREF      3900.0  //430.0  thermo1 =>3905.0 Om,  thermo2 =>3975.0 Om



// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  1000.0



#define START_MSG 2
#define END_MSG 3

int timerCount = 0;
int rad;
int koef = 1;

byte start = START_MSG;
byte end = END_MSG;

void setup() {
  Serial.begin(115200);

  //  Timer1.initialize(1000000); //1000 ms,   1000000 => 1 s
  //  Timer1.attachInterrupt(timerIsr); // attach the service routine here
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(9, OUTPUT);
  //pinMode(10, OUTPUT);
  //pinMode(12,INPUT_PULLUP);

  thermo1.begin(MAX31865_4WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo2.begin(MAX31865_4WIRE);  // set to 2WIRE or 4WIRE as necessary
  delay(1000);


}


void loop() {
  
    uint16_t rtd1 = thermo1.readRTD();
    //digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    //digitalWrite(LED_BUILTIN, LOW);
    uint16_t rtd2 = thermo2.readRTD();

    //Serial.print(rtd1); Serial.print("   "); Serial.println(rtd2);

    float temp1 =  thermo1.calculateTemperature(rtd1, 1000, 3893.0);
    float temp2 =  thermo2.calculateTemperature(rtd2, 1000, 3976.5);

    String str = "$" + String(timerCount) + (" ") + String(temp1) + (" ")  + String(temp2) + " ;" ;
   // if (timerCount % 2) {
   //   digitalWrite(LED_BUILTIN, HIGH);
   // }
    //else {
    //  digitalWrite(LED_BUILTIN, HIGH);
   // }
    Serial.println(str);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    //digitalWrite(LED_BUILTIN, LOW);

    timerCount++;
    //if (timerCount % 2) {
   //   digitalWrite(LED_BUILTIN, HIGH);
   // }
   // else {
   //   digitalWrite(LED_BUILTIN, LOW);
    //}
     
    }


  
  ///////////////////////////////////////
  void timerIsr() {
    timerCount++;
    if (timerCount % 2 == 0) {
      //digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
     // digitalWrite(LED_BUILTIN, LOW);
    }
    
    uint16_t rtd1 = thermo1.readRTD();
    uint16_t rtd2 = thermo2.readRTD();

    //thermo1 =>3905.0 Om,  thermo2 =>3975.0 Om
    float temp1 =  thermo1.calculateTemperature(rtd1, 1000, 3850.0);
    float temp2 =  thermo2.calculateTemperature(rtd2, 1000, 3876.0);

    String str = "$" + String(timerCount) + (" ") + String(temp1) + (" ")  + String(temp2) + " ;" ;
    Serial.println(str);

  }
  
