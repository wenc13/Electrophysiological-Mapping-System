#ifndef SBMENDIDEF_H
#define SBMENDIDEF_H

#define MODE_PRE_INIT		0x01
#define MODE_INIT			0x02
#define MODE_TRACKING		0x03
#define MODE_ACTIVATED		0x04

#define NO_HANDLES			0xFF
#define POLARIS_SYSTEM		1
#define AURORA_SYSTEM		2
#define ACCEDO_SYSTEM		3
#define VICRA_SYSTEM		4
#define SPECTRA_SYSTEM	    5

#define REPLY_ERROR				0x00
#define REPLY_OKAY				0x01
#define REPLY_RESET				0x02
#define REPLY_OTHER				0x04
#define REPLY_BADCRC			0x08
#define REPLY_WARNING			0x10
#define REPLY_INVALID			0x20

#define CARRIAGE_RETURN			0xD
#define MAX_REPLY_MSG			4096
#define MAX_COMMAND_MSG			1024
#define MAX_COM_BUFFER          10000
#define LINE_FEED    			0xA

#define TRANSFORM_VALID			0x0000
#define	TRANSFORM_MISSING		0x1000
#define TRANSFORM_UNOCCUPIED	0x2000
#define TRANSFORM_DISABLED		0x3000
#define TRANSFORM_ERROR			0x4000

#define BAD_FLOAT    (float)-3.697314E28
#define MAX_NEGATIVE (float)-3.0E28
#define RAD_TO_DEGREES  (180 / 3.1415926)

typedef struct Position3dStruct
{
    float x;
    float y;
    float z;
} Position3d;

typedef struct QuatRotationStruct
{
    float q0;
    float qx;
    float qy;
    float qz;
} QuatRotation;

typedef struct QuatTransformationStruct
{
    QuatRotation rotation;
    Position3d   translation;
} QuatTransformation;

typedef float RotationMatrix[3][3];

typedef struct Rotation
{
    float fRoll;     /* rotation about the object's z-axis (Euler angle) */
    float fPitch;    /* rotation about the object's y-axis (Euler angle) */
    float fYaw;      /* rotation about the object's x-axis (Euler angle) */
} Rotation;

typedef struct
{
    unsigned long ulFlags;
    unsigned long ulFrameNumber;
    QuatRotation rotation;
    Position3d translation;
    float fError;
} TransformInformation;

typedef struct
{
    int	bToolInPort;
    int	bGPIO1;
    int	bGPIO2;
    int	bGPIO3;
    int	bInitialized;
    int	bEnabled;
    int	bOutOfVolume;
    int	bPartiallyOutOfVolume;
    int	bDisturbanceDet;
    int	bSignalTooSmall;
    int	bSignalTooBig;
    int	bProcessingException;
    int	bHardwareFailure;
    int	bTIPCurrentSensing;
} HandleStatus;

/* Handle Information Structure */
typedef struct
{
    char szPhysicalPort[20];
    char szToolType[9];
    char szManufact[13];
    char szSerialNo[9];
    char szRev[4];
    char szChannel[3];
    char szPartNumber[21];
    TransformInformation Xfrms;
    HandleStatus HandleInfo;
} HandleInformation;

/*System Information Structure*/
typedef struct
{
    int nTypeofSystem;

    char szVersionInfo[1024];

    int	bActivePortsAvail;
    int	bPassivePortsAvail;
    int	bMultiVolumeParms;
    int	bTIPSensing;
    int	bActiveWirelessAvail;
    int	bMagneticPortsAvail;
    int	bFieldGeneratorAvail;

    /* POLARIS ONLY FIELDS */
    int	nNoActivePorts;
    int	nNoPassivePorts;
    int	nNoActTIPPorts;
    int	nNoActWirelessPorts;

    /* AURORA ONLY FIELDS */
    int	nNoMagneticPorts;
    int	nNoFGCards;
    int	nNoFGs;

    /* TRACKING INFORMATION */
    int	bCommunicationSyncError;
    int bTooMuchInterference;
    int bSystemCRCError;
    int bRecoverableException;
    int bHardwareFailure;
    int bHardwareChange;
    int bPortOccupied;
    int bPortUnoccupied;
    int bDiagnosticsPending;
    int bTemperatureOutOfRange;
} SystemInformation;

/*System Information Structure*/
/*typedef struct
{
    int	bFatalParamterFault;
    int	bSensorParameterFault;
    int	bMainVoltageFault;
    int	bSensorVoltageFault;
    int	bIlluminatorVoltageFault;
    int	bIlluminatorCurrentFault;
    int	bLeftSensorTempFault;
    int	bRightSensorTempFault;
    int	bMainBoardTempFault;
    int	bBatteryFaultAlarm;
    int	bBumpDetectedAlarm;
    int	bCableFaultAlarm;
    int	bFirmwareIncompatible;
    int	bNonFatalParamFault;
    int	bInternalFlashFull;
    int	bLaserBatteryFaultAlarm;
    int	bTempTooHigh;
    int	bTempTooLow;
} DiagNewAlertFlags;*/

#endif // SBMENDIDEF_H
