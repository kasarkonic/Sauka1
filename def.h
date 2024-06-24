#ifndef DEF_H
#define DEF_H

#endif // DEF_H

//for testing
//#define ENABLE_WIDGET_SIZE

#define DIOUT(adr,val)  global.DIoutput[adr].value = val; global.DIoutput[adr].update = true;


// defines outputs


// defines digital inputs


//defines analog inputs

#define  SUPLAY_24V  15 // ANinput4_20[SUPLAY_24V]

#define  MIXSPEED   96//  DIoutput  // invertor 96,97,98
#define  MIXONOFF   97//  DIoutput virtual //

#define  DINOSPEED   98//  DIoutput  virtual //
#define  DINONOFF   99//  DIoutput  virtual //

#define  TVERTNE1LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE1FULL  2//  DIinput   //

#define  PUMP1SPEED   100//  DIoutput  // reveerse => speed + 0x8000
#define  PUMP1NOFF  38//  DIoutput   //

#define  SCALESMASS 100      // DIinput

#define VALVE1ACT   8
#define VALVE1SWOPEN   23
#define VALVE1SWCLOSE   24


// LABEL

//MIX
#define  MIXSPEED   96//  DIoutput  // invertor 96,97,98
#define  MIXONOFF   97//  DIoutput virtual //

//PUMP
#define  PUMP_S4_SPEED   100//  DIoutput  // reveerse => speed + 0x8000
#define  PUMP_S4_NOFF  38//  DIoutput   //

#define  PUMP_S5_SPEED   100//  DIoutput  // reveerse => speed + 0x8000
#define  PUMP_S5_NOFF  38//  DIoutput   //


// TVERTNE
#define  TVERTNE_T2_LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE_T2_FULL  2//  DIinput   //

#define  TVERTNE_T3_LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE_T3_FULL  2//  DIinput   //

#define  TVERTNE_T4_LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE_T4_FULL  2//  DIinput   //

#define  TVERTNE_T5_LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE_T5_FULL  2//  DIinput   //
// VALVE
#define VALVE2_1ACT   3
#define VALVE2_1SWOPEN   23
#define VALVE2_1SWCLOSE   24

#define VALVE2_2ACT   3
#define VALVE2_2SWOPEN   23
#define VALVE2_2SWCLOSE   24

#define VALVE2_3_ACT   3
#define VALVE2_3SWOPEN   23
#define VALVE2_3SWCLOSE   24

#define VALVE2_4ACT   3
#define VALVE2_4SWOPEN   23
#define VALVE2_4SWCLOSE   24

#define VALVE3_1ACT   3
#define VALVE3_1SWOPEN   23
#define VALVE3_1SWCLOSE   24

#define VALVE3_2ACT   3
#define VALVE3_2SWOPEN   23
#define VALVE3_2SWCLOSE   24

#define VALVE3_3_ACT   3
#define VALVE3_3SWOPEN   23
#define VALVE3_3SWCLOSE   24

#define VALVE3_4ACT   3
#define VALVE3_4SWOPEN   23
#define VALVE3_4SWCLOSE   24

#define VALVE4_1ACT   3
#define VALVE4_1SWOPEN   23
#define VALVE4_1SWCLOSE   24

#define VALVE4_2ACT   3
#define VALVE4_2SWOPEN   23
#define VALVE4_2SWCLOSE   24

#define VALVE4_3_ACT   3
#define VALVE4_3SWOPEN   23
#define VALVE4_3SWCLOSE   24

#define VALVE4_4ACT   3
#define VALVE4_4SWOPEN   23
#define VALVE4_4SWCLOSE   24

#define VALVE5_1ACT   3
#define VALVE5_1SWOPEN   23
#define VALVE5_1SWCLOSE   24

#define VALVE5_2ACT   3
#define VALVE5_2SWOPEN   23
#define VALVE5_2SWCLOSE   24

#define VALVE5_3_ACT   3
#define VALVE5_3SWOPEN   23
#define VALVE5_3SWCLOSE   24

#define VALVE5_4ACT   3
#define VALVE5_4SWOPEN   23
#define VALVE5_4SWCLOSE   24

#define VALVE6_1ACT   3
#define VALVE6_1SWOPEN   23
#define VALVE6_1SWCLOSE   24

#define VALVE6_2ACT   3
#define VALVE6_2SWOPEN   23
#define VALVE6_2SWCLOSE   24

#define VALVE6_3_ACT   3
#define VALVE6_3SWOPEN   23
#define VALVE6_3SWCLOSE   24

#define VALVE6_4ACT   3
#define VALVE6_4SWOPEN   23
#define VALVE6_4SWCLOSE   24




