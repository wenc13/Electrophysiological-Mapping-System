#ifndef SBMEMAINWINDOW_H
#define SBMEMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
//#include <QMenu>
#include <QAction>
#include <QTimer>

#include "SBMENDIController.h"
#include "SBMENDIRomFileDlg.h"
#include "SBMEDeformModel.h"
#include "SBMENDIHandleCardDlg.h"
#include "SBMEQGL3DEAModeling.h"
#include "SBMEECGAcquisitionDlg.h"
#include "SBMEColorDlg.h"
#include "SBMEStereoProjectorControlPanelDlg.h"
#include "SBMEECGControlPanelDlg.h"
#include "SBMENDISerialPortSettingsDlg.h"
#include "SBMENDIProgramOptionDlg.h"
#include "SBMENDISystemFeaturesDlg.h"

//class SBMEQGL3DEAModeling;
//class SBMEECGAcquisitionDlg;
//class SBMEECGAnalysisDlg;
//class SBMEPointDlg;

/*namespace Ui
{
    class SBMEMainWindow;
}*/

class SBMEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SBMEMainWindow(QWidget *parent = 0);
    ~SBMEMainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private:
    //Ui::SBMEMainWindow *ui;
	QMenu *m_pFileMenu;
	QMenu *m_pEditMenu;
	QMenu *m_pViewMenu;
	QMenu *m_pNDIMenu;
	QMenu *m_pECGMenu;
	QMenu *m_p3DModelMenu;
	QMenu *m_pWindowMenu;
	QMenu *m_pHelpMenu;

	QMenu *m_pFiringRateMenu;

	QToolBar *m_pNDIToolBar;

	//m_pViewMenu
	QAction *m_pViewInModelAction;
	QAction *m_pViewSampledPointsOnlyAction;
	QAction *m_pPerspectiveAction;

	//m_pNDIMenu
	QAction *m_pAutoConnectAction;
	QAction *m_pSerialPortSettingsAction;
	QAction *m_pProgramOptionsAction;
	QAction *m_pSROMImageFileSettingsAction;
	QAction *m_pSystemFeaturesAction;
	
	QAction *m_pResetSystemAction;
	QAction *m_pInitializeSystemAction;
	QAction *m_pActivateAllHandlesAction;
	QAction *m_pStartTrackingAction;
	QAction *m_pStopTrackingAction;

	QAction *m_pFiringRate20Action;
	QAction *m_pFiringRate30Action;
	QAction *m_pFiringRate60Action;

	QAction *m_pEulerAngleFormatAction;
	QAction *m_pLargeSymbolAction;
	QAction *m_pExtendedVolumeAction;

	QAction *m_pTXModeAction;
	QAction *m_pBXModeAction;

	//m_pECGMenu
	//QAction *m_pSelectECGChannelAction;

	//m_p3DModelMenu
	QAction *m_pNew3DEAModelAction;
	QAction *m_pLoad3DEAModelAction;
	QAction *m_pLoad3DCTMRModelAction;
	QAction *m_pInsertPointAction;
	QAction *m_pDeletePointAction;

	//m_pHelpMenu
	QAction *m_pAboutAction;
	QAction *m_pAboutQtAction;
	QAction *m_pAboutOpenGLAction;
	QAction *m_pAboutNDIAction;

    //QDockWidget *m_pQGL3DEAModelingAddDock;
	QDockWidget *m_pColorPanelDock;
	QDockWidget *m_pStereoProjectorControlPanelDock;
	QDockWidget *m_pHandlesPanelDock;
	//ÐÞ¸ÄÓÚ2015/06/18
	QDockWidget *m_pQGL3DEAModelingAddDock;

	QDockWidget *m_pECGAcquisitionDlgDock;
	QDockWidget *m_pECGControlPanelDock;

	SBMENDIController                  *m_pNDIController;
	SBMENDIRomFileDlg                  *m_pRomFileDlg;
	SBMEECGControlPanelDlg             *m_pECGControlPanelDlg;
	SBMEECGAcquisitionDlg              *m_pECGAcquisitionDlg;
	SBMEColorDlg                       *m_pColorDlg;
	SBMEStereoProjectorControlPanelDlg *m_pStereoProjectorControlPanelDlg;
	SBMENDISerialPortSettingsDlg       *m_pSerialPortSettingsDlg;

	SBMEDeformModel                    *m_pDeformationModel;
	SBMEQGL3DEAModeling                *m_pQGL3DEAModeling;
    SBMEQGL3DEAModeling                *m_pQGL3DEAModelingAdd;

	SBMENDIHandleCardDlg *m_HandlesCardDlgList[NO_HANDLES];
	QTabWidget *m_pHandlesPanel;
	//QTabBar *m_pTXMode;
	//QTabBar *m_pBXMode;
	bool m_ReferenceHandle[NO_HANDLES];

	QThread *m_pThreadNDIAcquisition;
	
	//QTimer  *m_pSerialPortRecivTimer;

	QTimer  *m_pNDIAcquisitionTimer;
	QFile   *m_pModelFile;

	HandleInformation    *m_pDtHandleInformation;
	SystemInformation    *m_pDtSystemInformation;

	int  *m_pEnabledHandleIndex;

	bool m_bPreInitiation;
	bool m_bSystemInitialized;
	bool m_bIsTracking;
	bool m_bPortsActivated;
	bool m_bUseEulerAngles;
	
	int  m_nRefHandle;
	int  m_nHandlesEnabled;
	int	 m_nTrackingMode;
	int  m_nFrameNumber;
	
    QLabel     *m_pConnectedStatus;
    QLabel     *m_pTrackingStatus;
	QLCDNumber *m_pFrameNumber;
	QLabel     *m_pSystemStatus;

	QString m_szSystemMode;

	void CreateActions();
	void CreateMenuBar();
	void CreateToolBars();
	void CreateWindows();
	void CreatContextMenu();
    void CreateStatusBar();
	void CreateConnections();

	void SetMode(int nMode);

signals:
	void m_signalSystemModeChanged(QString Systemstatus);
	void m_signalNDIAcquisitionstart();
	void m_signalTrackingMode(int nTrackingMode);
	void m_signalTimeOutChoose(int);

private slots:
	//View
	void m_slotViewInOrOutModel(bool isViewIn);
	void m_slotViewSampledPointsOnly(bool isViewSampledPointsOnly);
	void m_slotPerspectiveOrOrtho(bool isPespective);
	
	//NDI
	void m_slotAutoConnect(bool isAutoConnect);
	void m_slotSetCommPort();
	void m_slotSetProgramOptions();
	void m_slotSROMFileSettings();
	void m_slotViewSystemFeatures();
	
	void m_slotResetSystem();
	void m_slotInitializeSystem();
	bool m_slotActivateAllHandles();
	    void m_slotEnableDisableHandle(int cardIndex, int portIndex, bool bEnable);
		void m_slotSetHandleModel(int portIndex, int model);
        void m_slotSetHandleColor(int portIndex, QColor color);
		void m_slotSetReferenceHandle(int cardIndex, int portIndex);
        void m_slotSetActiveHandle(int idx);
	bool m_slotStartTracking();
	bool m_slotStopTracking();
	
	void m_slotFiringRate20Hz();
    void m_slotFiringRate30Hz();
    void m_slotFiringRate60Hz();

	void m_slotEulerAngles(bool isUseEulerAngles);
	void m_slotLargerSymbol(bool isLargerSymbol);
	void m_slotExtendedVolume(bool isExtendedVolume);

	void m_slotTXMode();
	void m_slotBXMode();

	//ECG
	//void m_slotSelectECGChannel();
	
	//3D Model
	void m_slotNew3DEAModel();
    void m_slotLoad3DEAModel();
    void m_slotLoad3DCTMRModel();
	void m_slotInsertPoint();
	void m_slotDeletePoint();

	//Help
	void m_slotAbout();
	void m_slotAboutQt();
	void m_slotAboutOpenGL();
	void m_slotAboutNDI();

	//
	bool m_slotDisplaySystemTransformData(int bPortOccupied, bool isNewPortsActiveFailed);

	void m_slotSetSystemType(int nSystemType);
	void m_slotNDIAutoInitialized();
	void m_slotSetHandlesEnabled(int HandlesEnabled);

	void m_slotRomFileChanged();

	void m_slotUpdateStatusBar(QString SysTemstatus);

	//messageboxslot
	void m_slotInitErrorDetermineSystemType();
	void m_slotInitErrorInitializeSystem();
	void m_slotOpenLogFileError();
	void m_slotComportOpened();
	void m_slotComPortOpenFailure();
	void m_slotPINITError(char *);
	void m_slotSROMError(char *);
	void m_slotSROMImageError(char *);
	void m_slotErrorMessage(char *, char *);
	void m_slotWarningMessage(char *, char *);
	void m_slotWriteTimeoutError();
	void m_slotProcessTimeoutError();
	void m_slotReadTimeoutError();
	void m_slotCRCError();
	void m_slotInvalidResponseError();
	void m_slotLogFileError(char *);
};

#endif // SBMEMAINWINDOW_H
