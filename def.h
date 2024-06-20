#ifndef DEF_H
#define DEF_H

#endif // DEF_H


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

#define  VALVE1MOTOR   1//  DIoutput  // reveerse => speed + 0x8000
#define  VALVE1SENSOPEN  3//  DIinput   //
#define  VALVE1SENSCLOSE  4//  DIinput   //
#define  SCALESMASS 100      // DIinput
