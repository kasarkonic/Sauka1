#ifndef DEF_H
#define DEF_H

#include <QList>

#define DIOUT(adr,val)  global.DIoutput[adr].value = val; global.DIoutput[adr].update = true;


// define rive adress
#define M8 18
#define M9 19   // ??
#define M4 14  // ??
#define SENSORS 20 // tvertnĒm sensori

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

#define VIRUAL_PORTS 32 // Virtual input copy invertor ON/OFF
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
    pump1_speed,

    TVERTNE1LEVEL ,
    TVERTNE2LEVEL,
    TVERTNE3LEVEL,
    TVERTNE4LEVEL,
    TVERTNE5LEVEL,


    TVERTNE1FULL,
    TVERTNE2FULL,
    TVERTNE3FULL,
    TVERTNE4FULL,
    TVERTNE5FULL,

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

enum a1DIn
{
    Fāzu_relejs_RF1 = 0,    // nr. on board  => IN1
    Automātslēdži,
    Mot_aizs_1Q1,
    Mot_aizs_2Q1,
    Mot_aizs_3Q1,
    Mot_aizs_5Q1,
    Mot_aizs_6Q1,
    Mot_aizs_7Q1,
    dInomill_10Q1,
    VFD_4U1_ready,
    VFD_8U1_ready,
    VFD_9U1_ready,
    Rot_kontrole_šnekam,
    Šneks_auto_run,
    Šneks_manual_run,
    Šneks_MAN_FWD,
    Šneks_MAN_REV,
    Kontaktors_1KM1_ieslēgts,
    Kontaktors_2KM1_ieslēgts,
    Kontaktors_3KM1_ieslēgts,
    Kontaktors_5KM1_ieslēgts,
    Kontaktors_6KM1_ieslēgts,
    Kontaktors_7KM1_ieslēgts,

    kontrolbarošana_T2_Murr = 31,   // nr. on board  => IN32




};

enum a1DOut
{

    brīvs = 0,                  // nr. on board  => Q1
    Ieslēgt_kontaktor_1KM1,
    Ieslēgt_kontaktoru_2KM1,
    Ieslēgt_kontaktoru_3KM1,
    Ieslēgt_kontaktoru_5KM1,
    Ieslēgt_kontaktoru_6KM1,
    Ieslēgt_kontaktoru_7KM1,
    Luksofors_sirēna,


    VFD_Reset,
    brīvs1,
    Y1_1_atvērt,
    Y1_2_atvērt,
    Y1_3_atvērt,
    brīvs2,
    Y2_1_atvērt,
    Y2_1_aizv,
    Y2_2_atvērt,
    Y2_2_aizv,
    Y2_3_atvērt,
    Y2_3_aizv,
    Y2_4_atvērt,
    Y2_4_aizv,
    Y3_1_atvērt,
    Y3_1_aizv,
    Y3_2_atvērt,
    Y3_2_aizv,
    Y3_3_atvērt,
    Y3_3_aizv,
    Y3_4_atvērt,
    Y3_4_aizv,

};

enum a2DIn
{
    Y2_1_close = 32, // nr. on board  => IN1
    Y2_1_open,
    Y2_2_close,
    Y2_2_open,
    Y2_3_close,
    Y2_3_open,
    Y2_4_close,
    Y2_4_open,
    Y3_1_close,
    Y3_1_open,
    Y3_2_close,
    Y3_2_open,
    Y3_3_close,
    Y3_3_open,
    Y3_4_close,
    Y3_4_open,
    Y4_1_close,
    Y4_1_open,
    Y4_2_close,
    Y4_2_open,
    Y4_3_close,
    Y4_3_open,
    Y4_4_close,
    Y4_4_open,
    Y5_1_close,
    Y5_1_open,
    Y5_2_close,
    Y5_2_open,
    Y5_3_close,
    Y5_3_open,
    Y5_4_close,
    Y5_4_open,

};

enum a2DOut
{
    Y4_1_atvērt_4KY1 = 32,  // nr. on board  => Q1
    Y4_1_aizv_4KY2,
    Y4_2_atvērt_4KY3,
    Y4_2_aizv_4KY4,
    Y4_3_atvērt_4KY5,
    Y4_3_aizv_4KY6,
    Y4_4_atvērt_4KY7,
    Y4_4_aizv_4KY8,
    Y5_1_atvērt_5KY1,
    Y5_1_aizv_5KY2,
    Y5_2_atvērt_5KY3,
    Y5_2_aizv_5KY4,
    Y5_3_atvērt_5KY5,
    Y5_3_aizv_5KY6,
    Y5_4_atvērt_5KY7,
    Y5_4_aizv_5KY8,

};
enum a3DIn
{
    Y6_1_ciet = 64, // nr. on board  => IN1
    Y6_1_vaļā,
    Y6_2_ciet,
    Y6_2_vaļā,

};

enum a3DOut
{
    Outx = 64,  // nr. on board  => Q1
};











//#define  TVERTNE1LEVEL   1// DIinput   ANinput4_20  //
//#define  TVERTNE1FULL  2//  DIinput   //


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


#define VALVE2_3_ACT   3


#define VALVE2_4ACT   3


#define VALVE3_1ACT   3


#define VALVE3_2ACT   3


#define VALVE3_3_ACT   3


#define VALVE3_4ACT   3


#define VALVE4_1ACT   3


#define VALVE4_2ACT   3


#define VALVE4_3_ACT   3


#define VALVE4_4ACT   3


#define VALVE5_1ACT   3

#define VALVE5_2ACT   3

#define VALVE5_3_ACT   3

#define VALVE5_4ACT   3


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
#define LEVEL_SENSOR_3   103
#define TEMP_SENSOR_1   104
#define TEMP_SENSOR_2   105


class Def {
public:
    Def();
};

#endif // DEF_H
