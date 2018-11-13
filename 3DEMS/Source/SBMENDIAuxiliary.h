#ifndef SBMENDIAUXILIARY_H
#define SBMENDIAUXILIARY_H

#include "SBMENDIDef.h"

void InitCrcTable();
unsigned int CalcCrc16(unsigned int crc, int data);
unsigned int CalcCRCByLen(char *pszString, int nLen);
unsigned int SystemGetCRC(char *psz, int nLength);
int  SystemCheckCRC(char *psz);
bool bAddCRCToCommand(char *pszCommandString);
bool bAddCRToCommand(char *pszCommandString);
bool bBuildCommand(char *pszCommandString, bool bAddCRC);

int   nGetHex1(char *sz);
int   nGetHex2(char *sz);
int   nGetHex4(char *sz);
float fGetFloat(char *sz);

unsigned int nASCIItoHexInt(char *szStr, int len);
bool bExtractValue(char *pszVal, unsigned uLen, float fDivisor, float *pfValue);
void CvtQuatToRotationMatrix(QuatRotation *pdtQuatRot, RotationMatrix dtRotMatrix);
void DetermineEuler(RotationMatrix dtRotMatrix, Rotation *pdtEulerRot);
void CvtQuatToEulerRotation(QuatRotation *pdtQuatRot, Rotation *pdtEulerRot);
void QuatRotatePoint(QuatRotation *RotationQuaternionPtr, Position3d *OriginalPositionPtr, Position3d *RotatedPositionPtr);
void QuatInverseXfrm(QuatTransformation *pdtXfrm, QuatTransformation *pdtNewXfrm);
void QuatCombineXfrms(QuatTransformation *pdtXfrm12, QuatTransformation *pdtXfrm23, QuatTransformation *pdtXfrm13);

#endif // SBMENDIAUXILIARY_H
