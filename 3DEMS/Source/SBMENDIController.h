#ifndef SBMENDICONTROLLER_H
#define SBMENDICONTROLLER_H

#include <QtWidgets>
#include <QSerialPort>

#include "SBMEUserDef.h"
#include "SBMENDIDef.h"
#include "SBMESerialPortBuffer.h"
//#include "SBMENDISerialPortSettingsDlg.h"
//#include "SBMENDIProgramOptionDlg.h"
//#include "SBMENDISystemFeaturesDlg.h"

//–ﬁ∏ƒ”⁄2015/05/13
//class SBMENDIController : public QWidget
class SBMENDIController : public QObject
{
    Q_OBJECT

public:
    //SBMENDIController(QWidget *parent);
	SBMENDIController();
    ~SBMENDIController();
	
	void AutoConnect();
    
	void SetAutoConnect(bool isAutoConnect);
    void SetCommPort();
	void SetProgramOptions();
	void ViewSystemFeatures();

    bool ResetSystem();
    bool InitializeSystem();
	
	bool bEnableHandle(int nHandle);
    bool bDisableHandle(int nHandle);
    bool bActivateAllHandles();
    bool bStartTracking();
	bool bGetTXTransforms();
	bool bGetBXTransforms();
    bool bStopTracking();

	void FiringRate20Hz();
    void FiringRate30Hz();
    void FiringRate60Hz();

	void SetReferenceHandle(int referenceHandle);

    int *GetEnnabledHandleIndex();

    HandleInformation *GetHandleInformation();
    SystemInformation *GetSystemInformation();

private:
	bool m_bIsAtuoConnect;
	bool m_bReportOutOfVolume;
	bool m_bDisplayErrorsWhileTracking;    //display the error while tracking
	bool m_bLogToFile;
	bool m_bClearLogFile;
    bool m_bDateTimeStampFile;
    
	bool m_bSerialPortOpened;
	bool m_bResetHardware;                //reset hardware variable
    bool m_bWireless;                     //uses the wireless compatible settings
    
	bool m_bIsNewPortsActiveFailed;

	int m_nCOMPort;                       //the current com port number
	int m_nTimeout;                       //timeout value in seconds
	int m_nDefaultTimeout;                //default timeout value in seconds
    
	int  m_nBaudRate;
    int  m_nParity;
    int  m_nStopBits;
    int  m_nDataBits;
    int  m_nFlowControl;
	bool m_bResetChecked;
	bool m_bWirelessChecked;

    int m_nHandlesEnabled;
	int m_nSerialBreakDelay;

	int m_nTrackingMode;
	int m_nTimeOutChoose;

	//int m_nNumBytes;
	//int m_nIndexBuffer;

    char m_szLogFile[_MAX_PATH];
    char m_szLastReply[MAX_REPLY_MSG];
    char m_szCommand[MAX_COMMAND_MSG];

	int  m_nRefHandle;
	int  m_EnabledHandleIndex[NO_HANDLES];

    QSettings *m_pSettings;
    QSettings *m_pErrorIniFile;

	//SBMENDISerialPortSettingsDlg *m_pSerialPortSettingsDlg;
    //SBMENDISystemFeaturesDlg     *m_pSystemFeaturesDlg;
	
	QSerialPort *m_pSerialPort;
    
    SBMESerialPortBuffer<char>   m_ComBuffer;
	QMap<QString, int> m_dtTimeoutValues;

	HandleInformation  m_dtHandleInformation[NO_HANDLES];
    SystemInformation  m_dtSystemInformation;

    void ReadSettings();  
    void GetComParms();
    int  ReadComPort();
    void GetErrorResponse(char *pszReply, char *pszErrorMsg);
    void ClearLogFile();

	bool bCloseCurrentComport();
	bool bOpenComport();
    bool bHardWareReset(bool bWireless);
	bool bSetSystemComParms(int nBaudRate, int nDataBits, int nParity, int nStopBits, int nFlowControl);
	bool bSetPcComParms();    
	bool bBeepSystem(int nBeeps);
	bool bInitializeSystem();
	bool bSetFiringRate();
	bool bGetSystemInfo();
	bool bInitializeAllHandles();
	bool bInitializeHandle(int nHandle);
	bool bEnableAllHandles();

	int  nLoadTTCFG(char *pszPortID);
	int  nGetHandleForPort(char *pszPortID);
	bool bLoadVirtualSROM(char *pszFileName, char *pszPhysicalPortID, bool bPassive);
    bool bFreeAllHandles();
    bool bGetHandleInformation(int nPortHandle);

    void ErrorMessage();
    void WarningMessage();
	bool bCreateTimeoutTable();
	int  nLookupTimeout(char *szCommand);
    
	void ApplyXfrms();
	bool bSendCommand(char *m_szCommand, bool bAddCRC);
    bool bGetResponse();
	bool bGetBinaryResponse();
	int  nVerifyResponse(char *pszReply, bool bCheckCRC);
	bool bCheckResponse(int nReturnedValue);
    void LogToFile(int nDirection, char *psz);

signals:
	void m_signalNDIAutoInitialized();
	//void m_signalSetProgramOptions();
	void m_signalSystemTypeGot(int nSystemType);
    void m_signalHandlesEnabledGot(int HandlesEnabled);

	void m_signalGetSystemTransformData(int bPortOccupied, bool isnewportsactivefailed);

	//messageboxsignal
	void m_signalInitErrorDetermineSystemType();
	void m_signalInitErrorInitializeSystem();
	void m_signalOpenLogFileError();
	void m_signalComportOpened();
	void m_signalComPortOpenFailure();
	void m_signalPINITError(char *);
	void m_signalSROMError(char *);
	void m_signalSROMImageError(char *);
	void m_signalErrorMessage(char *, char *);
	void m_signalWarningMessage(char *, char *);
	void m_signalWriteTimeoutError();
	void m_signalProcessTimeoutError();
	void m_signalReadTimeoutError();
	void m_signalCRCError();
	void m_signalInvalidResponseError();
	void m_signalLogFileError(char *);

private slots:
	bool m_slotGetSystemTransformData();
	void m_slotTrackingMode(int nTrackingMode);
	void m_slotTimeOutChoose(int);
	void m_slotCOMPortParametersChange();

//≤‚ ‘¥˙¬Î
private:
	//≤‚ ‘¥˙¬Î
	int temp;
	//char temp_szCommand[MAX_COMMAND_MSG];
	//≤‚ ‘¥˙¬Î
//≤‚ ‘¥˙¬Î
};

#endif // SBMENDICONTROLLER_H
