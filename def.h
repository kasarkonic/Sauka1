#ifndef DEF_H
#define DEF_H

//#include "qtypes.h"
//#include <QString>
//#include <QList>


//for testing
//#define ENABLE_WIDGET_SIZE


#define DIOUT(adr,val)  global.DIoutput[adr].value = val; global.DIoutput[adr].update = true;


// define rive adress
#define M8 18
#define M9 19   // ??
#define M10 20  // ??

// defines drive registers
#define CMD_REG  8501   // command reg
#define LFR_REG  8502   // set frequence
#define LFRD_REG 8602   // set rpm
#define ETA_REG  3201   // drive status
#define RFRD_REG 8604   // output velocyty
#define ERRD 8606   //CiA402 fault code  see error code table  driveErrorCodes[]
#define STOS    15322   // STO status

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




/*
 struct drError_code{
    int code;
    const char *name;
};

 drError_code driveErrorCodes[] = {

    {0x0000,	"[No fault] (NOF)	No fault saved"},
    {0x1000,	"[Precharge] (CRF1)	Precharge"},
    {0x1000,	"[Motor overload] (OLF)	Motor overload fault"},
    {0x1000,	"[Overspeed] (SOF)	Motor overspeed fault"},
    {0x1000,	"[IGBT desaturation] (HDF)	IGBT desaturation"},
    {0x1000,	"[internal- CPU ] (INFE)	internal- CPU"},
    {0x1000,	"[Ch.sw. fault] (CSF)	Channel switching fault"},
    {0x1000,	"[Angle error] (ASF)	Angle error"},
    {0xffff,    "last"}
    };
*/
class Def{
    Def();


// Drive fault coder  ERRD = 8606;
/*
16#0000	[No fault] (NOF)	No fault saved
    16#1000	[Precharge] (CRF1)	Precharge
    16#1000	[Motor overload] (OLF)	Motor overload fault
    16#1000	[Overspeed] (SOF)	Motor overspeed fault
    16#1000	[IGBT desaturation] (HDF)	IGBT desaturation
    16#1000	[internal- CPU ] (INFE)	internal- CPU
    16#1000	[Ch.sw. fault] (CSF)	Channel switching fault
    16#1000	[Angle error] (ASF)	Angle error
    16#2230	[IGBT short circuit] (SCF4)	IGBT short circuit fault
    16#2310	[Overcurrent] (OCF)	Overcurrent fault
    16#2311	[Proc.Overload Flt] (OLC)	Process Overload Fault
    16#2320	[Motor short circuit] (SCF1)	Motor short circuit
    16#2320	[Motor short circuit] (SCF5)	motor short circuit
    16#2330	[Ground short circuit] (SCF3)	Ground short circuit
    16#3110	[Mains overvoltage] (OSF)	Supply overvoltage fault
    16#3120	[Undervoltage] (USF)	Supply undervolt fault
    16#3130	[Input phase loss] (PHF)	Supply phase loss fault
    16#3310	[Overbraking] (OBF)	DC bus overvoltage fault
    16#3310	[1 output phase loss] (OPF1)	1 motor phase loss fault
    16#3310	[3out ph loss] (OPF2)	3 motor phase loss fault
    16#4210	[Drive overheat] (OHF)	Drive overheating fault
    16#4210	[IGBT overheat] (TJF)	IGBT overheat fault
    16#4310	[PTC fault] (OTFL)	LI6=PTC overheat fault
      16#5000	[Out. contact. stuck] (FCF1)	Output cont close fault
      16#5000	[Out. contact. open.] (FCF2)	Output cont open fault
      16#5000	[input contactor] (LCF)	input contactor
      16#5210	[Internal- I measure] (INF9)	Internal I measure fault
      16#5210	[Internal-mains circuit] (INFA)	Internal i/p volt circuit flt
        16#5210	[Internal- th. sensor] (INFB)	Internal temperature fault
        16#5530	[Control Eeprom] (EEF1)	EEprom control fault
        16#5530	[Power Eeprom] (EEF2)	EEprom power fault
        16#6100	[Rating error] (INF1)	Rating error
        16#6100	[PWR Calib.] (INF2)	Incompatible control card
        16#6100	[Int.serial link] (INF3)	Internal coms link fault
        16#6100	[Int.Mfg area] (INF4)	Internal manu zone fault
        16#6100	[Cards pairing] (HCF)	Cards pairing
        16#6300	[Incorrect config.] (CFF)	Incorrect configuration
        16#6300	[Invalid config.] (CFI)	Invalid config parameters
        16#6300	[Bad conf] (CFI2)	Interrupted config.
        16#7000	[Internal-option] (INF6)	Internal option fault
        16#7110	[Brake feedback] (BRF)	Brake feedback fault
        16#7300	[Load slipping] (ANF)	Output speed <> ref
        16#7300	[LI6=PTC probe] (PTFL)	LI6=PTC failed
      16#7300	[AI3 4-20mA loss] (LFF3)	AI3 4-20mA loss
      16#7310	[Speed fdback loss] (SPF)	Speed feedback loss
      16#7400	[FB fault] (FBE)	FB fault
      16#7400	[FB stop flt.] (FBES)	FB stop fault
      16#7510	[Modbus com.] (SLF1)	Modbus coms fault
      16#7510	[HMI com.] (SLF3)	HMI coms fault
      16#7520	[int. com.link] (ILF)	Com Internal link fault
      16#7520	[Com. network] (CNF)	Network fault
      16#7530	[PC com.] (SLF2)	PC coms fault
      16#8100	[CAN com.] (COF)	Comms fault CANopen
      16#9000	[External flt-LI/Bit] (EPF1)	External fault logic input
      16#9000	[External fault com.] (EPF2)	External fault comms
      16#FF00	[Auto-tuning ] (TNF)	Auto-tuning fault
            16#FF01	[Brake control] (BLF)	Brake control fault
            16#FF02	[Torque/current lim] (SSF)	Torque/current limit fault
            16#FF03	[Pr.Underload.Flt] (ULF)	Process Underlaod Fault
            16#FF03	[Safety fault] (SAFF)	Safety fault
            16#FF80	[Load fault] (DLF)	Dynamic load fault

*/



private:
 //   QString    getDriveErrorTxt(int errCode);


};

#endif // DEF_H
