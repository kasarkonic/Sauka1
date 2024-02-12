
#include <TimerOne.h>

#define TEST_DELAY   1000 
#define START_MSG 2
#define END_MSG 3

 int timerCount;
 int rad;
 int koef = 1;

byte start = START_MSG;
byte end = END_MSG;

void setup() {
  Serial.begin(115200);
  
  Timer1.initialize(100000); //100 ms,   1000000 => 1 s
  Timer1.attachInterrupt(timerIsr); // attach the service routine here

  timerCount = 0;
}


void loop() {

}


void timerIsr(){
  timerCount++;
  int t = timerCount%10000; 
  rad = rad + koef;
  if (rad >= 30)
    koef = -1;
  if (rad <= 0)
  koef = 1;  

  //Serial.print("T1,");
String str = "$" + String(timerCount) + (" ")+ String(rad + 50) + (" ")  + String(rad + 25) + ";" ;
//String str = String(t) + ("T1,") + String(rad + 50) + ",T2," + String(rad + 25) + "," ;
//str + ("T1,");
//str.append(String(rad + 50));
//str.append(",T2,");
//str.append(String(rad + 25));
//str.append(",");

  Serial.println(str);

   }

  
