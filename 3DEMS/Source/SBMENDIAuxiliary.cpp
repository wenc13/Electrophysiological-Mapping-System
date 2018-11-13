//#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include "SBMENDIAuxiliary.h"

static unsigned int CrcTable[256];
static int bFirst = 1;

void InitCrcTable()
{
    int i, j;
    long lCrcTable;
    for (i = 0; i < 256; i++)
    {
        lCrcTable = i;
        for (j = 0; j < 8; j++)
            lCrcTable = (lCrcTable >> 1) ^ ((lCrcTable & 1) ? 0xA001L : 0);
        CrcTable[i] = (unsigned int) lCrcTable & 0xFFFF;
    }
}

unsigned int CalcCrc16(unsigned int crc, int data)
{
    if (bFirst)
    {
        bFirst = 0;
        InitCrcTable();
    }
    crc = CrcTable[(crc ^ data) & 0xFF] ^ (crc >> 8);
    return (crc & 0xFFFF);
}

unsigned int CalcCRCByLen(char *pszString, int nLen)
{
    static unsigned char oddparity[16] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
    unsigned data, uCrc = 0;
    unsigned char *puch = (unsigned char *)pszString;
    int	nCnt = 0;
    while (nCnt < nLen)
    {
        data = (*puch ^ (uCrc & 0xff)) & 0xff;
        uCrc >>= 8;

        if (oddparity[data & 0x0f] ^ oddparity[data >> 4])
        {
            uCrc ^= 0xc001;
        }
        data <<= 6;
        uCrc ^= data;
        data <<= 1;
        uCrc ^= data;
        puch++;
        nCnt++;
    }
    return uCrc;
}

unsigned int SystemGetCRC(char *psz, int nLength)
{
	unsigned int
		uCrc = 0;
	int
		m = 0;

	for (m = 0; m<(nLength); m++)
	{
		uCrc = CalcCrc16(uCrc, psz[m]);
	}

	return uCrc;
}

int SystemCheckCRC(char *psz)
{
    unsigned int uCrc = 0;
    unsigned int uReplyCrc = 0;
    unsigned int uReplySize = 0;
    int	m, n;
    uCrc = 0;

    if (((psz[0] & 0xff) == 0xc4) && ((psz[1] & 0xff) == 0xa5))
    {
        uReplyCrc = (psz[4] & 0xff) | ((psz[5] & 0xff) << 8);
        if (CalcCRCByLen(psz, 4) == uReplyCrc)
        {
            uReplySize = ((psz[2] & 0xff) | ((psz[3] & 0xff) << 8)) + 8;
            uReplyCrc  = (psz[uReplySize - 2] & 0xff) | ((psz[uReplySize - 1] & 0xff) << 8);
            if (CalcCRCByLen(&psz[6], (uReplySize - 8)) == uReplyCrc)
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    else
    {
        for (n = 0; (psz[n] != CARRIAGE_RETURN) && (n < MAX_REPLY_MSG); n++)
        {
            ;
        }
        if (n >= MAX_REPLY_MSG)
            return 0;
        psz[n + 1] = 0;
        for (m = 0; m < (n - 4); m++)
            uCrc = CalcCrc16(uCrc, psz[m]);
        sscanf(&(psz[n - 4]), "%04x", &uReplyCrc);
        return (uCrc == uReplyCrc);
    }
}

bool bAddCRCToCommand(char *pszCommandString)
{
    int m, n;
    unsigned int uCrc;
    bool bFirstSpace = false;
    
	n = strlen(pszCommandString);

    if (n >= (MAX_COMMAND_MSG - 6))
        return 0;

    uCrc = 0;
    for (m = 0; m < n; m++)
    {
        if (pszCommandString[m] == ' ' && !bFirstSpace)
        {
            pszCommandString[m] = ':';
            bFirstSpace = true;
        }
        uCrc = CalcCrc16(uCrc, pszCommandString[m]);
    }
    sprintf(&pszCommandString[n], "%04X", uCrc);
	n += 4;

    return 1;
}

bool bAddCRToCommand(char *pszCommandString)
{
    int n = strlen(pszCommandString);

    if (n >= (MAX_COMMAND_MSG - 1))
        return 0;

    pszCommandString[n] = CARRIAGE_RETURN;
    pszCommandString[n+1] = '\0';

    return 1;
}

bool bBuildCommand(char *pszCommandString, bool bAddCRC)    //ÐÞ¸ÄÓÚ2015/04/19
{
    int nCnt = 0;
	int nNumCR = 0;
    //int nNumCR = strlen(pszCommandString);

    for (nCnt = 0; nCnt < MAX_COMMAND_MSG; nCnt++)
    {
        if (pszCommandString[nCnt++] == CARRIAGE_RETURN)
        {
            pszCommandString[nCnt++] = '\0';
            return 1;
        }
    }
	
	/*for (nCnt = 0; nCnt < nNumCR; nCnt++)
    {
        if (pszCommandString[nCnt++] == CARRIAGE_RETURN)
        {
            pszCommandString[nCnt++] = '\0';
            return 1;
        }
    }*/
    if (bAddCRC)
        if (!bAddCRCToCommand(pszCommandString))
            return 0;

    if (!bAddCRToCommand(pszCommandString))
        return 0;

    return 1;
}

int nGetHex1(char *sz)
{
    unsigned int u;

    u=sz[0] & 0xff;

    return u;
} /* nGetHex1 */

int nGetHex2(char *sz)
{
    unsigned int u;

    u=sz[0] & 0xff;
    u|=((sz[1] & 0xFF) << 8);

    return u;
} /* nGetHex2 */

int nGetHex4(char *sz)
{
    unsigned int u;

    u=sz[0] & 0xff;
    u|=((sz[1] & 0xFF) << 8);
    u|=((sz[2] & 0xFF) << 16);
    u|=((sz[3] & 0xFF) << 24);

    return (int) u;
} /* nGetHex4 */

float fGetFloat(char *sz)
{
    float f;
    unsigned int *pu;

    pu =((unsigned int *)&f);

    (*pu)=sz[0] & 0xff;
    (*pu)|=((sz[1] & 0xFF) << 8);
    (*pu)|=((sz[2] & 0xFF) << 16);
    (*pu)|=((sz[3] & 0xFF) << 24);

    return f;
} /* fGetFloat */

unsigned int nASCIItoHexInt(char *szStr, int len)
{
    QString str(szStr);
    str.truncate(len);
    bool ok;
    return str.toInt(&ok, 16);
}

bool bExtractValue(char *pszVal, unsigned uLen, float fDivisor, float *pfValue)
{
    QString str(pszVal);
    str.truncate(uLen);
    bool ok;
    float fvalue = str.toFloat(&ok);
    if (ok)
        *pfValue = fvalue / fDivisor;
    return ok;
}

void CvtQuatToRotationMatrix(QuatRotation *pdtQuatRot, RotationMatrix dtRotMatrix)
{
    float fQ0Q0, fQxQx, fQyQy, fQzQz, fQ0Qx, fQ0Qy, fQ0Qz, fQxQy, fQxQz, fQyQz;
    fQ0Q0 = pdtQuatRot->q0 * pdtQuatRot->q0;
    fQxQx = pdtQuatRot->qx * pdtQuatRot->qx;
    fQyQy = pdtQuatRot->qy * pdtQuatRot->qy;
    fQzQz = pdtQuatRot->qz * pdtQuatRot->qz;
    fQ0Qx = pdtQuatRot->q0 * pdtQuatRot->qx;
    fQ0Qy = pdtQuatRot->q0 * pdtQuatRot->qy;
    fQ0Qz = pdtQuatRot->q0 * pdtQuatRot->qz;
    fQxQy = pdtQuatRot->qx * pdtQuatRot->qy;
    fQxQz = pdtQuatRot->qx * pdtQuatRot->qz;
    fQyQz = pdtQuatRot->qy * pdtQuatRot->qz;
    dtRotMatrix[0][0] = fQ0Q0 + fQxQx - fQyQy - fQzQz;
    dtRotMatrix[0][1] = 2.0 * (-fQ0Qz + fQxQy);
    dtRotMatrix[0][2] = 2.0 * (fQ0Qy + fQxQz);
    dtRotMatrix[1][0] = 2.0 * (fQ0Qz + fQxQy);
    dtRotMatrix[1][1] = fQ0Q0 - fQxQx + fQyQy - fQzQz;
    dtRotMatrix[1][2] = 2.0 * (-fQ0Qx + fQyQz);
    dtRotMatrix[2][0] = 2.0 * (-fQ0Qy + fQxQz);
    dtRotMatrix[2][1] = 2.0 * (fQ0Qx + fQyQz);
    dtRotMatrix[2][2] = fQ0Q0 - fQxQx - fQyQy + fQzQz;
}

void DetermineEuler(RotationMatrix dtRotMatrix, Rotation *pdtEulerRot)
{
    float fRoll, fCosRoll, fSinRoll;
    fRoll = atan2(dtRotMatrix[1][0], dtRotMatrix[0][0]);
    fCosRoll = cos(fRoll);
    fSinRoll = sin(fRoll);
    pdtEulerRot->fRoll  = fRoll;
    pdtEulerRot->fPitch = atan2(-dtRotMatrix[2][0], (fCosRoll * dtRotMatrix[0][0]) + (fSinRoll * dtRotMatrix[1][0]));
    pdtEulerRot->fYaw   = atan2((fSinRoll * dtRotMatrix[0][2]) - (fCosRoll * dtRotMatrix[1][2]),
                                (-fSinRoll * dtRotMatrix[0][1]) + (fCosRoll * dtRotMatrix[1][1]));
}

void CvtQuatToEulerRotation(QuatRotation *pdtQuatRot, Rotation *pdtEulerRot)
{
    RotationMatrix dtRotMatrix;
    CvtQuatToRotationMatrix(pdtQuatRot, dtRotMatrix);
    DetermineEuler(dtRotMatrix, pdtEulerRot);
    pdtEulerRot->fYaw   *= RAD_TO_DEGREES;
    pdtEulerRot->fPitch *= RAD_TO_DEGREES;
    pdtEulerRot->fRoll  *= RAD_TO_DEGREES;
}

void QuatRotatePoint(QuatRotation *RotationQuaternionPtr, Position3d *OriginalPositionPtr, Position3d *RotatedPositionPtr)
{
    Position3d UCrossV;
    if ((OriginalPositionPtr->x < MAX_NEGATIVE) || (OriginalPositionPtr->y < MAX_NEGATIVE) || (OriginalPositionPtr->z < MAX_NEGATIVE))
    {
        RotatedPositionPtr->x =  RotatedPositionPtr->y = RotatedPositionPtr->z = BAD_FLOAT;
        return;
    }
    UCrossV.x = RotationQuaternionPtr->qy * OriginalPositionPtr->z - RotationQuaternionPtr->qz * OriginalPositionPtr->y;
    UCrossV.y = RotationQuaternionPtr->qz * OriginalPositionPtr->x - RotationQuaternionPtr->qx * OriginalPositionPtr->z;
    UCrossV.z = RotationQuaternionPtr->qx * OriginalPositionPtr->y - RotationQuaternionPtr->qy * OriginalPositionPtr->x;
    RotatedPositionPtr->x = float(OriginalPositionPtr->x + 2.0 * (RotationQuaternionPtr->q0 * UCrossV.x + RotationQuaternionPtr->qy * UCrossV.z - RotationQuaternionPtr->qz * UCrossV.y));
    RotatedPositionPtr->y = float(OriginalPositionPtr->y + 2.0 * (RotationQuaternionPtr->q0 * UCrossV.y + RotationQuaternionPtr->qz * UCrossV.x - RotationQuaternionPtr->qx * UCrossV.z));
    RotatedPositionPtr->z = float(OriginalPositionPtr->z + 2.0 * (RotationQuaternionPtr->q0 * UCrossV.z + RotationQuaternionPtr->qx * UCrossV.y - RotationQuaternionPtr->qy * UCrossV.x));
}

void QuatInverseXfrm(QuatTransformation *pdtXfrm, QuatTransformation *pdtNewXfrm)
{
    pdtNewXfrm->rotation.q0 =  pdtXfrm->rotation.q0;
    pdtNewXfrm->rotation.qx = -pdtXfrm->rotation.qx;
    pdtNewXfrm->rotation.qy = -pdtXfrm->rotation.qy;
    pdtNewXfrm->rotation.qz = -pdtXfrm->rotation.qz;
    QuatRotatePoint(&pdtNewXfrm->rotation, &pdtXfrm->translation, &pdtNewXfrm->translation);
    pdtNewXfrm->translation.x = -pdtNewXfrm->translation.x;
    pdtNewXfrm->translation.y = -pdtNewXfrm->translation.y;
    pdtNewXfrm->translation.z = -pdtNewXfrm->translation.z;
}

void QuatCombineXfrms(QuatTransformation *pdtXfrm12, QuatTransformation *pdtXfrm23, QuatTransformation *pdtXfrm13)
{
    QuatRotation *pdtQ12 = &pdtXfrm12->rotation;
    QuatRotation *pdtQ23 = &pdtXfrm23->rotation;
    QuatRotation *pdtQ13 = &pdtXfrm13->rotation;
    float fA, fB, fC, fD, fE, fF, fG, fH;
    fA = ( pdtQ23->q0 + pdtQ23->qx ) * ( pdtQ12->q0 + pdtQ12->qx );
    fB = ( pdtQ23->qz - pdtQ23->qy ) * ( pdtQ12->qy - pdtQ12->qz );
    fC = ( pdtQ23->qx - pdtQ23->q0 ) * ( pdtQ12->qy + pdtQ12->qz );
    fD = ( pdtQ23->qy + pdtQ23->qz ) * ( pdtQ12->qx - pdtQ12->q0 );
    fE = ( pdtQ23->qx + pdtQ23->qz ) * ( pdtQ12->qx + pdtQ12->qy );
    fF = ( pdtQ23->qx - pdtQ23->qz ) * ( pdtQ12->qx - pdtQ12->qy );
    fG = ( pdtQ23->q0 + pdtQ23->qy ) * ( pdtQ12->q0 - pdtQ12->qz );
    fH = ( pdtQ23->q0 - pdtQ23->qy ) * ( pdtQ12->q0 + pdtQ12->qz );
    pdtQ13->q0 =  float (fB + ( -fE - fF + fG + fH ) / 2.0);
    pdtQ13->qx =  float (fA - (  fE + fF + fG + fH ) / 2.0);
    pdtQ13->qy = float (-fC + (  fE - fF + fG - fH ) / 2.0);
    pdtQ13->qz = float (-fD + (  fE - fF - fG + fH ) / 2.0);
    QuatRotatePoint(&pdtXfrm23->rotation, &pdtXfrm12->translation, &pdtXfrm13->translation);
    pdtXfrm13->translation.x += pdtXfrm23->translation.x;
    pdtXfrm13->translation.y += pdtXfrm23->translation.y;
    pdtXfrm13->translation.z += pdtXfrm23->translation.z;
}
