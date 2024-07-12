#ifndef DEF_H
#define DEF_H

#include <QList>
#include "def.h"

#define DIOUT(adr,val)  global.DIoutput[adr].value = val; global.DIoutput[adr].update = true;


// define rive adress
#define M8 18
#define M9 19   // ??
#define M4 14  // ??

// defines drive registers
#define CMD_REG  8501   // command reg
#define LFR_REG  8502   // set frequence
#define LFRD_REG 8602   // set rpm
#define ETA_REG  3201   // drive status
#define RFRD_REG 8604   // output velocyty  use len = 3
#define ERRD 8606   //CiA402 fault code  see error code table  driveErrorCodes[]
#define STOS    15322   // STO status

#define SAF1    15350   // Safety fault register 1  use len 14
#define SAF2    15359   // Safety fault register 2
#define SF00    15351   // Safety fault subregister 0:15351   subregister 11: 15363

#define WR_REG 6
#define RD_REG 3

// defines ports count
#define DI_IN_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIinput
#define DI_OUT_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIoutput
#define AN_IN_START_ADDRESS DI_IN_START_ADDRESS + MAX_DIinput // modbuss address 2  ANinput 1-15
#define AN_VIRTUAL_IN_START_ADDRESS AN_IN_START_ADDRESS + MAX_AN_INPUT4_20 // modbuss address 2  ANinput 1-15

#define VIRUAL_PORTS 16 // Virtual input copy invertor ON/OFF
#define MAX_DIinput     32*3 + VIRUAL_PORTS       // addres [0 , MAX_DIinp] 32*3
#define MAX_DIoutput     32*3 + VIRUAL_PORTS      // addres [0 , MAX_DIinp] + MAX_AN_VIRUAL_INPUT invertor speed, on/off...
#define MAX_ACTUATOR    64  // addres [0 , MAX_DIoutput]
#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V


// defines virtual inputs


enum virtualInputs
{
    scales_mass = MAX_DIinput - VIRUAL_PORTS  ,    // virtual input

    drive_M8_status,
    drive_M8_speed,
    drive_M4_status,
    drive_M4_speed,
    drive_M9_status,
    drive_M9_speed,


    mix_speeds,
    dino_speed,
    pump1_speed



};

enum virtualOutputs
{

    set_mix_speed = MAX_DIoutput - VIRUAL_PORTS,
    set_mix_On_Off,
    set_dino_speed,
    set_dino_On_Off,
    set_pump1_speed,
    set_pump1_On_Off,

};



//defines analog inputs

#define  SUPLAY_24V  15 // ANinput4_20[SUPLAY_24V]


#define  TVERTNE1LEVEL   1// DIinput   ANinput4_20  //
#define  TVERTNE1FULL  2//  DIinput   //


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

#define LEVEL_SENSOR_1   101
#define LEVEL_SENSOR_2   102
#define TEMP_SENSOR_1   103
#define TEMP_SENSOR_2   104

class Def {
public:
    Def();
};

#endif // DEF_H
