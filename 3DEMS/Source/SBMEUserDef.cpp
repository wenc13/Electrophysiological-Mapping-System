#include "SBMEUserDef.h"

//ECG
//bool   sbme_bThreadECGFlagAcq;
//bool   sbme_bThreadECGFlagPro;
float  sbme_ThreadECGfloat[SBME_MAX_CHANNEL_COUNT][16];

QMutex sbme_ThreadECGMutex;
QWaitCondition sbme_ThreadECGWaitCondition;
//QWaitCondition sbme_ThreadECGAcqWaitCondition;
//QWaitCondition sbme_ThreadECGProWaitCondition;

//int    sbme_nReadIndex = 0;
int    sbme_nSegmentCounts;
//int    sbme_nProSegmentCounts;
WORD   sbme_ADBuffer[SBME_MAX_SEGMENT_COUNT][32768];

//NDI
bool   sbme_bStopTracking = true;
QMutex sbme_ThreadNDIMutex;
