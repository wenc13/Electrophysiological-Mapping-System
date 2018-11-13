#include <QSerialPort.h>
#include "SBMENDIController.h"
#include "SBMENDIAuxiliary.h"

//测试代码
#include <QDebug>
#include <iostream>
//测试代码

//修改于2015/05/13
//SBMENDIController::SBMENDIController(QWidget *parent) :
    //QWidget(parent)
SBMENDIController::SBMENDIController() :
    QObject()
{
    m_pSettings     = new QSettings("NDISettings.ini", QSettings::IniFormat);
    m_pErrorIniFile = new QSettings("NDIErrors.ini", QSettings::IniFormat);
    ReadSettings();

    //m_pSerialPortSettingsDlg = new SBMENDISerialPortSettingsDlg;
    //m_pSystemFeaturesDlg     = new SBMENDISystemFeaturesDlg;

    m_pSerialPort = new QSerialPort(this);
    //m_pSerialPort->setPortName(m_pSerialPortSettingsDlg->portName);
	m_pSerialPort->setPortName(m_pSettings->value("/Communication/COM Port Name", "").toString());
    
	m_ComBuffer = SBMESerialPortBuffer<char>(MAX_COM_BUFFER, 0);
    
	m_bSerialPortOpened       = false;
	m_bIsNewPortsActiveFailed = false;
    m_nSerialBreakDelay       = 256;

	m_nTrackingMode           = 0;
	m_nTimeOutChoose          = -1;

	//m_nNumBytes = 0;
	//m_nIndexBuffer = 0;

	m_nTimeout = 3;
	m_nRefHandle = -1;

	GetComParms();

	//测试代码
	temp = 0;
	//测试代码
}

SBMENDIController::~SBMENDIController()
{
}

void SBMENDIController::AutoConnect()
{
    /*if (m_bIsAtuoConnect)
    {
        if (m_pSerialPortSettingsDlg->Settings().NDIComIndex != -1)
        {
            if (InitializeSystem())
                emit m_signalNDIAutoInitialized();
        }
    }*/
}

void SBMENDIController::SetAutoConnect(bool isAutoConnect)
{
    m_pSettings->setValue("/Communication/AutoConnect", isAutoConnect);
}

void SBMENDIController::SetCommPort()
{
    //m_pSerialPortSettingsDlg->show();
}

void SBMENDIController::SetProgramOptions()
{
    /*
	//原始代码
	SBMENDIProgramOptionDlg *m_pNDIProgramOptionDlg = new SBMENDIProgramOptionDlg;
    if (m_pNDIProgramOptionDlg)
    {
        if (m_pNDIProgramOptionDlg->exec())
            delete m_pNDIProgramOptionDlg;
    }
	*/
	//emit m_signalSetProgramOptions();
}

void SBMENDIController::ViewSystemFeatures()
{
    /*SBMENDISystemFeaturesDlg *m_pSystemFeaturesDlg = new SBMENDISystemFeaturesDlg;
	if (m_pSystemFeaturesDlg == NULL)
		return;
	if (m_dtSystemInformation.nTypeofSystem != AURORA_SYSTEM)
    {
        m_pSystemFeaturesDlg->SetVariables(m_dtSystemInformation.szVersionInfo,
                                           m_dtSystemInformation.nNoActivePorts,
                                           m_dtSystemInformation.nNoPassivePorts,
                                           m_dtSystemInformation.nNoActWirelessPorts,
                                           m_dtSystemInformation.nNoActTIPPorts);
    }
    else
    {

        m_pSystemFeaturesDlg->SetVariables(m_dtSystemInformation.szVersionInfo,
                                           m_dtSystemInformation.nNoMagneticPorts,
                                           m_dtSystemInformation.nNoFGs,
                                           m_dtSystemInformation.nNoFGCards);
    }
    if(m_pSystemFeaturesDlg->exec())
		delete m_pSystemFeaturesDlg;*/
}

bool SBMENDIController::ResetSystem()
{
    m_bResetHardware = m_pSettings->value("/Communication/Reset Hardware", 0).toBool();
    m_bWireless = m_pSettings->value("/Communication/Wireless", 0).toBool();

	bCloseCurrentComport();
    if (bOpenComport())
    {
        if (m_bResetHardware)
        {
            if (!bHardWareReset(m_bWireless))
                return false;
            if (!bSetSystemComParms(0, 0, 0, 0, 0))
                return false;
        }
        return true;
    }
    else
        return false;
}

bool SBMENDIController::InitializeSystem()
{
    m_bResetHardware = m_pSettings->value("/Communication/Reset Hardware", 0).toBool();
    m_bWireless = m_pSettings->value("/Communication/Wireless", 0).toBool();

    bCloseCurrentComport();
	if (bOpenComport())
    {
        if (m_bResetHardware)
        {
            if (!bHardWareReset(m_bWireless))
                return false;
        }
        if (!bCreateTimeoutTable())
            return false;
        //GetComParms();
        if (!bSetSystemComParms(m_nBaudRate, m_nDataBits, m_nParity, m_nStopBits, m_nFlowControl))
            return false;
		
        if (bInitializeSystem())
        {
            if(!bGetSystemInfo())
            {
                //修改于2015/05/13
				/*QMessageBox::warning(NULL, "INIT ERROR","Could not determine type of system\n"
                                     "(Polaris, Polaris Accedo, Polaris Vicra or Aurora)",
                                     QMessageBox::Ok );*/
				emit m_signalInitErrorDetermineSystemType();
                return false;
            }
            if (m_dtSystemInformation.nTypeofSystem != AURORA_SYSTEM)
            {
                bSetFiringRate();
            }
            return true;
        }
        else
        {
            //修改于2015/05/13
			/*QMessageBox::critical(NULL, "INIT ERROR","System could not be initialized.\n "
                                  "Check your COM Port settings, make sure your\n"
                                  "system is turned on and the system components are compatible.",
                                  QMessageBox::Ok );*/
			emit m_signalInitErrorInitializeSystem();
            return false;
        }
    }
}

bool SBMENDIController::bEnableHandle(int nHandle)
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PENA %02X%c", nHandle, 'D');
    if (!bSendCommand( m_szCommand, TRUE))
        return 0;
    if (!bGetResponse())
        return 0;
    if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
        return 0;
    bGetHandleInformation(nHandle);
    return 1;
}

bool SBMENDIController::bDisableHandle(int nHandle)
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PDIS %02X", nHandle);
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
        {
            bGetHandleInformation(nHandle);
            return 1;
        }
    }
    else
        return 0;
}

bool SBMENDIController::bActivateAllHandles()
{
    if (!bFreeAllHandles())
        return 0;
    if (!bInitializeAllHandles())
        return 0;
    if (!bEnableAllHandles())
        return 0;
    return true;
}

bool SBMENDIController::bStartTracking()
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "TSTART ");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse( nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        return 1;
    }
    else
        return 0;
}

bool SBMENDIController::bGetTXTransforms()
{
    int nReplyMode = 0x0001;
    int nNoHandles = 0;
    int nHandle    = 0;
    int nRet       = 0;
    
	unsigned int unHandleStatus = 0;
    unsigned int unSystemStatus = 0;
    
	bool bDisabled = FALSE;
    
	char *pszTransformInfo = NULL;
    
	nReplyMode = m_bReportOutOfVolume ? 0x0801 : 0x0001;
    
	memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "TX %04X", nReplyMode);
    
	if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (m_bDisplayErrorsWhileTracking)
        {
            //测试代码
			//QString str1 = ;

			/*int a = nVerifyResponse(m_szLastReply, TRUE);
			int b = a;
			
			if (a == 4)
				temp = temp + 1;
			int c = temp;
			
			if (a == 0x08)
			{
				temp = 0;
				QMessageBox msgBox;
                msgBox.setText(m_szLastReply);
                msgBox.exec();
			}
			if (!bCheckResponse(a))
                return 0;*/
			//测试代码
			
			if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
        }
        else
        {
            if (!nVerifyResponse(m_szLastReply, FALSE))
                return 0;
        }
        pszTransformInfo = m_szLastReply;
        
		nNoHandles = nASCIItoHexInt(pszTransformInfo, 2);
        pszTransformInfo += 2;
        
		for (int i = 0; i < nNoHandles; i++)
        {
            nHandle = nASCIItoHexInt(pszTransformInfo, 2);
            pszTransformInfo += 2;
            bDisabled = FALSE;
            
			if (strlen(pszTransformInfo ) < 18)
                return 0;
            
			if (!strncmp(pszTransformInfo, "MISSING", 7) ||
                !strncmp(pszTransformInfo, "DISABLED", 8) ||
                !strncmp(pszTransformInfo, "UNOCCUPIED", 10))
            {
                if (!strncmp(pszTransformInfo, "UNOCCUPIED", 10))
                {
                    m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_UNOCCUPIED;
                    pszTransformInfo += 10;
                    bDisabled = TRUE;
                }
                else if (!strncmp(pszTransformInfo, "DISABLED", 8))
                {
                    m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_DISABLED;
                    pszTransformInfo += 8;
                    bDisabled = TRUE;
                }
                else
                {
                    m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_MISSING;
                    pszTransformInfo += 7;
                }
                m_dtHandleInformation[nHandle].Xfrms.rotation.q0   =
                m_dtHandleInformation[nHandle].Xfrms.rotation.qx   =
                m_dtHandleInformation[nHandle].Xfrms.rotation.qy   =
                m_dtHandleInformation[nHandle].Xfrms.rotation.qz   =
                m_dtHandleInformation[nHandle].Xfrms.translation.x =
                m_dtHandleInformation[nHandle].Xfrms.translation.y =
                m_dtHandleInformation[nHandle].Xfrms.translation.z =
                m_dtHandleInformation[nHandle].Xfrms.fError        = BAD_FLOAT;
            }
            else
            {
                m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_VALID;

                if (!bExtractValue(pszTransformInfo,      6, 10000., &m_dtHandleInformation[nHandle].Xfrms.rotation.q0)   ||
                    !bExtractValue(pszTransformInfo + 6,  6, 10000., &m_dtHandleInformation[nHandle].Xfrms.rotation.qx)   ||
                    !bExtractValue(pszTransformInfo + 12, 6, 10000., &m_dtHandleInformation[nHandle].Xfrms.rotation.qy)   ||
                    !bExtractValue(pszTransformInfo + 18, 6, 10000., &m_dtHandleInformation[nHandle].Xfrms.rotation.qz)   ||
                    !bExtractValue(pszTransformInfo + 24, 7, 100.,   &m_dtHandleInformation[nHandle].Xfrms.translation.x) ||
                    !bExtractValue(pszTransformInfo + 31, 7, 100.,   &m_dtHandleInformation[nHandle].Xfrms.translation.y) ||
                    !bExtractValue(pszTransformInfo + 38, 7, 100.,   &m_dtHandleInformation[nHandle].Xfrms.translation.z) ||
                    !bExtractValue(pszTransformInfo + 45, 6, 10000., &m_dtHandleInformation[nHandle].Xfrms.fError))
                {
                    m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_MISSING;
                    return 0;
                }
                else
                    pszTransformInfo += 51;
            }
            if (!bDisabled)
            {
                unHandleStatus = nASCIItoHexInt(pszTransformInfo, 8);
                pszTransformInfo += 8;
                m_dtHandleInformation[nHandle].HandleInfo.bToolInPort           = (unHandleStatus & 0x01   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bGPIO1                = (unHandleStatus & 0x02   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bGPIO2                = (unHandleStatus & 0x04   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bGPIO3                = (unHandleStatus & 0x08   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bInitialized          = (unHandleStatus & 0x10   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bEnabled              = (unHandleStatus & 0x20   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bOutOfVolume          = (unHandleStatus & 0x40   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bPartiallyOutOfVolume = (unHandleStatus & 0x80   ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bDisturbanceDet       = (unHandleStatus & 0x200  ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bSignalTooSmall       = (unHandleStatus & 0x400  ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bSignalTooBig         = (unHandleStatus & 0x800  ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bProcessingException  = (unHandleStatus & 0x1000 ? 1 : 0);
                m_dtHandleInformation[nHandle].HandleInfo.bHardwareFailure      = (unHandleStatus & 0x2000 ? 1 : 0);

                m_dtHandleInformation[nHandle].Xfrms.ulFrameNumber = nASCIItoHexInt(pszTransformInfo, 8);
                pszTransformInfo += 8;
            }
            pszTransformInfo++;
        }
        unSystemStatus = nASCIItoHexInt(pszTransformInfo, 4);
        m_dtSystemInformation.bCommunicationSyncError = (unSystemStatus & 0x01  ? 1 : 0);
        m_dtSystemInformation.bTooMuchInterference    = (unSystemStatus & 0x02  ? 1 : 0);
        m_dtSystemInformation.bSystemCRCError         = (unSystemStatus & 0x04  ? 1 : 0);
        m_dtSystemInformation.bRecoverableException   = (unSystemStatus & 0x08  ? 1 : 0);
        m_dtSystemInformation.bHardwareFailure        = (unSystemStatus & 0x10  ? 1 : 0);
        m_dtSystemInformation.bHardwareChange         = (unSystemStatus & 0x20  ? 1 : 0);
        m_dtSystemInformation.bPortOccupied           = (unSystemStatus & 0x40  ? 1 : 0);
        m_dtSystemInformation.bPortUnoccupied         = (unSystemStatus & 0x80  ? 1 : 0);
        m_dtSystemInformation.bDiagnosticsPending     = (unSystemStatus & 0x100 ? 1 : 0);
        m_dtSystemInformation.bTemperatureOutOfRange  = (unSystemStatus & 0x200 ? 1 : 0);

		ApplyXfrms();
        
		return 1;
    }
    else
        return 0;
}

bool SBMENDIController::bGetBXTransforms()
{
	int	nReplyMode = 0x0001;
	int	nReplySize = 0;
	int	nSpot      = 0;
	int	nNoHandles = 0;
	int	nHandle    = 0;
	int	nRet       = 0;

	unsigned int unSystemStatus = 0;
	unsigned int uTransStatus   = 0;
	unsigned int unHandleStatus = 0;
	unsigned int uHeaderCRC     = 0;
	unsigned int uBodyCRC       = 0;
	unsigned int uCalcCRC       = 0;
	
	char *pszTransformInfo = NULL;

	nReplyMode = m_bReportOutOfVolume ? 0x0801 : 0x0001;

	memset(m_szCommand, 0, sizeof(m_szCommand));
	sprintf(m_szCommand, "BX %04X", nReplyMode);

	if (bSendCommand(m_szCommand, TRUE))
	{
		if (!bGetBinaryResponse())
			return 0;

		if ( m_bDisplayErrorsWhileTracking )
		{
			if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
				return 0;
		}
		else
		{
			if (!nVerifyResponse( m_szLastReply, FALSE ))
				return 0;
		}

		pszTransformInfo = m_szLastReply;
		uCalcCRC = SystemGetCRC(m_szLastReply, 4 );

        while (((pszTransformInfo[0]&0xff) != 0xc4))
            pszTransformInfo++;

		if ((pszTransformInfo[0]&0xff) != 0xc4 || (pszTransformInfo[1]&0xff) != 0xa5)
			return REPLY_INVALID;

        nSpot+=2;
		nReplySize = nGetHex2(&pszTransformInfo[nSpot]);
        nSpot+=2;
		uHeaderCRC = nGetHex2(&pszTransformInfo[nSpot]);
        nSpot+=2;

		if (uCalcCRC != uHeaderCRC)
		{
			if (m_bDisplayErrorsWhileTracking)
				bCheckResponse( REPLY_BADCRC );
			return REPLY_BADCRC;
		}

		nNoHandles = nGetHex1(&pszTransformInfo[nSpot]);
		nSpot++;

		for (int i = 0; i < nNoHandles; i++)
		{
			nHandle = nGetHex1(&pszTransformInfo[nSpot]);
			nSpot++;

			uTransStatus = nGetHex1(&pszTransformInfo[nSpot]);
			nSpot++;

			if (uTransStatus == 1)
			{
				m_dtHandleInformation[nHandle].Xfrms.rotation.q0 = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.rotation.qx = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.rotation.qy = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.rotation.qz = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.translation.x = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.translation.y = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.translation.z = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.fError = fGetFloat(&pszTransformInfo[nSpot]);
				nSpot+=4;
				unHandleStatus = nGetHex4(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.ulFrameNumber = nGetHex4(&pszTransformInfo[nSpot]);
				nSpot+=4;
				m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_VALID;
			}

			if (uTransStatus == 2 || uTransStatus == 4)    //2 means the tool is missing and 4 means DISABLED
			{
				if (uTransStatus == 2)
				{
					unHandleStatus = nGetHex4(&pszTransformInfo[nSpot]);
					nSpot+=4;
					m_dtHandleInformation[nHandle].Xfrms.ulFrameNumber = nGetHex4(&pszTransformInfo[nSpot]);
					nSpot+=4;
					m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_MISSING;
				}
				else
					m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_DISABLED;

				m_dtHandleInformation[nHandle].Xfrms.rotation.q0   =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qx   =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qy   =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qz   =
				m_dtHandleInformation[nHandle].Xfrms.translation.x =
				m_dtHandleInformation[nHandle].Xfrms.translation.y =
				m_dtHandleInformation[nHandle].Xfrms.translation.z =
				m_dtHandleInformation[nHandle].Xfrms.fError = BAD_FLOAT;
			}

			if (uTransStatus == 1 || uTransStatus == 2)
			{
				m_dtHandleInformation[nHandle].HandleInfo.bToolInPort           = (unHandleStatus & 0x01   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bGPIO1                = (unHandleStatus & 0x02   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bGPIO2                = (unHandleStatus & 0x04   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bGPIO3                = (unHandleStatus & 0x08   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bInitialized          = (unHandleStatus & 0x10   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bEnabled              = (unHandleStatus & 0x20   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bOutOfVolume          = (unHandleStatus & 0x40   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bPartiallyOutOfVolume = (unHandleStatus & 0x80   ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bDisturbanceDet       = (unHandleStatus & 0x200  ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bSignalTooSmall       = (unHandleStatus & 0x400  ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bSignalTooBig         = (unHandleStatus & 0x800  ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bProcessingException  = (unHandleStatus & 0x1000 ? 1 : 0);
				m_dtHandleInformation[nHandle].HandleInfo.bHardwareFailure      = (unHandleStatus & 0x2000 ? 1 : 0);
			}
		}

		unSystemStatus = nGetHex2( &pszTransformInfo[nSpot] );
		nSpot+=2;
		uBodyCRC = nGetHex2(&pszTransformInfo[nSpot]);
		m_dtSystemInformation.bCommunicationSyncError = (unSystemStatus & 0x01  ? 1 : 0);
		m_dtSystemInformation.bTooMuchInterference    = (unSystemStatus & 0x02  ? 1 : 0);
		m_dtSystemInformation.bSystemCRCError         = (unSystemStatus & 0x04  ? 1 : 0);
		m_dtSystemInformation.bRecoverableException   = (unSystemStatus & 0x08  ? 1 : 0);
		m_dtSystemInformation.bHardwareFailure        = (unSystemStatus & 0x10  ? 1 : 0);
		m_dtSystemInformation.bHardwareChange         = (unSystemStatus & 0x20  ? 1 : 0);
		m_dtSystemInformation.bPortOccupied           = (unSystemStatus & 0x40  ? 1 : 0);
		m_dtSystemInformation.bPortUnoccupied         = (unSystemStatus & 0x80  ? 1 : 0);
		m_dtSystemInformation.bDiagnosticsPending     = (unSystemStatus & 0x100 ? 1 : 0);
		m_dtSystemInformation.bTemperatureOutOfRange  = (unSystemStatus & 0x200 ? 1 : 0);

		uCalcCRC = SystemGetCRC(pszTransformInfo+=6, nSpot-6 );
		if ( uCalcCRC != uBodyCRC )
		{
			bCheckResponse(REPLY_BADCRC);
			return REPLY_BADCRC;
		}

		ApplyXfrms();

	    return 1;
	}
	else
		return 0;
}

bool SBMENDIController::bStopTracking()
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "TSTOP ");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
		
		//测试代码
		QString str = m_szLastReply;
		QString str1 = str;
		//测试代码
        
		if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        return 1;
    }
    else return 0;
}

void SBMENDIController::FiringRate20Hz()
{
    m_pSettings->setValue("/POLARIS Options/Activation Rate", 0);
    bSetFiringRate();
}

void SBMENDIController::FiringRate30Hz()
{
    m_pSettings->setValue("/POLARIS Options/Activation Rate", 1);
    bSetFiringRate();
}

void SBMENDIController::FiringRate60Hz()
{
    m_pSettings->setValue("/POLARIS Options/Activation Rate", 2);
    bSetFiringRate();
}

void SBMENDIController::SetReferenceHandle(int referenceHandle)
{
	m_nRefHandle = referenceHandle;
}

int *SBMENDIController::GetEnnabledHandleIndex()
{
    return m_EnabledHandleIndex;
}

HandleInformation *SBMENDIController::GetHandleInformation()
{
    return m_dtHandleInformation;
}

SystemInformation *SBMENDIController::GetSystemInformation()
{
    return &m_dtSystemInformation;
}

void SBMENDIController::ReadSettings()
{
    m_bIsAtuoConnect              = m_pSettings->value("/Communication/AutoConnect", 1).toBool();
	m_bReportOutOfVolume          = m_pSettings->value("Reporting Options/Report While Tracking", true).toBool();
    m_bDisplayErrorsWhileTracking = m_pSettings->value("/Reporting Options/Report While Tracking", 1).toBool();
	m_bLogToFile                  = m_pSettings->value("/Logging Options/Log To File", 1).toBool();
	m_bClearLogFile               = m_pSettings->value("/Logging Options/Clear File", 1).toBool();
    m_bDateTimeStampFile          = m_pSettings->value("/Logging Options/Date Time Stamp", 1).toBool();

	m_nCOMPort                    = m_pSettings->value("/Communication/COM Port Index", 0).toInt();
    m_nTimeout                    = m_pSettings->value("/Communication/Timeout Time", 10).toInt();
	m_nDefaultTimeout             = m_pSettings->value("/Communication/Timeout Time", 10).toInt();
    
    QString str = m_pSettings->value("/Logging Options/Log File Name", "").toString();
    qstrcpy(m_szLogFile, str.toLatin1().data());
}

void SBMENDIController::GetComParms()
{
    m_nBaudRate        = m_pSettings->value("/Communication/Baud Rate", 0).toInt();
    m_nParity          = m_pSettings->value("/Communication/Parity", 0).toInt();
    m_nStopBits        = m_pSettings->value("/Communication/Stop Bits", 0).toInt();
    m_nDataBits        = m_pSettings->value("/Communication/Data Bits", 0).toInt();
    m_nFlowControl     = m_pSettings->value("/Communication/Flow Control", 0).toBool();
	m_bResetChecked    = m_pSettings->value("/Communication/Reset Hardware", 0).toBool();
	m_bWirelessChecked = m_pSettings->value("/Communication/Wireless", 0).toBool();
}

//修改于2015/05/01
int SBMENDIController::ReadComPort()
{
    /*char *tmp = NULL;
    QByteArray ba = m_pSerialPort->readAll();
    int n = ba.size();
    tmp = ba.data();
    for (int i = 0; i < n; i++)
    {
        m_ComBuffer.write(tmp[i]);
    }*/

	return 0;
}

void SBMENDIController::GetErrorResponse(char *pszReply, char *pszErrorMsg)
{
    char chErrorToSearchFor[8];
    if (!strnicmp(pszReply, "ERROR",5))
    {
        pszReply += 5;
        sprintf(chErrorToSearchFor, "0x%c%c", pszReply[0], pszReply[1]);
        QString key = "/Error Messages/";
        key += chErrorToSearchFor;
        QString str = m_pErrorIniFile->value(key, "Unknown Error").toString();
        qstrcpy(pszErrorMsg, str.toLatin1().data());
    }
    else if (!strnicmp(pszReply, "WARNING", 7))
    {
        pszReply += 7;
        sprintf(chErrorToSearchFor, "0x%c%c", pszReply[0], pszReply[1]);
        QString key = "/Warning Messages/";
        key += chErrorToSearchFor;
        QString str = m_pErrorIniFile->value(key, "A non-fatal tool error has been encountered").toString();
        qstrcpy(pszErrorMsg, str.toLatin1().data());
    }
    else
        sprintf(pszErrorMsg, "Unknown Error response");
}

void SBMENDIController::ClearLogFile()
{
    FILE *pfOut = NULL;
    m_pSettings->value("/Logging Options/Log File Name", m_szLogFile);
    m_pSettings->value("/Logging Options/Clear File", m_bClearLogFile);
    if (m_bLogToFile && m_bClearLogFile)
    {
        if (m_szLogFile[0] != 0)
        {
            pfOut = fopen(m_szLogFile, "w+t");
            if (pfOut == NULL)
            {
                m_bLogToFile = FALSE;
                m_pSettings->setValue("/Logging Options/Log To File", m_bLogToFile);
                //修改于2015/05/13
				//QMessageBox::warning(NULL, "Log File Error", "Failed to open log file.", QMessageBox::Ok);
				emit m_signalOpenLogFileError();
                return;
            }
            fclose(pfOut);
        }
        else
        {
            m_bLogToFile = FALSE;
            m_pSettings->setValue("/Logging Options/Log To File", m_bLogToFile);
            m_bClearLogFile = FALSE;
            m_pSettings->setValue( "/Logging Options/Clear File", m_bClearLogFile);
        }
    }
}

bool SBMENDIController::bCloseCurrentComport()
{
    if (m_bSerialPortOpened)
    {
        m_pSerialPort->close();
        m_bSerialPortOpened = false;
		return true;
    }
	else
		return false;
}

bool SBMENDIController::bOpenComport()
{
    //修改于2015/05/15
	/*int comPort = m_pSerialPortSettingsDlg->portNumber;

    if (m_nCOMPort != comPort)
    {
        bCloseCurrentComport();
        m_nCOMPort = comPort;
        m_pSerialPort->setPortName(m_pSerialPortSettingsDlg->portName);
    }*/

    if (m_bSerialPortOpened)
    {
        //修改于2015/05/13
		//QMessageBox::warning(NULL, "Warning", "The comport has been opened.", QMessageBox::Ok);
		emit m_signalComportOpened();
        return true;
    }
    else if (!m_pSerialPort->open(QIODevice::ReadWrite))
    {
        //修改于2015/05/13
		//QMessageBox::critical(NULL, "Error", "Open ComPort Failure", QMessageBox::Ok);

		//QSerialPort::SerialPortError str = m_pSerialPort->error();
		//QSerialPort::SerialPortError str1 = str;

		emit m_signalComPortOpenFailure();
        return false;
    }
    else
        m_bSerialPortOpened = true;

    bSetPcComParms();
    return true;
}

bool SBMENDIController::bHardWareReset(bool bWireless)
{
    if (!bWireless)
    {
        m_pSerialPort->sendBreak(m_nSerialBreakDelay);
		if (bGetResponse())
			return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
        return false;
    }
    else
    {
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "RESET 0");
        if (bSendCommand(m_szCommand, true))
        {
			if (bGetResponse())
                return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
            return false;
        }
        else
            return false;
    }
}

bool SBMENDIController::bSetSystemComParms(int nBaudRate, int nDataBits, int nParity, int nStopBits, int nFlowControl)
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "COMM %d%d%d%d%d", nBaudRate, nDataBits, nParity, nStopBits, nFlowControl);
    
	//int a = bSendCommand(m_szCommand, true);
	//int b = a;
	//int c = b;
	//QString str1 = m_szCommand;
	//QString str2 = str1;
	//QString str3 = str2;

	if (bSendCommand(m_szCommand, true))
    {
		if (bGetResponse())
			return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
        return false;
    }
    else
        return false;
}

//修改于2015/04/19
bool SBMENDIController::bSetPcComParms()
{
    //QSettings m_Settings("NDISettings.ini", QSettings::IniFormat);

	QSerialPort::BaudRate    baudRate;
	QSerialPort::DataBits    dataBits;
	QSerialPort::Parity      parity;
	QSerialPort::StopBits    stopBits;
	QSerialPort::FlowControl flowControl;

	switch (m_nBaudRate)
	{
		case 0:
			baudRate = QSerialPort::Baud9600;
			break;
		case 1:
			baudRate = static_cast<QSerialPort::BaudRate>(14400);
			break;
		case 2:
			baudRate = QSerialPort::Baud19200;
			break;
		case 3:
			baudRate = QSerialPort::Baud38400;
			break;
		case 4:
			baudRate = QSerialPort::Baud57600;
			break;
		case 5:
			baudRate = QSerialPort::Baud115200;
			break;
		default:
			baudRate = QSerialPort::Baud9600;
			break;
	}

	switch (m_nDataBits)
	{
		case 0:
			dataBits = QSerialPort::Data8;
			break;
		case 1:
			dataBits = QSerialPort::Data7;
			break;
		default:
			dataBits = QSerialPort::Data8;
			break;
	}

	switch (m_nParity)
	{
		case 0:
			parity = QSerialPort::NoParity;
			break;
		case 1:
			parity = QSerialPort::OddParity;
			break;
		case 2:
			parity = QSerialPort::EvenParity;
			break;
		default:
			parity = QSerialPort::NoParity;
			break;
	}

	switch (m_nStopBits)
	{
		case 0:
			stopBits = QSerialPort::OneStop;
			break;
		case 1:
			stopBits = QSerialPort::TwoStop;
			break;
		default:
			stopBits = QSerialPort::OneStop;
			break;
	}

	switch (m_nFlowControl)
	{
		case 0:
			flowControl = QSerialPort::NoFlowControl;
			break;
		case 1:
			flowControl = QSerialPort::HardwareControl;
			break;
		default:
			flowControl = QSerialPort::NoFlowControl;
			break;
	}

	m_pSerialPort->setBaudRate(baudRate);
    m_pSerialPort->setDataBits(dataBits);
    m_pSerialPort->setParity(parity);
    m_pSerialPort->setStopBits(stopBits);
    m_pSerialPort->setFlowControl(flowControl);
	
	return true;
}

bool SBMENDIController::bBeepSystem(int nBeeps)
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "BEEP %d", nBeeps);
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (bGetResponse())
            return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
    }
    else
        return 0;
}

bool SBMENDIController::bInitializeSystem()
{
    ClearLogFile();
    for (int i = 0; i < NO_HANDLES; i++ )
    {
        memset(m_dtHandleInformation[i].szPhysicalPort, 0, 5);
        m_dtHandleInformation[i].HandleInfo.bInitialized = FALSE;
        m_dtHandleInformation[i].HandleInfo.bEnabled = FALSE;
    }
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "INIT ");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (bGetResponse())
            return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
        else
            return false;
    }
    else
        return false;
}

bool SBMENDIController::bSetFiringRate()
{
    int	nFiringRate = m_pSettings->value("/POLARIS Options/Activation Rate", 0).toInt();
    if (((m_dtSystemInformation.nTypeofSystem == ACCEDO_SYSTEM) || (m_dtSystemInformation.nTypeofSystem == VICRA_SYSTEM)) && (nFiringRate != 0))
    {
        nFiringRate = 0;
        m_pSettings->setValue("/POLARIS Options/Activation Rate", nFiringRate);
    }
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "IRATE %d", nFiringRate);
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (bGetResponse())
            return bCheckResponse(nVerifyResponse(m_szLastReply, TRUE));
    }
    else
        return 0;
}

bool SBMENDIController::bGetSystemInfo()
{
    m_dtSystemInformation.nNoActivePorts      = 0;
    m_dtSystemInformation.nNoActTIPPorts      = 0;
    m_dtSystemInformation.nNoActWirelessPorts = 0;
    m_dtSystemInformation.nNoFGCards          = 0;
    m_dtSystemInformation.nNoFGs              = 0;
    m_dtSystemInformation.nNoMagneticPorts    = 0;
    m_dtSystemInformation.nNoPassivePorts     = 0;
    m_dtSystemInformation.nTypeofSystem       = POLARIS_SYSTEM;
	int nHexResponse = 0, i = 0;
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "VER 4");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        if (!strncmp(m_szLastReply, "POLARIS", 7) ||
            !strncmp(m_szLastReply, "polaris", 7) ||
            !strncmp(m_szLastReply, "Polaris", 7))
        {
            if (strstr(m_szLastReply, "ACCEDO"))
            {
                m_dtSystemInformation.nTypeofSystem = ACCEDO_SYSTEM;
            }
            else if (strstr(m_szLastReply, "VICRA") ||
                     strstr(m_szLastReply, "vicra") ||
                     strstr(m_szLastReply, "Vicra"))
            {
                m_dtSystemInformation.nTypeofSystem = VICRA_SYSTEM;
            }
            else if (strstr(m_szLastReply, "SPECTRA") ||
                     strstr(m_szLastReply, "spectra") ||
                     strstr(m_szLastReply, "Spectra"))
            {
                m_dtSystemInformation.nTypeofSystem = SPECTRA_SYSTEM;
            }
            else
            {
                m_dtSystemInformation.nTypeofSystem = POLARIS_SYSTEM;
            }
        }
        else if (!strncmp(m_szLastReply, "AURORA", 6)||
                 !strncmp(m_szLastReply, "aurora", 6)||
                 !strncmp(m_szLastReply, "Aurora", 6))
        {
            m_dtSystemInformation.nTypeofSystem = AURORA_SYSTEM;
        }
        else
            return 0;
        sprintf(m_dtSystemInformation.szVersionInfo, m_szLastReply);
        m_dtSystemInformation.szVersionInfo[strlen(m_dtSystemInformation.szVersionInfo) - 5] = 0;
        emit m_signalSystemTypeGot(m_dtSystemInformation.nTypeofSystem);
    }
    if (m_dtSystemInformation.nTypeofSystem != AURORA_SYSTEM)
    {
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 00");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            nHexResponse = nASCIItoHexInt(m_szLastReply, 8);
            m_dtSystemInformation.bActivePortsAvail    = (0x01 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bPassivePortsAvail   = (0x02 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bMultiVolumeParms    = (0x04 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bTIPSensing          = (0x08 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bActiveWirelessAvail = (0x10 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bMagneticPortsAvail  = (0x8000 & nHexResponse ? 1 : 0);
            m_dtSystemInformation.bFieldGeneratorAvail = (0x40000 & nHexResponse ? 1 : 0);
        }
        sprintf(m_szCommand, "SFLIST 01");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoActivePorts = nASCIItoHexInt(m_szLastReply, 1);
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 02");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoPassivePorts = nASCIItoHexInt(m_szLastReply, 1);
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 04");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoActTIPPorts = nASCIItoHexInt(m_szLastReply, 1);
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 05");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoActWirelessPorts = nASCIItoHexInt(m_szLastReply, 1);
        }
    }
    else
    {
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 10");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoMagneticPorts = nASCIItoHexInt(m_szLastReply, 2);
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "SFLIST 12");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtSystemInformation.nNoFGCards = nASCIItoHexInt(m_szLastReply, 1);
            m_dtSystemInformation.nNoFGs = nASCIItoHexInt(&m_szLastReply[1], 1);
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "VER 7");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            strcat(m_dtSystemInformation.szVersionInfo, "\n");
            strcat(m_dtSystemInformation.szVersionInfo, m_szLastReply);
            m_dtSystemInformation.szVersionInfo[strlen(m_dtSystemInformation.szVersionInfo) - 5] = 0;
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "VER 8");
        if (bSendCommand(m_szCommand, TRUE))
        {
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            strcat(m_dtSystemInformation.szVersionInfo, "\n");
            strcat(m_dtSystemInformation.szVersionInfo, m_szLastReply);
            m_dtSystemInformation.szVersionInfo[strlen(m_dtSystemInformation.szVersionInfo) - 5] = 0;
        }
    }
    return 1;
}

bool SBMENDIController::bInitializeAllHandles()
{
    int i = 0;
    int n = 0;
    int nHandle = 0;
    int nNoHandles = 0;
    int nPhysicalPorts = 0;

    char pszPortID[20];
    char pszROMFileName[MAX_PATH];
    char szHandleList[MAX_REPLY_MSG];
    char szErrorMessage[50];
    QString key;

    if (m_dtSystemInformation.nTypeofSystem != AURORA_SYSTEM)
    {
        for (i = 0; i < m_dtSystemInformation.nNoPassivePorts; i++)
        {
            sprintf(pszPortID, "Wireless Tool %02d", i + 1);
            key = "/POLARIS SROM Image Files/";
            key += pszPortID;
            QString str = m_pSettings->value(key).toString();
            qstrcpy(pszROMFileName, str.toLatin1().data());
            if (*pszROMFileName)
            {
                bLoadVirtualSROM(pszROMFileName, pszPortID, TRUE);
            }
        }
    }
    do
    {
        n = 0;
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "PHSR 02");
        if (!bSendCommand(m_szCommand, TRUE))
            return 0;
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        sprintf(szHandleList, m_szLastReply);
        nNoHandles = nASCIItoHexInt(&m_szLastReply[n], 2);
        n += 2;
        if (nNoHandles > 0)
        {
            nPhysicalPorts = (m_dtSystemInformation.nNoActivePorts > 0 ?
                                  m_dtSystemInformation.nNoActivePorts :
                                  m_dtSystemInformation.nNoMagneticPorts > 0 ?
                                      m_dtSystemInformation.nNoMagneticPorts : 0);
            if (m_dtSystemInformation.nNoActivePorts == 4)
                nPhysicalPorts = 12;
            key = m_dtSystemInformation.nNoActivePorts > 0 ?
                        "POLARIS SROM Image Files\0" :
                        m_dtSystemInformation.nNoMagneticPorts > 0 ?
                            "AURORA SROM Image Files\0" : "" ;

            for (i = 0; i < nPhysicalPorts; i++)
            {
                sprintf(pszPortID, "Port %d", i + 1);
                key += pszPortID;
                QString str = m_pSettings->value(key).toString();
                qstrcpy(pszROMFileName, str.toLatin1().data());
                if (*pszROMFileName)
                {
                    if (!strncmp(pszROMFileName, "TTCFG", 5))
                        nLoadTTCFG(pszPortID);
                    else
                        bLoadVirtualSROM(pszROMFileName, pszPortID, TRUE);
                    nHandle = nGetHandleForPort(pszPortID);
                    if (nHandle != 0)
                    {
                        if (!bInitializeHandle(nHandle))
                        {
                            sprintf(szErrorMessage, "Port %s could not be initialized.\n"
                                    "Check your SROM image file settings.", m_dtHandleInformation[nHandle].szPhysicalPort);
                            //修改于2015/05/13
							//QMessageBox::critical(NULL, "PINIT ERROR", szErrorMessage, QMessageBox::Ok);
							emit m_signalPINITError(szErrorMessage);
                            return 0;
                        }
                    }
                }
            }
            for (int i = 0; i < nNoHandles; i++)
            {
                nHandle = nASCIItoHexInt(&szHandleList[n], 2);
                if (!bGetHandleInformation(nHandle))
                    return 0;
                if (!m_dtHandleInformation[nHandle].HandleInfo.bInitialized)
                {
                    if (!bInitializeHandle(nHandle))
                    {
                        sprintf(szErrorMessage, "Port %s could not be initialized.\n"
                                "Check your SROM image file settings.", m_dtHandleInformation[nHandle].szPhysicalPort);
                        //修改于2015/05/13
						//QMessageBox::critical(NULL, "PINIT ERROR", szErrorMessage, QMessageBox::Ok);
						emit m_signalPINITError(szErrorMessage);
                        return 0;
                    }
                    n += 5;
                }
            }
        }
    }while (nNoHandles > 0);
    return 1;
}

bool SBMENDIController::bInitializeHandle(int nHandle)
{
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PINIT %02X", nHandle);
    if (!bSendCommand( m_szCommand, TRUE))
        return 0;
    if (!bGetResponse())
        return 0;
    if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
        return 0;
    m_dtHandleInformation[nHandle].HandleInfo.bInitialized = TRUE;
    return 1;
}

bool SBMENDIController::bEnableAllHandles()
{
    int nNoHandles = 0;
    int nHandle = 0;
    int n = 0;
    char szHandleList[MAX_REPLY_MSG];
    m_nHandlesEnabled = 0;
    
	memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PHSR 03");
    
	if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        sprintf(szHandleList, m_szLastReply);
        nNoHandles = nASCIItoHexInt(&szHandleList[n], 2);
        n += 2;
        for (int i = 0; i < nNoHandles; i++)
        {
            nHandle = nASCIItoHexInt(&szHandleList[n], 2);
            n += 5;
            bEnableHandle(nHandle);
            m_EnabledHandleIndex[m_nHandlesEnabled] = nHandle;
            m_nHandlesEnabled++;
        }
        emit m_signalHandlesEnabledGot(m_nHandlesEnabled);
        return 1;
    }
    return 0;
}

int SBMENDIController::nLoadTTCFG(char *pszPortID)
{
    int	nPortHandle = 0;
    nPortHandle = nGetHandleForPort(pszPortID);
    if (nPortHandle == 0)
        return 0;
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "TTCFG %02X", nPortHandle);
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
    }
    else
        return 0;
}

int SBMENDIController::nGetHandleForPort(char *pszPortID)
{
    int nPortHandle = 0;
    int nNoHandles = 0;
    int n = 0;
    char szHandleList[MAX_REPLY_MSG];
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PHSR 00");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (bGetResponse())
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
    }
    sprintf(szHandleList, m_szLastReply);
    nNoHandles = nASCIItoHexInt(&szHandleList[n], 2);
    n += 2;
    for (int i = 0; i < nNoHandles; i++)
    {
        nPortHandle = nASCIItoHexInt(&szHandleList[n], 2);
        n += 5;
        bGetHandleInformation(nPortHandle);
        if (!strncmp(m_dtHandleInformation[nPortHandle].szPhysicalPort, pszPortID, 2))
            return nPortHandle;
    }
    return 0;
}

bool SBMENDIController::bLoadVirtualSROM(char *pszFileName, char *pszPhysicalPortID, bool bPassive)
{
    FILE *pFileHandle = NULL;
    int nHandle = 0;
    int nBytes = 0;
    int nCnt = 0;
    int i = 0;
    int n = 0;
    static unsigned char gruchBuff[1024];
    char cMessage[256];

    if (!*pszFileName)
        return 0;
    if (bPassive)
    {
        for (i = 0; i < NO_HANDLES; i++)
        {
            if (!strncmp( m_dtHandleInformation[i].szPhysicalPort, pszPhysicalPortID, 16))
                return 0;
        }
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "PHRQ ********01****");
        if (!bSendCommand( m_szCommand, TRUE))
            return 0;
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        nHandle = nASCIItoHexInt(&m_szLastReply[n], 2);
        if (m_dtHandleInformation[nHandle].HandleInfo.bInitialized == 1)
            return 0;
    }
    if (!(pFileHandle = fopen(pszFileName, "rb")))
        return 0;
    if ((nBytes = fread(gruchBuff, 1, sizeof(gruchBuff), pFileHandle)) < 1)
    {
        sprintf(cMessage, "Unable to read ROM image file %s.", pszFileName);
        //修改于2015/05/13
		//QMessageBox::critical(NULL, "SROM Error", cMessage, QMessageBox::Ok);
		emit m_signalSROMError(cMessage);
        goto cleanup;
    }
    for (nCnt = 0; nCnt < nBytes; )
    {
        memset(m_szCommand, 0, sizeof(m_szCommand));
        sprintf(m_szCommand, "PVWR:%02X%04X", nHandle, nCnt);
        for (i = 0; i < 64; i++, nCnt++)
        {
            sprintf(m_szCommand + 11 + 2 * i, "%02X", gruchBuff[nCnt]);
        }
        if (!bSendCommand(m_szCommand, TRUE))
            goto cleanup;
        if (!bGetResponse())
        {
            sprintf(cMessage, "Failed writing to %s.", pszPhysicalPortID);
            //修改于2015/05/13
			//QMessageBox::critical(NULL, "SROM Image Error", cMessage, QMessageBox::Ok);
			emit m_signalSROMImageError(cMessage);
            goto cleanup;
        }
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
        {
            goto cleanup;
        }
    }
cleanup:
    if (!(fclose(pFileHandle)))
        return 0;
    if (m_dtSystemInformation.nTypeofSystem == VICRA_SYSTEM || m_dtSystemInformation.nTypeofSystem == SPECTRA_SYSTEM)
        sprintf(m_dtHandleInformation[nHandle].szPhysicalPort, pszPhysicalPortID);
    return 1;
}

bool SBMENDIController::bFreeAllHandles()
{
    int nNoHandles = 0, nHandle = 0, n = 0;
    char szHandleList[MAX_REPLY_MSG];
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "PHSR 01");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
        if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
            return 0;
        sprintf(szHandleList, m_szLastReply);
        nNoHandles = nASCIItoHexInt(&szHandleList[n], 2);
        n += 2;
        for (int i = 0; i < nNoHandles; i++)
        {
            nHandle = nASCIItoHexInt(&szHandleList[n], 2);
            memset(m_szCommand, 0, sizeof(m_szCommand));
            sprintf(m_szCommand, "PHF %02X", nHandle);
            n += 5;
            if (!bSendCommand(m_szCommand, TRUE))
                return 0;
            if (!bGetResponse())
                return 0;
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            m_dtHandleInformation[nHandle].HandleInfo.bInitialized = FALSE;
            m_dtHandleInformation[nHandle].HandleInfo.bEnabled = FALSE;
            memset(m_dtHandleInformation[nHandle].szPhysicalPort, 0, 5);
        }
        return 1;
    }
    else
        return 0;
}

bool SBMENDIController::bGetHandleInformation(int nPortHandle)
{
    unsigned int uASCIIConv = 0;
    char *pszPortInformation = NULL;
    memset(m_szCommand, 0, sizeof(m_szCommand));
    if (m_dtSystemInformation.nTypeofSystem == VICRA_SYSTEM || m_dtSystemInformation.nTypeofSystem == SPECTRA_SYSTEM)
        sprintf(m_szCommand, "PHINF %02X0005", nPortHandle);
    else
        sprintf(m_szCommand, "PHINF %02X0025", nPortHandle);

    if (bSendCommand(m_szCommand, TRUE))
    {
        if (bGetResponse())
        {
            if (!bCheckResponse(nVerifyResponse(m_szLastReply, TRUE)))
                return 0;
            pszPortInformation = m_szLastReply;
            strncpy(m_dtHandleInformation[nPortHandle].szToolType, pszPortInformation, 8);
            m_dtHandleInformation[nPortHandle].szToolType[8] = '\0';
            pszPortInformation += 8;
            strncpy(m_dtHandleInformation[nPortHandle].szManufact, pszPortInformation, 12);
            m_dtHandleInformation[nPortHandle].szManufact[12] = '\0';
            pszPortInformation += 12;
            strncpy(m_dtHandleInformation[nPortHandle].szRev, pszPortInformation, 3);
            m_dtHandleInformation[nPortHandle].szRev[3] = '\0';
            pszPortInformation += 3;
            strncpy(m_dtHandleInformation[nPortHandle].szSerialNo, pszPortInformation, 8);
            m_dtHandleInformation[nPortHandle].szSerialNo[8] = '\0';
            pszPortInformation += 8;
            uASCIIConv = nASCIItoHexInt(pszPortInformation, 2);
            pszPortInformation += 2;
            m_dtHandleInformation[nPortHandle].HandleInfo.bToolInPort        = (uASCIIConv & 0x01 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bGPIO1             = (uASCIIConv & 0x02 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bGPIO2             = (uASCIIConv & 0x04 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bGPIO3             = (uASCIIConv & 0x08 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bInitialized       = (uASCIIConv & 0x10 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bEnabled           = (uASCIIConv & 0x20 ? 1 : 0);
            m_dtHandleInformation[nPortHandle].HandleInfo.bTIPCurrentSensing = (uASCIIConv & 0x80 ? 1 : 0);
            strncpy(m_dtHandleInformation[nPortHandle].szPartNumber, pszPortInformation, 20);
            m_dtHandleInformation[nPortHandle].szPartNumber[20] = '\0';
            pszPortInformation += 20;
            return 1;
        }
        else
            return 0;
    }
    else return 0;
}

void SBMENDIController::ErrorMessage()
{
    char pchErrorMessage[256];
    char pchErrorNumber[8];
    bool bBeepOnError = FALSE;
    int  nNoErrorBeeps = 0;
    GetErrorResponse(m_szLastReply, pchErrorMessage);
    strncpy(pchErrorNumber, m_szLastReply, 7);
    pchErrorNumber[7] = '\0';
    bBeepOnError = m_pSettings->value("/Beeping Options/Beep On Error", 0).toBool();
    nNoErrorBeeps = m_pSettings->value("/Beeping Options/No Error Beeps", 1).toInt();
    if (bBeepOnError)
        bBeepSystem(nNoErrorBeeps);
    //修改于2015/05/13
	//QMessageBox::critical(NULL, pchErrorNumber, pchErrorMessage, QMessageBox::Ok);
	emit m_signalErrorMessage(pchErrorNumber, pchErrorMessage);
}

void SBMENDIController::WarningMessage()
{
    char pchWarningMessage[256];
    char pchWarningNumber[10];
    bool bBeepOnWarning = FALSE;
    int  nNoWarningBeeps = 0;
    GetErrorResponse(m_szLastReply, pchWarningMessage);
    strncpy(pchWarningNumber, m_szLastReply, 9);
    pchWarningNumber[9] = '\0';
    bBeepOnWarning = m_pSettings->value("/Beeping Options/Beep On Error", 0).toBool();
    nNoWarningBeeps = m_pSettings->value("/Beeping Options/No Error Beeps", 1).toInt();
    if (bBeepOnWarning)
        bBeepSystem(nNoWarningBeeps);
    //修改于2015/05/13
	//QMessageBox::warning(NULL, pchWarningNumber, pchWarningMessage, QMessageBox::Ok);
	emit m_signalWarningMessage(pchWarningNumber, pchWarningMessage);
}

//修改于2015/04/30
bool SBMENDIController::bCreateTimeoutTable()
{
    /*m_dtTimeoutValues.clear();
    memset(m_szCommand, 0, sizeof(m_szCommand));
    sprintf(m_szCommand, "GET Info.Timeout.*");
    if (bSendCommand(m_szCommand, TRUE))
    {
        if (!bGetResponse())
            return 0;
		
        if (!nVerifyResponse(m_szLastReply, TRUE))
            return 0;
        QStringList strlist;
        QString sTimeoutInfo(m_szLastReply);
        strlist = sTimeoutInfo.split(QChar(LINE_FEED), QString::KeepEmptyParts, Qt::CaseSensitive);
        foreach (QString str, strlist)
        {
            int i = str.indexOf("=");
            int timeoutvalue = str.right(str.size() - i - 1).toInt();
            int n = strlen("Info.Timeout.");
            QString command = str.mid(n, i - n);
            m_dtTimeoutValues.insert(command, timeoutvalue);
        }
        return 1;
    }
    else
        return 0;*/

	char *pszTimeoutInfo = NULL;
	char szTimeoutString[] = "Info.Timeout.\0";

	m_dtTimeoutValues.clear();
	memset(m_szCommand, 0, sizeof(m_szCommand));
	sprintf( m_szCommand, "GET Info.Timeout.*" );
	
	if (bSendCommand(m_szCommand, TRUE))
	{
		if (!bGetResponse())
			return 0;

		if( !nVerifyResponse(m_szLastReply, TRUE))
			return 0;

		m_szLastReply[strlen(m_szLastReply) - 5] = LINE_FEED; // 4 for CRC and 1 for <CR>
		m_szLastReply[strlen(m_szLastReply) - 4] = 0;

		pszTimeoutInfo = m_szLastReply;

		char *chValue, *chNext;
		while (strchr( pszTimeoutInfo, '='))
		{
			pszTimeoutInfo += strlen(szTimeoutString);
			chValue = strchr( pszTimeoutInfo, '=' );
			*chValue++ = 0;
			chNext = strchr( chValue, LINE_FEED );
			*chNext++ = 0;

			int a = atoi( chValue );
			m_dtTimeoutValues.insert(pszTimeoutInfo, a);

			pszTimeoutInfo = chNext;
		}
	}

	return 1;
}

//修改于2015/04/30
int SBMENDIController::nLookupTimeout(char *szCommand)
{
    //QString str;
	
    QString sCommand(szCommand);
	int nTimeoutValue;
	int nPos;
    
	if (m_dtSystemInformation.nTypeofSystem == AURORA_SYSTEM)
        return m_nDefaultTimeout;
    
	if (sCommand.indexOf(" ") == -1)
	{
		if(sCommand.indexOf(":") == -1)
			nPos = -1;
		else
            nPos = sCommand.indexOf(":");
	}
	else
	    nPos = sCommand.indexOf(" ");
    
	if (nPos > 0)
        sCommand = sCommand.left(nPos);
    else
        return m_nDefaultTimeout;

	nTimeoutValue = m_dtTimeoutValues.value(sCommand, 0);
	if (!nTimeoutValue)
		return m_nDefaultTimeout;

	return nTimeoutValue;

    //return m_dtTimeoutValues.value(str, m_nDefaultTimeout);
}

void SBMENDIController::ApplyXfrms()
{
	QuatTransformation dtRefQuatXfrm;
	QuatTransformation dtRefQuatXfrmInv;
	QuatTransformation dtPortQuatXfrm;
	QuatTransformation dtNewQuatXfrm;

	if( m_nRefHandle == -1 ) //if no reference handle do nothing
		return;

	for( int nHandle = 0; nHandle < NO_HANDLES; nHandle++ )
	{
		if( nHandle != m_nRefHandle &&							  // don't apply the reference to itself
			m_dtHandleInformation[nHandle].HandleInfo.bEnabled )  // only apply if the handle is enabled
		{
			if( m_dtHandleInformation[m_nRefHandle].Xfrms.translation.x <= MAX_NEGATIVE )
			{
				m_dtHandleInformation[nHandle].Xfrms.translation.x =
				m_dtHandleInformation[nHandle].Xfrms.translation.y =
				m_dtHandleInformation[nHandle].Xfrms.translation.z =
				m_dtHandleInformation[nHandle].Xfrms.rotation.q0 =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qx =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qy =
				m_dtHandleInformation[nHandle].Xfrms.rotation.qz = BAD_FLOAT;
				m_dtHandleInformation[nHandle].Xfrms.ulFlags = TRANSFORM_MISSING;
			}/* if */
			else
			{
				dtRefQuatXfrm.rotation = m_dtHandleInformation[m_nRefHandle].Xfrms.rotation;
				dtRefQuatXfrm.translation = m_dtHandleInformation[m_nRefHandle].Xfrms.translation;
				QuatInverseXfrm(&dtRefQuatXfrm, &dtRefQuatXfrmInv);

				dtPortQuatXfrm.rotation = m_dtHandleInformation[nHandle].Xfrms.rotation;
				dtPortQuatXfrm.translation = m_dtHandleInformation[nHandle].Xfrms.translation;
				QuatCombineXfrms( &dtPortQuatXfrm, &dtRefQuatXfrmInv, &dtNewQuatXfrm );
				m_dtHandleInformation[nHandle].Xfrms.rotation = dtNewQuatXfrm.rotation;
				m_dtHandleInformation[nHandle].Xfrms.translation = dtNewQuatXfrm.translation;
			}/* else */
		} /* if */
	} /* for */
} /* ApplyXfrm */

//修改于2015/04/20
bool SBMENDIController::bSendCommand(char *m_szCommand, bool bAddCRC)
{
    bool bComplete = false;

	if (m_pSerialPort == NULL)
        return bComplete;

	m_nTimeout = nLookupTimeout(m_szCommand);

    if (!bBuildCommand(m_szCommand, bAddCRC))
        return bComplete;

	if(strlen(m_szCommand) >= (MAX_COMMAND_MSG))
		return bComplete;

    int n = strlen(m_szCommand);
	
	//修改于2015/04/28
	/*m_pSerialPort->write(m_szCommand, n);
	
	if (!m_pSerialPort->waitForBytesWritten(50 * n + 2000))
	{
		//修改于2015/05/13
		//QMessageBox::critical(NULL, tr("Timeout Error!"), tr("Comport Write Time out!"));
		emit m_signalWriteTimeoutError();
		bComplete = false;
	}
	else
		bComplete = true;*/
	
	
	//原始代码
	if (m_pSerialPort->write(m_szCommand, n) < 0)
		bComplete = false;
	else
		bComplete = true;
	//原始代码
	
    
	//m_pSerialPort->flush();
    LogToFile(0, m_szCommand);
    return bComplete;
}

//修改于2015/05/01
bool SBMENDIController::bGetResponse()
{
	/*
	//测试代码
	char chChar;
    bool bDone = false;

	int  dataindex = 0;
	int  nCount    = 0;
	int  nRetry    = 0;
	int  nRet      = 0;
    
    memset(m_szLastReply, 0, sizeof(m_szLastReply));

	QTime time;
	time.start();
    
    do
	{
		if (m_pSerialPort == NULL)
			return false;

		m_pSerialPort->waitForReadyRead(100 * m_nTimeout);
		//while (m_pSerialPort->waitForReadyRead(10 * m_nTimeout) && (!bDone))
		while (m_pSerialPort->waitForReadyRead(10) && (!bDone))
        {
			QByteArray bytearray = m_pSerialPort->readAll();
			
			int bytearray_size = bytearray.size();
			char *bytearray_data = bytearray.data();
            
			for (int i = 0; i < bytearray_size; i++)
				m_ComBuffer.write(bytearray_data[i]);
            
			int datalength = m_ComBuffer.GetLen();
            
			for (dataindex = 0; dataindex < datalength; dataindex++)
            {
                chChar = m_ComBuffer.read(dataindex);
                if (chChar == '\r')
                {
                    m_szLastReply[nCount] = CARRIAGE_RETURN;
                    m_szLastReply[nCount + 1] = '\0';
                    bDone = TRUE;
                    break;
                }
                else
                {
                    m_szLastReply[nCount] = chChar;
					nCount++;
                }
            }
			if (bDone)
                m_ComBuffer.MoveRead(dataindex + 1);
            else
				m_ComBuffer.MoveRead(datalength);
		}
           
		if (!bDone)
		{
			if (time.elapsed() > m_nTimeout)
			{
				nCount = 0;
				if (nRetry < 3)
				{
					nRetry++;
					memset(m_szLastReply, 0, sizeof(m_szLastReply));
					bSendCommand(m_szCommand, FALSE);
					time.restart();
				}
				else
				{
					nRet = QMessageBox::critical(this, tr("Timeout Error!"), tr("Comport Time out!\n""what do you want to do?"), QMessageBox::Retry | QMessageBox::Abort| QMessageBox::Ignore);
					switch (nRet)
					{
					case QMessageBox::Retry:
						if (strlen(m_szCommand) > 0)
						{
							nRetry = 1;
							memset(m_szLastReply, 0, sizeof(m_szLastReply));
							bSendCommand(m_szCommand, FALSE);
							time.restart();
						}
						else
							m_pSerialPort->sendBreak(m_nSerialBreakDelay);
						break;
					case QMessageBox::Abort:
					    QApplication::exit();
						break;
					case QMessageBox::Ignore:
						return FALSE;
						break;
					default:
						return FALSE;
						break;
					}
				}
			}
		}
    } while (!bDone);

    LogToFile(1, m_szLastReply);
	return 1;
	//测试代码
	*/
	
	//sbme_ThreadNDIMutex.lock();
	//原始代码
	m_nTimeOutChoose = -1;

	char chChar;
	bool bDone = false;
    
	int  dataindex = 0;
	int  nCount    = 0;
	int  nRetry    = 0;
    //int  nRet      = 0;
    
    QTime time;

    memset(m_szLastReply, 0, sizeof(m_szLastReply));
    int ntimeout = 1000 * m_nTimeout;
    
	if (m_pSerialPort->waitForReadyRead(ntimeout))
    {
        time.start();

		QTime mytime;
		mytime = QTime::currentTime();
        while (!bDone)
        {
            m_pSerialPort->waitForReadyRead(10);
            //ReadComPort();
			
			QByteArray bytearray = m_pSerialPort->readAll();
			
			int bytearray_size = bytearray.size();
			char *bytearray_data = bytearray.data();
            
			for (int i = 0; i < bytearray_size; i++)
				m_ComBuffer.write(bytearray_data[i]);

            int datalength = m_ComBuffer.GetLen();
            
			for (dataindex = 0; dataindex < datalength; dataindex++)
            {
                chChar = m_ComBuffer.read(dataindex);
                if (chChar == '\r')
                {
                    m_szLastReply[nCount] = CARRIAGE_RETURN;
                    m_szLastReply[nCount+1] = '\0';
                    bDone = TRUE;
                    break;
                }
                else
                {
                    m_szLastReply[nCount] = chChar;
					nCount++;
                }
            }
            if (bDone)
                m_ComBuffer.MoveRead(dataindex + 1);
            else
				m_ComBuffer.MoveRead(datalength);
            
			if (time.elapsed() > ntimeout)
			{
				//修改于2015/05/13
				//QMessageBox::critical(NULL, tr("Timeout Error!"), tr("Comport Time out!"));
				emit m_signalProcessTimeoutError();
                break;
			}
        }
		qDebug()<<(QTime::currentTime().second() - mytime.second())*1000 + QTime::currentTime().msec() - mytime.msec();
    }
    else
    {
        //nCount = 0;
		if (nRetry < 3)
        {
            nRetry++;
            memset(m_szLastReply, 0, sizeof(m_szLastReply));
            bSendCommand(m_szCommand, FALSE);
			//time.restart();
        }
        else
        {
            //修改于2015/05/13
			//nRet = QMessageBox::critical(NULL, tr("Timeout Error!"), tr("Comport Time out!\n""what do you want to do?"), QMessageBox::Retry | QMessageBox::Abort| QMessageBox::Ignore);
            emit m_signalReadTimeoutError();
			
			while (m_nTimeOutChoose == -1)
				;

			switch (m_nTimeOutChoose)
            {
            case QMessageBox::Retry:
                if (strlen(m_szCommand) > 0)
                {
                    nRetry = 1;
                    memset(m_szLastReply, 0, sizeof(m_szLastReply));
                    bSendCommand(m_szCommand, FALSE);
					//time.restart();
                }
                else
                    m_pSerialPort->sendBreak(m_nSerialBreakDelay);
                break;
            case QMessageBox::Abort:
                QApplication::exit();
                break;
            case QMessageBox::Ignore:
                return FALSE;
                break;
            default:
                return FALSE;
                break;
            }
        }
    }
    LogToFile(1, m_szLastReply);
	
	//sbme_ThreadNDIMutex.unlock();
	return 1;
	//原始代码
}

bool SBMENDIController::bGetBinaryResponse()
{
	return true;
}

int SBMENDIController::nVerifyResponse(char *pszReply, bool bCheckCRC)
{
   int nResponse = 0;

    if (!strnicmp(pszReply, "RESET", 5))
        nResponse = REPLY_RESET;
    else if (!strnicmp(pszReply, "OKAY", 4))
        nResponse = REPLY_OKAY;
    else if (!strnicmp(pszReply, "ERROR", 5))
        nResponse = REPLY_ERROR;
    else if (!strnicmp(pszReply, "WARNING", 7))
        nResponse = REPLY_WARNING;
    else if (strlen(pszReply) > 0)
        nResponse = REPLY_OTHER;
    else
        return REPLY_INVALID;
    if (nResponse & REPLY_OKAY  || nResponse & REPLY_RESET|| nResponse & REPLY_OTHER && bCheckCRC)
    {
        if (!SystemCheckCRC(pszReply))
            return REPLY_BADCRC;
        else
            return nResponse;
    }
    else
        return nResponse;
}

bool SBMENDIController::bCheckResponse(int nReturnedValue)
{
    if (nReturnedValue == REPLY_ERROR)
    {
        ErrorMessage();
        return 0;
    }
    else if (nReturnedValue == REPLY_BADCRC)
    {
        //修改于2015/05/13
		//QMessageBox::critical(NULL, "CRC Error", "Bad CRC received with reply.", QMessageBox::Ok);
		emit m_signalCRCError();
        return 0;
    }
    else if (nReturnedValue == REPLY_WARNING)
    {
        WarningMessage();
        return 1;
    }
    else if (nReturnedValue == REPLY_INVALID)
    {
        //修改于2015/05/13
		//QMessageBox::critical(NULL, "Invalid Response", "Invalid response received from the system", QMessageBox::Ok);
		emit m_signalInvalidResponseError();
        return 0;
    }
    else return 1;
}

void SBMENDIController::LogToFile(int nDirection, char *psz)
{
    int n;
    
	FILE *pfOut = NULL;
    
	time_t ltime;

	char pszTimeStamp[256];
    char szMessage[256];
    

    if (!m_bLogToFile)
        return;

    pfOut = fopen(m_szLogFile, "a+t");
    
	if (pfOut == NULL)
    {
        sprintf(szMessage, "The log file (%s) could not be opened.\n"
                "COM Port logging will be turned off.\n\n"
                "To reactivate this feature, please do so under\n"
                "the Options menu.", m_szLogFile);
        m_bLogToFile = FALSE;
        m_pSettings->setValue("/Logging Options/Log To File", m_bLogToFile);
        //修改于2015/05/13
		//QMessageBox::warning(NULL, "Log File Error", szMessage, QMessageBox::Ok);
		emit m_signalLogFileError(szMessage);
        return;
    }
    
	if (m_bDateTimeStampFile)
    {
        int i = 0;
        QString str = QTime::currentTime().toString();
        qstrcpy(pszTimeStamp, str.toLatin1().data());
        do
        {
            putc(pszTimeStamp[i], pfOut);
            i++;
        }while (pszTimeStamp[i]);
    }
   
	putc(nDirection?'<':'>', pfOut);
    putc(' ', pfOut);
    
	if (!*psz)
        psz[0] = CARRIAGE_RETURN;
    
	if (((psz[0] & 0xff) == 0xc4) && ((psz[1] & 0xff) == 0xa5))
        fprintf(pfOut, "BINARY REPLY");
    else
        for (n = 0; (n < MAX_REPLY_MSG) && (psz[n] != CARRIAGE_RETURN); putc(psz[n++],pfOut))
            ;
    
	putc(LINE_FEED, pfOut);
    putc(LINE_FEED, pfOut);
    
	fclose(pfOut);
}

bool SBMENDIController::m_slotGetSystemTransformData()
{
	while (!sbme_bStopTracking)
	{
		//char pszTemp[256];
		//QString str;
		//Rotation dtEulerRot;

		//if (!m_bIsTracking)
			//return 0;
		//sbme_ThreadNDIMutex.lock();

		//if (!bGetTXTransforms())
			//return 0;

		if (m_nTrackingMode == 0)
	    {
		    if (!bGetTXTransforms())
			    return 0;
	    }
	    else if (m_nTrackingMode == 1)
	    {
		    if (!bGetBXTransforms())
			    return 0;
	    }

		//sbme_ThreadNDIMutex.unlock();

		//if a new port has become occupied we do the following:
		//(1) Stop tracking
		//(2) Activate Ports
		//(3) Start Tracking

		if (m_dtSystemInformation.bPortOccupied)
		{
			if (bStopTracking() && bActivateAllHandles() && bStartTracking())
				m_bIsNewPortsActiveFailed = false;
			else
				m_bIsNewPortsActiveFailed = true;
		}

		//sbme_ThreadNDIMutex.unlock();
		emit m_signalGetSystemTransformData(m_dtSystemInformation.bPortOccupied, m_bIsNewPortsActiveFailed);

		//sbme_ThreadNDIMutex.unlock();
	}

	/*
	if (m_nTrackingMode == 0)
	{
		if (!bGetTXTransforms())
			return 0;
	}
	else if (m_nTrackingMode == 1)
	{
		if (!bGetBXTransforms())
			return 0;
	}

	//if a new port has become occupied we do the following:
	//(1) Stop tracking
	//(2) Activate Ports
	//(3) Start Tracking

	if (m_dtSystemInformation.bPortOccupied)
	{
		if (bStopTracking() && bActivateAllHandles() && bStartTracking())
			m_bIsNewPortsActiveFailed = false;
		else
			m_bIsNewPortsActiveFailed = true;
	}

	emit m_signalGetSystemTransformData(m_dtSystemInformation.bPortOccupied, m_bIsNewPortsActiveFailed);
	*/
}

void SBMENDIController::m_slotTrackingMode(int nTrackingMode)
{
	m_nTrackingMode = nTrackingMode;
}

void SBMENDIController::m_slotTimeOutChoose(int nTimeOutChoose)
{
	m_nTimeOutChoose = nTimeOutChoose;
}

void SBMENDIController::m_slotCOMPortParametersChange()
{
	GetComParms();
	bSetPcComParms();
	bSetSystemComParms(m_nBaudRate, m_nDataBits, m_nParity, m_nStopBits, m_nFlowControl);
}