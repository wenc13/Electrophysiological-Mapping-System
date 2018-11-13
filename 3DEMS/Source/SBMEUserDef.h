#ifndef SBMEUSERDEF_H
#define SBMEUSERDEF_H

#include <QMutex>
#include <QWaitCondition>
#include "SBMEMacroDefinition.h"
#include "Usb2805.h"

//ECG
//extern bool   sbme_bThreadECGFlagAcq;
//extern bool   sbme_bThreadECGFlagPro;
extern float  sbme_ThreadECGfloat[SBME_MAX_CHANNEL_COUNT][16];

extern QMutex sbme_ThreadECGMutex;
extern QWaitCondition sbme_ThreadECGWaitCondition;
//extern QWaitCondition sbme_ThreadECGAcqWaitCondition;
//extern QWaitCondition sbme_ThreadECGProWaitCondition;

//extern int    sbme_nReadIndex;
extern int    sbme_nSegmentCounts;
//extern int    sbme_nProSegmentCounts;
extern WORD   sbme_ADBuffer[SBME_MAX_SEGMENT_COUNT][32768];

//NDI
extern bool   sbme_bStopTracking;
extern QMutex sbme_ThreadNDIMutex;

#endif // SBMEUSERDEF_H
