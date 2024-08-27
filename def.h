#ifndef DEF_H
#define DEF_H

#include <QList>

#define DIOUT(adr,val)  global.DIoutput[adr].value = val; global.DIoutput[adr].update = 1;


// define rive adress
#define M8 18   // conveyor
#define M9 19   // MIX
#define M4 14  // Pump Mohno 5.5kw

#define SENSOR_BOARD 20 // tvertnĒm sensori

// defines drive registers
#define CMD_REG  8501   // command reg
#define LFR_REG  8502   // set frequence
#define LFRD_REG 8602   // set rpm
#define ETA_REG  3201   // drive status
#define RFRD_REG 8604   // output velocyty, 8605 ramp speed, 8606 error  use len = 3 ?
#define ERRD 8606   //CiA402 fault code  see error code table  driveErrorCodes[]
#define STOS    15322   // STO status

#define SAF1    15350   // Safety fault register 1  use len 14
#define SAF2    15359   // Safety fault register 2
#define SF00    15351   // Safety fault subregister 0:15351   subregister 11: 15363

#define WR_REG 6
#define RD_REG 3
#define RD_IN_REG 4

// defines ports count
#define DI_IN_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIinput
#define DI_OUT_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIoutput
#define AN_IN_START_ADDRESS DI_IN_START_ADDRESS + MAX_DIinput // modbuss address 2  ANinput 1-15
#define AN_VIRTUAL_IN_START_ADDRESS AN_IN_START_ADDRESS + MAX_AN_INPUT4_20 // modbuss address 2  ANinput 1-15

#define VIRUAL_PORTS 128 // Virtual input copy invertor ON/OFF
#define MAX_DIinput     32*3 + VIRUAL_PORTS       // addres [0 , MAX_DIinp] 32*3
#define MAX_DIoutput     32*3 + VIRUAL_PORTS      // addres [0 , MAX_DIinp] + MAX_AN_VIRUAL_INPUT invertor speed, on/off...
#define MAX_ACTUATOR    64  // addres [0 , MAX_DIoutput]
#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V


// defines virtual inputs


//defines analog inputs

#define  SUPLAY_24V  15 // ANinput4_20[SUPLAY_24V]

//*********** INPUTS ****************
enum A1DIn
{
    Fazu_relejs_RF1,    // nr. on board  => IN1
    Automatsledzi,
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
    Mot_aiz_11Q1,
    Sneks_auto_run,
    Sneks_manual_run,
    Sneks_MAN_FWD,
    Sneks_MAN_REV,
    Kontaktors_1KM1_ieslegts,
    Kontaktors_2KM1_ieslegts,
    Kontaktors_3KM1_ieslegts,
    Kontaktors_5KM1_ieslegts,
    Kontaktors_6KM1_ieslegts,
    Kontaktors_7KM1_ieslegts,
    Kontaktors_5KM2_ieslēgts,
    Kontaktors_12KM1_ieslēgts,
    Motora_aizsardzība_12Q1,
    Nop,
    Y6_1_close,
    Y6_1_open,
    Y6_2_close,
    Y6_2_open,
    kontrolbarosana_T2_Murr,   // nr. on board  => IN32
};


enum A2DIn
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


enum A3DIn
{
};


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

    TVERTNE1TEMP,
    TVERTNE2TEMP,
    TVERTNE3TEMP,
    TVERTNE4TEMP,
    TVERTNE5TEMP,

    TVERTNE1LEVELPROC,
    TVERTNE2LEVELPROC,
    TVERTNE3LEVELPROC,
    TVERTNE4LEVELPROC,
    TVERTNE5LEVELPROC,

    TVERTNE1KALIBEMPTY,
    TVERTNE1KALIBFULL,
    TVERTNE2KALIBEMPTY,
    TVERTNE2KALIBFULL,
    TVERTNE3KALIBEMPTY,
    TVERTNE3KALIBFULL,
    TVERTNE4KALIBEMPTY,
    TVERTNE4KALIBFULL,
    TVERTNE5KALIBEMPTY,
    TVERTNE5KALIBFULL,


};

//*********** OUTPUTS ****************

enum A1DOut
{
    set_pump2_2_On_Off_FW = 0,                  // nr. on board  => Q1
    On_pilda_H2o,
    On_pilda_Na,
    On_pilda_B,
    set_pump2_2_On_Off_RW = 4,
    set_dispax_On_Off = 5,
    On_MOHNO_5_5_On_Off,
    H3,
    H4,
    H5,
    VFD_Reset,
    Dispax_2_On,         // jaunais/ 11kW Dispax 2.


    Y1_1_atvērt = 12,
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
enum A2DOut
{
    Y4_1_atvērt = 32,  // nr. on board  => Q1
    Y4_1_aizv,
    Y4_2_atvērt,
    Y4_2_aizv,
    Y4_3_atvērt,
    Y4_3_aizv,
    Y4_4_atvērt,
    Y4_4_aizv,
    Y5_1_atvērt,
    Y5_1_aizv,
    Y5_2_atvērt,
    Y5_2_aizv,
    Y5_3_atvērt,
    Y5_3_aizv,
    Y5_4_atvērt,
    Y5_4_aizv,
    Y6_1_atvērt,
    Y6_1_aizv,
    Y6_2_atvērt,
    Y6_2_aizv,

};

enum a3DOut
{
};

enum virtualOutputs
{

    set_mix_speed = MAX_DIoutput - VIRUAL_PORTS,
    set_mix_On_Off,

    //set_dispax_On_Off,


    // set_pump2_2_On_Off_FW = 4,              set_pump2_2_On_Off_rw = 0
    //set_dispax_On_Off = 5,
    set_dispax_speed  ,

    set_pump1_speed,
    set_dino0_speed,
    set_dino0_On_Off,

    pipe_dir0,
    pipe_dir1,
    pipe_dir2,
    pipe_dir3,
    pipe_dir4,
    pipe_dir5,
    pipe_dir6,
    pipe_dir7,
    pipe_dir8,
    pipe_dir9,
    pipe_dir10,
    pipe_dir11,
    pipe_dir12,
    pipe_dir13,
    pipe_dir14,
    pipe_dir15,
    pipe_dir16,
    pipe_dir17,
    pipe_dir18,
    pipe_dir19,
    pipe_dir20,
    pipe_dir21,
    pipe_dir22,
    pipe_dir23,
    pipe_dir24,
    pipe_dir25,
    pipe_dir26,
    pipe_dir27,
    pipe_dir28,
    pipe_dir29,
    pipe_dir30,
    pipe_dir31,
    pipe_dir32,
    pipe_dir33,
    pipe_dir34,
    pipe_dir35,
    pipe_dir36,
    pipe_dir37,
    pipe_dir38,
    pipe_dir39,
    pipe_dir40,
    pipe_dir41,
    pipe_dir42,
    pipe_dir43,
    pipe_dir44,
    pipe_dir45,
    pipe_dir46,
    pipe_dir47,
    pipe_dir48,
    pipe_dir49,
    pipe_dir50,
    pipe_dir51,
    pipe_dir52,
    pipe_dir53,
    pipe_dir54,
    pipe_dir55,
    pipe_dir56,
    pipe_dir57,
    pipe_dir58,
    pipe_dir59,
    pipe_dir60,
    pipe_dir61,
    pipe_dir62,
    pipe_dir63,
    pipe_dir64,
    pipe_dir65,
    pipe_dir66,
    pipe_dir67,
    pipe_dir68,
    pipe_dir69,
    pipe_dir70,
    pipe_dir71,
    pipe_dir72,
    pipe_dir73,
    pipe_dir74,
    pipe_dir75,
    pipe_dir76,
    pipe_dir77,
    pipe_dir78,
    pipe_dir79,
    pipe_dir80,
    pipe_dir81,
    pipe_dir82,
    pipe_dir83,
    pipe_dir84,
    pipe_dir85,
    pipe_dir86,

};

//QStringList   pipeItems;
//   pipeItems << "pipe_dir0";

/*

  << "pipe_dir0"
    << " pipe_dir1 " ;




   " pipe_dir2" +
   " pipe_dir3" +
   " pipe_dir4" +
    "pipe_dir5" +
    "pipe_dir6" +
    "pipe_dir7" +
    "pipe_dir8,
    "pipe_dir9,
    "pipe_dir10,
    "pipe_dir11,
    "pipe_dir12,
    "pipe_dir13,
    "pipe_dir14,
    "pipe_dir15,
    "pipe_dir16,
    "pipe_dir17,
    "pipe_dir18,
    "pipe_dir19,
    "pipe_dir20,
    "pipe_dir21,
    "pipe_dir22,
    "pipe_dir23,
    "pipe_dir24,
    "pipe_dir25,
    "pipe_dir26,
    "pipe_dir27,
    "pipe_dir28,
    "pipe_dir29,
    "pipe_dir30,
    "pipe_dir31,
    "pipe_dir32,
    "pipe_dir33,
    "pipe_dir34,
    "pipe_dir35,
    "pipe_dir36,
    "pipe_dir37,
    "pipe_dir38,
    "pipe_dir39,
    "pipe_dir40,
    "pipe_dir41,
    "pipe_dir42,
    "pipe_dir43,
    "pipe_dir44,
    "pipe_dir45,
    "pipe_dir46,
    "pipe_dir47,
    "pipe_dir48,
    "pipe_dir49,
    "pipe_dir50,
    "pipe_dir51,
    "pipe_dir52,
    "pipe_dir53,
    "pipe_dir54,
    "pipe_dir55,
    "pipe_dir56,
    "pipe_dir57,
    "pipe_dir58,
    "pipe_dir59,
    "pipe_dir60,
    "pipe_dir61,
    "pipe_dir62,
    "pipe_dir63,
    "pipe_dir64,
    "pipe_dir65,
    "pipe_dir66,
    "pipe_dir67,
    "pipe_dir68,
    "pipe_dir69,
    pipe_dir70";



*/



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
/*
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
*/
#define LEVEL_SENSOR_1   101
#define LEVEL_SENSOR_2   102
#define LEVEL_SENSOR_3   103
#define TEMP_SENSOR_1   104
#define TEMP_SENSOR_2   105


class Def {
public:
    Def();
    // QStringList   pipeItems;
};


#endif // DEF_H
