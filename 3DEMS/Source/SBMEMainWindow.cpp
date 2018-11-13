#include "SBMEMainWindow.h"
//#include "ui_SBMEMainWindow.h"

//#include "SBMEQGL3DEAModeling.h"
//#include "SBMEECGAnalysisDlg.h"
//#include "SBMEPointDlg.h"
#include "SBMENDIAuxiliary.h"

SBMEMainWindow::SBMEMainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //ui(new Ui::SBMEMainWindow)
{
    //ui->setupUi(this);
    setWindowIcon(QIcon(":/Images/Images/THU-logo.png"));
    //setWindowState(Qt::WindowFullScreen);
	//showMaximized();

	m_bPreInitiation     = false;
	m_bSystemInitialized = false;
	m_bIsTracking        = false;
	m_bPortsActivated    = false;
	m_bUseEulerAngles    = false;

	m_nRefHandle         = -1;
	m_nHandlesEnabled    = 0;
	m_nTrackingMode      = 0;
	m_nFrameNumber       = 0;

	m_szSystemMode       = "";

	//修改于2015/05/13
	//m_pNDIController = new SBMENDIController(this);
	m_pNDIController                  = new SBMENDIController();
    m_pEnabledHandleIndex             = m_pNDIController->GetEnnabledHandleIndex();
	m_pDtHandleInformation            = m_pNDIController->GetHandleInformation();
	m_pDtSystemInformation            = m_pNDIController->GetSystemInformation();
    
    m_pRomFileDlg                     = new SBMENDIRomFileDlg;
	m_pECGControlPanelDlg             = new SBMEECGControlPanelDlg;
	m_pECGAcquisitionDlg              = new SBMEECGAcquisitionDlg;
	m_pColorDlg                       = new SBMEColorDlg;
	m_pStereoProjectorControlPanelDlg = new SBMEStereoProjectorControlPanelDlg;
	m_pSerialPortSettingsDlg          = new SBMENDISerialPortSettingsDlg(this);
	m_pDeformationModel               = new SBMEDeformModel;

	m_pQGL3DEAModeling                = new SBMEQGL3DEAModeling;
	m_pQGL3DEAModelingAdd             = new SBMEQGL3DEAModeling(0, SBMEQGL3DEAModeling::AddView);
	m_pQGL3DEAModeling->Set3DEAModel(m_pDeformationModel);
    m_pQGL3DEAModelingAdd->Set3DEAModel(m_pDeformationModel);
	m_pQGL3DEAModeling->SetColorMappingBar(m_pColorDlg->GetColorMappingBar());
    m_pQGL3DEAModelingAdd->SetColorMappingBar(m_pColorDlg->GetColorMappingBar());

	

	m_HandlesCardDlgList[0] = new SBMENDIHandleCardDlg;
	m_HandlesCardDlgList[0]->SetReferenceHandleEnabled(false);
	m_pHandlesPanel = new QTabWidget;
    m_pHandlesPanel->insertTab(0, m_HandlesCardDlgList[0], QIcon(":/Images/Images/ball0"), QString("HandleNO."));
	for (int i = 0; i < NO_HANDLES; i++)
		m_ReferenceHandle[i] = true;

	m_pThreadNDIAcquisition = new QThread;
	m_pNDIController->moveToThread(m_pThreadNDIAcquisition);

	//m_pSerialPortRecivTimer = new QTimer(this);
    //m_pSerialPortRecivTimer->setInterval(SBME_NDI_COM_RECIEVE_INTERVAL);

	m_pNDIAcquisitionTimer = new QTimer(this);
	m_pNDIAcquisitionTimer->setInterval(SBME_NDI_COM_RECIEVE_INTERVAL);

	m_pModelFile = NULL;
	
	m_pConnectedStatus = new QLabel;
	m_pTrackingStatus  = new QLabel;
	m_pFrameNumber     = new QLCDNumber;
	m_pSystemStatus    = new QLabel("Ready");

	CreateActions();
	CreateMenuBar();
	CreateToolBars();
	CreateWindows();
	CreatContextMenu();
    CreateStatusBar();
	CreateConnections();

	SetMode(MODE_PRE_INIT);

	m_pThreadNDIAcquisition->start();
    //m_pNDIController->AutoConnect();
}

SBMEMainWindow::~SBMEMainWindow()
{
    //delete ui;
}

void SBMEMainWindow::closeEvent(QCloseEvent *event)
{
	int ret = QMessageBox::question(this, "Attention!", "Do you really want to exit?",
		                            QMessageBox::Yes, QMessageBox::No);
	if (ret == QMessageBox::Yes)

		event->accept();
	else
		event->ignore();
}

void SBMEMainWindow::CreateActions()
{
	//View
	m_pViewInModelAction = new QAction(tr("View in Model"), this);
	//m_pViewInModelAction->setIcon(QIcon(""));
	//m_pViewInModelAction->setShortcut();
	//m_pViewInModelAction->setStatusTip(tr(""));
	//m_pViewInModelAction->setCheckable(true);
	connect(m_pViewInModelAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotViewInOrOutModel(bool)));
	
	m_pViewSampledPointsOnlyAction = new QAction(tr("View Sampled Points Only"), this);
	//m_pViewSampledPointsOnlyAction->setIcon(QIcon(""));
	//m_pViewSampledPointsOnlyAction->setShortcut();
	//m_pViewSampledPointsOnlyAction->setStatusTip(tr(""));
	m_pViewSampledPointsOnlyAction->setCheckable(true);
	m_pViewSampledPointsOnlyAction->setChecked(true);
	connect(m_pViewSampledPointsOnlyAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotViewSampledPointsOnly(bool)));

	m_pPerspectiveAction = new QAction(tr("Perspective"), this);
	//m_pPerspectiveAction->setIcon(QIcon(""));
	//m_pPerspectiveAction->setShortcut();
	//m_pPerspectiveAction->setStatusTip(tr(""));
	m_pPerspectiveAction->setCheckable(true);
	m_pPerspectiveAction->setChecked(true);
	connect(m_pPerspectiveAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotPerspectiveOrOrtho(bool)));
	
	//NDI
	m_pAutoConnectAction = new QAction(tr("Auto Connection"), this);
	//m_pAutoConnectAction->setIcon(QIcon(""));
	//m_pAutoConnectAction->setShortcut();
	//m_pAutoConnectAction->setStatusTip(tr(""));
	m_pAutoConnectAction->setCheckable(true);
	connect(m_pAutoConnectAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotAutoConnect(bool)));

	m_pSerialPortSettingsAction = new QAction(tr("Serial Port Settings"), this);
	m_pSerialPortSettingsAction->setIcon(QIcon(":Images/Images/SerialPortSettings.png"));
	//m_pSerialPortSettingsAction->setShortcut();
	//m_pSerialPortSettingsAction->setStatusTip(tr(""));
	//m_pSerialPortSettingsAction->setCheckable(true);
	connect(m_pSerialPortSettingsAction,  SIGNAL(triggered()), this, SLOT(m_slotSetCommPort()));

	m_pProgramOptionsAction = new QAction(tr("Program Options"), this);
	//m_pProgramOptionsAction->setIcon(QIcon(""));
	//m_pProgramOptionsAction->setShortcut();
	//m_pProgramOptionsAction->setStatusTip(tr(""));
	//m_pProgramOptionsAction->setCheckable(true);
	connect(m_pProgramOptionsAction,  SIGNAL(triggered()), this, SLOT(m_slotSetProgramOptions()));
	
	m_pSROMImageFileSettingsAction = new QAction(tr("Load SROM Files"), this);
	//m_pSROMImageFileSettingsAction->setIcon(QIcon(""));
	//m_pSROMImageFileSettingsAction->setShortcut();
	//m_pSROMImageFileSettingsAction->setStatusTip(tr(""));
	//m_pSROMImageFileSettingsAction->setCheckable(true);
	connect(m_pSROMImageFileSettingsAction,  SIGNAL(triggered()), this, SLOT(m_slotSROMFileSettings()));

	m_pSystemFeaturesAction = new QAction(tr("System Features"), this);
	//m_pSystemFeaturesAction->setIcon(QIcon(""));
	//m_pSystemFeaturesAction->setShortcut();
	//m_pSystemFeaturesAction->setStatusTip(tr(""));
	//m_pSystemFeaturesAction->setCheckable(true);
	connect(m_pSystemFeaturesAction,  SIGNAL(triggered()), this, SLOT(m_slotViewSystemFeatures()));

	m_pResetSystemAction = new QAction(tr("Reset System"), this);
	m_pResetSystemAction->setIcon(QIcon(":Images/Images/ResetSystem.png"));
	//m_pResetSystemAction->setShortcut();
	//m_pResetSystemAction->setStatusTip(tr(""));
	//m_pResetSystemAction->setCheckable(true);
	connect(m_pResetSystemAction,  SIGNAL(triggered()), this, SLOT(m_slotResetSystem()));

	m_pInitializeSystemAction = new QAction(tr("Initialize System"), this);
	m_pInitializeSystemAction->setIcon(QIcon(":Images/Images/Initialize System.png"));
	//m_pInitializeSystemAction->setShortcut();
	//m_pInitializeSystemAction->setStatusTip(tr(""));
	//m_pInitializeSystemAction->setCheckable(true);
	connect(m_pInitializeSystemAction,  SIGNAL(triggered()), this, SLOT(m_slotInitializeSystem()));

	m_pActivateAllHandlesAction = new QAction(tr("Activate All Handles"), this);
	m_pActivateAllHandlesAction->setIcon(QIcon(":Images/Images/activate.png"));
	//m_pActivateAllHandlesAction->setShortcut();
	//m_pActivateAllHandlesAction->setStatusTip(tr(""));
	//m_pActivateAllHandlesAction->setCheckable(true);
	connect(m_pActivateAllHandlesAction,  SIGNAL(triggered()), this, SLOT(m_slotActivateAllHandles()));

	m_pStartTrackingAction = new QAction(tr("Start Tracking"), this);
	m_pStartTrackingAction->setIcon(QIcon(":Images/Images/start.png"));
	//m_pStartTrackingAction->setShortcut();
	//m_pStartTrackingAction->setStatusTip(tr(""));
	//m_pStartTrackingAction->setCheckable(true);
	connect(m_pStartTrackingAction,  SIGNAL(triggered()), this, SLOT(m_slotStartTracking()));

	m_pStopTrackingAction = new QAction(tr("Stop Tracking"), this);
	m_pStopTrackingAction->setIcon(QIcon(":Images/Images/pause.png"));
	//m_pStopTrackingAction->setShortcut();
	//m_pStopTrackingAction->setStatusTip(tr(""));
	//m_pStopTrackingAction->setCheckable(true);
	connect(m_pStopTrackingAction,  SIGNAL(triggered()), this, SLOT(m_slotStopTracking()));

	m_pFiringRate20Action = new QAction(tr("Rate 20 Hz"), this);
	connect(m_pFiringRate20Action,  SIGNAL(triggered()), this, SLOT(m_slotFiringRate20Hz()));
	m_pFiringRate30Action = new QAction(tr("Rate 30 Hz"), this);
	connect(m_pFiringRate30Action,  SIGNAL(triggered()), this, SLOT(m_slotFiringRate30Hz()));
	m_pFiringRate60Action = new QAction(tr("Rate 60 Hz"), this);
	connect(m_pFiringRate60Action,  SIGNAL(triggered()), this, SLOT(m_slotFiringRate60Hz()));
	m_pFiringRateMenu = new QMenu(tr("Firing Rate"),this);

	m_pEulerAngleFormatAction = new QAction(tr("Euler Angle Format"), this);
	//m_pEulerAngleFormatAction->setIcon(QIcon(""));
	//m_pEulerAngleFormatAction->setShortcut();
	//m_pEulerAngleFormatAction->setStatusTip(tr(""));
	m_pEulerAngleFormatAction->setCheckable(true);
	m_pEulerAngleFormatAction->setChecked(false);
	connect(m_pEulerAngleFormatAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotEulerAngles(bool)));

	m_pLargeSymbolAction = new QAction(tr("Large Symbol"), this);
	//m_pLargeSymbolAction->setIcon(QIcon(""));
	//m_pLargeSymbolAction->setShortcut();
	//m_pLargeSymbolAction->setStatusTip(tr(""));
	m_pLargeSymbolAction->setCheckable(true);
	m_pLargeSymbolAction->setChecked(false);
	connect(m_pLargeSymbolAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotLargerSymbol(bool)));

	m_pExtendedVolumeAction = new QAction(tr("Extended Volume Action"), this);
	//m_pExtendedVolumeAction->setIcon(QIcon(""));
	//m_pExtendedVolumeAction->setShortcut();
	//m_pExtendedVolumeAction->setStatusTip(tr(""));
	m_pExtendedVolumeAction->setCheckable(true);
	m_pExtendedVolumeAction->setChecked(true);
	connect(m_pExtendedVolumeAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotExtendedVolume(bool)));

	m_pTXModeAction = new QAction(tr("TX Mode (ASCII Return)"), this);
	//m_pTXModeAction->setIcon(QIcon(""));
	//m_pTXModeAction->setShortcut();
	//m_pTXModeAction->setStatusTip(tr(""));
	m_pTXModeAction->setCheckable(true);
	m_pTXModeAction->setChecked(true);
	connect(m_pTXModeAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotTXMode()));

	m_pBXModeAction = new QAction(tr("BX Mode (Binary Return)"), this);
	//m_pBXModeAction->setIcon(QIcon(""));
	//m_pBXModeAction->setShortcut();
	//m_pBXModeAction->setStatusTip(tr(""));
	m_pBXModeAction->setCheckable(true);
	m_pBXModeAction->setChecked(false);
	connect(m_pBXModeAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotBXMode()));

	//ECG
	//m_pSelectECGChannelAction = new QAction(tr("Select ECG Channel"), this);
	//m_pSelectECGChannelAction->setIcon(QIcon(""));
	//m_pSelectECGChannelAction->setShortcut();
	//m_pSelectECGChannelAction->setStatusTip(tr(""));
	//m_pSelectECGChannelAction->setCheckable(true);
	//m_pSelectECGChannelAction->setChecked(false);
	//connect(m_pSelectECGChannelAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotSelectECGChannel()));

	//3D Model
	m_pNew3DEAModelAction = new QAction(tr("New 3D EA Model"), this);
	//m_pNew3DEAModelAction->setIcon(QIcon(""));
	//m_pNew3DEAModelAction->setShortcut();
	//m_pNew3DEAModelAction->setStatusTip(tr(""));
	//m_pNew3DEAModelAction->setCheckable(true);
	connect(m_pNew3DEAModelAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotNew3DEAModel()));

	m_pLoad3DEAModelAction = new QAction(tr("Load 3D EA Model"), this);
	//m_pLoad3DEAModelAction->setIcon(QIcon(""));
	//m_pLoad3DEAModelAction->setShortcut();
	//m_pLoad3DEAModelAction->setStatusTip(tr(""));
	//m_pLoad3DEAModelAction->setCheckable(true);
	connect(m_pLoad3DEAModelAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotLoad3DEAModel()));

	m_pLoad3DCTMRModelAction = new QAction(tr("Load 3D CT/MR Model"), this);
	//m_pLoad3DCTMRModelAction->setIcon(QIcon(""));
	//m_pLoad3DCTMRModelAction->setShortcut();
	//m_pLoad3DCTMRModelAction->setStatusTip(tr(""));
	//m_pLoad3DCTMRModelAction->setCheckable(true);
	connect(m_pLoad3DCTMRModelAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotLoad3DCTMRModel()));

	m_pInsertPointAction = new QAction(tr("Insert Point"), this);
	//m_pInsertPointAction->setIcon(QIcon(""));
	//m_pInsertPointAction->setShortcut();
	//m_pInsertPointAction->setStatusTip(tr(""));
	//m_pInsertPointAction->setCheckable(true);
	connect(m_pInsertPointAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotInsertPoint()));
	m_pInsertPointAction->setDisabled(true);

	m_pDeletePointAction = new QAction(tr("Delete Point"), this);
	//m_pDeletePointAction->setIcon(QIcon(""));
	//m_pDeletePointAction->setShortcut();
	//m_pDeletePointAction->setStatusTip(tr(""));
	//m_pDeletePointAction->setCheckable(true);
	connect(m_pDeletePointAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotDeletePoint()));
	m_pDeletePointAction->setDisabled(true);

	//Help
	m_pAboutAction = new QAction(tr("About"), this);
	m_pAboutAction->setIcon(QIcon(":/Images/Images/THU-logo.png"));
	//m_pAboutAction->setShortcut();
	//m_pAboutAction->setStatusTip(tr(""));
	//m_pAboutAction->setCheckable(true);
	connect(m_pAboutAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotAbout()));

	m_pAboutQtAction = new QAction(tr("About Qt"), this);
	m_pAboutQtAction->setIcon(QIcon(":/Images/Images/Qt.png"));
	//m_pAboutQtAction->setShortcut();
	//m_pAboutQtAction->setStatusTip(tr(""));
	//m_pAboutQtAction->setCheckable(true);
	connect(m_pAboutQtAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotAboutQt()));

	m_pAboutOpenGLAction = new QAction(tr("About OpenGL"), this);
	m_pAboutOpenGLAction->setIcon(QIcon(":/Images/Images/OpenGL.png"));
	//m_pAboutOpenGLAction->setShortcut();
	//m_pAboutOpenGLAction->setStatusTip(tr(""));
	//m_pAboutOpenGLAction->setCheckable(true);
	connect(m_pAboutOpenGLAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotAboutOpenGL()));

	m_pAboutNDIAction = new QAction(tr("About NDI"), this);
	m_pAboutNDIAction->setIcon(QIcon(":/Images/Images/NDI_Logo.png"));
	//m_pAboutNDIAction->setShortcut();
	//m_pAboutNDIAction->setStatusTip(tr(""));
	//m_pAboutNDIAction->setCheckable(true);
	connect(m_pAboutNDIAction,  SIGNAL(triggered(bool)), this, SLOT(m_slotAboutNDI()));

}

void SBMEMainWindow::CreateMenuBar()
{
	m_pFileMenu = menuBar()->addMenu(tr("File"));

	m_pEditMenu = menuBar()->addMenu(tr("Edit"));

	m_pViewMenu = menuBar()->addMenu(tr("View"));
	m_pViewMenu->addAction(m_pViewInModelAction);
	m_pViewMenu->addAction(m_pViewSampledPointsOnlyAction);
	m_pViewMenu->addAction(m_pPerspectiveAction);

	m_pNDIMenu = menuBar()->addMenu(tr("NDI"));
	m_pNDIMenu->addAction(m_pAutoConnectAction);
	m_pNDIMenu->addAction(m_pSerialPortSettingsAction);
	m_pNDIMenu->addAction(m_pProgramOptionsAction);
	m_pNDIMenu->addAction(m_pSROMImageFileSettingsAction);
	m_pNDIMenu->addAction(m_pSystemFeaturesAction);
	
	m_pNDIMenu->addSeparator();

	m_pNDIMenu->addAction(m_pResetSystemAction);
	m_pNDIMenu->addAction(m_pInitializeSystemAction);
	m_pNDIMenu->addAction(m_pActivateAllHandlesAction);
	m_pNDIMenu->addAction(m_pStartTrackingAction);
	m_pNDIMenu->addAction(m_pStopTrackingAction);

	m_pNDIMenu->addSeparator();

	m_pFiringRateMenu->addAction(m_pFiringRate20Action);
	m_pFiringRateMenu->addAction(m_pFiringRate30Action);
	m_pFiringRateMenu->addAction(m_pFiringRate60Action);
	m_pNDIMenu->addMenu(m_pFiringRateMenu);

	m_pNDIMenu->addAction(m_pEulerAngleFormatAction);
	m_pNDIMenu->addAction(m_pLargeSymbolAction);
	m_pNDIMenu->addAction(m_pExtendedVolumeAction);

	m_pNDIMenu->addAction(m_pTXModeAction);
	m_pNDIMenu->addAction(m_pBXModeAction);

	m_pECGMenu = menuBar()->addMenu(tr("ECG"));
	//m_pECGMenu->addAction(m_pSelectECGChannelAction);

	m_p3DModelMenu = menuBar()->addMenu(tr("3D Model"));
	m_p3DModelMenu->addAction(m_pNew3DEAModelAction);
	m_p3DModelMenu->addAction(m_pLoad3DEAModelAction);
	m_p3DModelMenu->addAction(m_pLoad3DCTMRModelAction);
	m_p3DModelMenu->addAction(m_pInsertPointAction);
	m_p3DModelMenu->addAction(m_pDeletePointAction);

	m_pWindowMenu = menuBar()->addMenu(tr("Window"));

	m_pHelpMenu = menuBar()->addMenu(tr("Help"));
	m_pHelpMenu->addAction(m_pAboutAction);
	m_pHelpMenu->addAction(m_pAboutQtAction);
	m_pHelpMenu->addAction(m_pAboutOpenGLAction);
	m_pHelpMenu->addAction(m_pAboutNDIAction);
}

void SBMEMainWindow::CreateToolBars()
{
    m_pNDIToolBar = addToolBar(tr("NDI"));
	m_pNDIToolBar->addAction(m_pInitializeSystemAction);
	m_pNDIToolBar->addAction(m_pActivateAllHandlesAction);
	m_pNDIToolBar->addAction(m_pStartTrackingAction);
	m_pNDIToolBar->addAction(m_pStopTrackingAction);
}

void SBMEMainWindow::CreateWindows()
{
    //m_pQGL3DEAModeling = new SBMEQGL3DEAModeling(this, SBMEQGL3DEAModeling::MainView);
    setCentralWidget(m_pQGL3DEAModeling);

    //m_pQGL3DEAModelingAddDock = new QDockWidget(tr("3D Navigation"), this);
    //m_pQGL3DEAModelingAdd = new SBMEQGL3DEAModeling(this, SBMEQGL3DEAModeling::AddView);
    //m_pQGL3DEAModelingAddDock->setWidget(m_pQGL3DEAModelingAdd);
    //addDockWidget(Qt::BottomDockWidgetArea, m_pQGL3DEAModelingAddDock);

    //m_pECGAnalysisDlgDock = new QDockWidget(tr("ECG Analysis"), this);
    //m_pSBMEECGAnalysisDlg = new SBMEECGAnalysisDlg;
    //m_pECGAnalysisDlgDock->setWidget(m_pSBMEECGAnalysisDlg);
    //addDockWidget(Qt::RightDockWidgetArea, m_pECGAnalysisDlgDock);

    //m_pPointDlgDock = new QDockWidget(tr("Point Panel"), this);
    //m_pSBMEPointDlg = new SBMEPointDlg;
    //m_pPointDlgDock->setWidget(m_pSBMEPointDlg);
    //addDockWidget(Qt::LeftDockWidgetArea, m_pPointDlgDock);

	m_pColorPanelDock = new QDockWidget(tr("Color Panel"), this);
	m_pColorPanelDock->setWidget(m_pColorDlg);
    addDockWidget(Qt::LeftDockWidgetArea, m_pColorPanelDock);

	m_pStereoProjectorControlPanelDock = new QDockWidget(tr("Stereo Projector Panel"), this);
	m_pStereoProjectorControlPanelDock->setWidget(m_pStereoProjectorControlPanelDlg);
    addDockWidget(Qt::LeftDockWidgetArea, m_pStereoProjectorControlPanelDock);

	//修改于2015/06/18
	m_pQGL3DEAModelingAddDock = new QDockWidget(tr("3D Navigation"), this);
	m_pQGL3DEAModelingAddDock->setWidget(m_pQGL3DEAModelingAdd);
	addDockWidget(Qt::RightDockWidgetArea, m_pQGL3DEAModelingAddDock);

	m_pHandlesPanelDock = new QDockWidget(tr("Handles Panel"), this);
	m_pHandlesPanelDock->setWidget(m_pHandlesPanel);
    addDockWidget(Qt::BottomDockWidgetArea, m_pHandlesPanelDock);

	m_pECGAcquisitionDlgDock = new QDockWidget(tr("ECG Acquisition"), this);
    //m_pSBMEECGAcquisitionDlg = new SBMEECGAcquisitionDlg;
    m_pECGAcquisitionDlgDock->setWidget(m_pECGAcquisitionDlg);
    addDockWidget(Qt::BottomDockWidgetArea, m_pECGAcquisitionDlgDock);

	m_pECGControlPanelDock = new QDockWidget(tr("Select ECG Channel"), this);
	m_pECGControlPanelDock->setWidget(m_pECGControlPanelDlg);
	addDockWidget(Qt::BottomDockWidgetArea, m_pECGControlPanelDock);
}

void SBMEMainWindow::CreatContextMenu()
{
	m_pQGL3DEAModeling->addAction(m_pInsertPointAction);
	m_pQGL3DEAModeling->addAction(m_pDeletePointAction);
	m_pQGL3DEAModeling->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void SBMEMainWindow::CreateStatusBar()
{
	m_pSystemStatus->setAlignment(Qt::AlignVCenter);
    m_pSystemStatus->setMinimumSize(m_pSystemStatus->sizeHint());
    statusBar()->addWidget(m_pConnectedStatus);
    statusBar()->addWidget(m_pTrackingStatus);
    statusBar()->addWidget(m_pFrameNumber);
    statusBar()->addWidget(m_pSystemStatus);
    connect(this, SIGNAL(m_signalSystemModeChanged(QString)), this, SLOT(m_slotUpdateStatusBar(QString)));
}

void SBMEMainWindow::CreateConnections()
{
    connect(this, SIGNAL(m_signalNDIAcquisitionstart()), m_pNDIController, SLOT(m_slotGetSystemTransformData()));
	connect(this, SIGNAL(m_signalTrackingMode(int)),     m_pNDIController, SLOT(m_slotTrackingMode(int)));
	connect(this, SIGNAL(m_signalTimeOutChoose(int)),    m_pNDIController, SLOT(m_slotTimeOutChoose(int)));
	
	//connect(m_pSerialPortRecivTimer, SIGNAL(timeout()), this, SLOT(m_slotGetSystemTransformData()));
	//connect(m_pNDIAcquisitionTimer, SIGNAL(timeout()), m_pNDIController, SLOT(m_slotGetSystemTransformData()));
	
	connect(m_pNDIController, SIGNAL(m_signalSystemTypeGot(int)),                this, SLOT(m_slotSetSystemType(int)));
    connect(m_pNDIController, SIGNAL(m_signalNDIAutoInitialized()),              this, SLOT(m_slotNDIAutoInitialized()));
    connect(m_pNDIController, SIGNAL(m_signalHandlesEnabledGot(int)),            this, SLOT(m_slotSetHandlesEnabled(int)));
	connect(m_pNDIController, SIGNAL(m_signalGetSystemTransformData(int, bool)), this, SLOT(m_slotDisplaySystemTransformData(int, bool)));

	connect(m_pNDIController, SIGNAL(m_signalInitErrorDetermineSystemType()), this, SLOT(m_slotInitErrorDetermineSystemType()));
    connect(m_pNDIController, SIGNAL(m_signalInitErrorInitializeSystem()),    this, SLOT(m_slotInitErrorInitializeSystem()));
    connect(m_pNDIController, SIGNAL(m_signalOpenLogFileError()),             this, SLOT(m_slotOpenLogFileError()));
	connect(m_pNDIController, SIGNAL(m_signalComportOpened()),                this, SLOT(m_slotComportOpened()));
	connect(m_pNDIController, SIGNAL(m_signalComPortOpenFailure()),           this, SLOT(m_slotComPortOpenFailure()));
	connect(m_pNDIController, SIGNAL(m_signalPINITError(char *)),             this, SLOT(m_slotPINITError(char *)));
	connect(m_pNDIController, SIGNAL(m_signalSROMError(char *)),              this, SLOT(m_slotSROMError(char *)));
	connect(m_pNDIController, SIGNAL(m_signalSROMImageError(char *)),         this, SLOT(m_slotSROMImageError(char *)));
	connect(m_pNDIController, SIGNAL(m_signalErrorMessage(char *, char *)),   this, SLOT(m_slotErrorMessage(char *, char *)));
	connect(m_pNDIController, SIGNAL(m_signalWarningMessage(char *, char *)), this, SLOT(m_slotWarningMessage(char *, char *)));
	connect(m_pNDIController, SIGNAL(m_signalWriteTimeoutError()),            this, SLOT(m_slotWriteTimeoutError()));
	connect(m_pNDIController, SIGNAL(m_signalProcessTimeoutError()),          this, SLOT(m_slotProcessTimeoutError()));
	connect(m_pNDIController, SIGNAL(m_signalReadTimeoutError()),             this, SLOT(m_slotReadTimeoutError()));
	connect(m_pNDIController, SIGNAL(m_signalCRCError()),                     this, SLOT(m_slotCRCError()));
	connect(m_pNDIController, SIGNAL(m_signalInvalidResponseError()),         this, SLOT(m_slotInvalidResponseError()));
	connect(m_pNDIController, SIGNAL(m_signalLogFileError(char *)),           this, SLOT(m_slotLogFileError(char *)));
	
	connect(m_pRomFileDlg, SIGNAL(m_signalRomFileChanged()), this, SLOT(m_slotRomFileChanged()));

	//connect(m_pQGL3DEAModeling, SIGNAL(m_signalRefreshLeftRightView(GLfloat ,GLfloat ,GLfloat ,GLfloat )), m_pQGL3DEAModelingLeft,  SLOT(m_slotRefreshWithMainView(GLfloat ,GLfloat ,GLfloat ,GLfloat )));
    //connect(m_pQGL3DEAModeling, SIGNAL(m_signalRefreshLeftRightView(GLfloat ,GLfloat ,GLfloat ,GLfloat )), m_pQGL3DEAModelingRight, SLOT(m_slotRefreshWithMainView(GLfloat ,GLfloat ,GLfloat ,GLfloat )));
    //connect(m_pQGL3DEAModeling, SIGNAL(m_signalNewPointSampled()),                                         m_pQGL3DEAModelingLeft,  SLOT(m_slotRefreshModel()));
    //connect(m_pQGL3DEAModeling, SIGNAL(m_signalNewPointSampled()),                                         m_pQGL3DEAModelingRight, SLOT(m_slotRefreshModel()));
    connect(m_pQGL3DEAModeling, SIGNAL(m_signalNewPointSampled()), m_pQGL3DEAModelingAdd,   SLOT(m_slotRefreshModel()));
	
	connect(m_pECGControlPanelDlg, SIGNAL(m_signalSelectedECGtoDispaly(int, int *)), m_pECGAcquisitionDlg, SLOT(m_slotDialogSelectedECG(int ,int *)));
	connect(m_pECGAcquisitionDlg,  SIGNAL(m_signalECGControlPanelDlgEnabled(bool)),  m_pECGControlPanelDlg, SLOT(m_slotOKButtonEnabled(bool)));
	
	connect(m_pColorDlg, SIGNAL(m_signalEnableDisableColoring(bool)),  m_pQGL3DEAModeling,      SLOT(m_slotRefreshWithColoringFlag(bool)));
    connect(m_pColorDlg, SIGNAL(m_signalColoringRadiusChanged(float)), m_pQGL3DEAModeling,      SLOT(m_slotRefreshWithColoringRadius(float)));
    connect(m_pColorDlg, SIGNAL(m_signalColorMappingChanged()),        m_pQGL3DEAModeling,      SLOT(m_slotRefreshWithColorBar()));
    connect(m_pColorDlg, SIGNAL(m_signalColorMappingChanged()),        m_pQGL3DEAModelingAdd,   SLOT(m_slotRefreshWithColorBar()));

	connect(m_pStereoProjectorControlPanelDlg, SIGNAL(m_signalFocusDistanceChanged(int)), m_pQGL3DEAModeling,      SLOT(m_slotRefreshWithFocalDistance(int)));
    connect(m_pStereoProjectorControlPanelDlg, SIGNAL(m_signalFovyChanged(int)),          m_pQGL3DEAModeling,      SLOT(m_slotRefreshWithFovy(int)));

	connect(m_pSerialPortSettingsDlg, SIGNAL(m_signalCOMPortParametersChange()), m_pNDIController, SLOT(m_slotCOMPortParametersChange()));

    //connect(m_pCoordinateRegistraionDlg,       SIGNAL(m_signalToGetNDIPoint()),           this,                    SLOT(m_slotOnGetNDIPoint()));
    //connect(m_pCoordinateRegistraionDlg,       SIGNAL(m_signalToGetModelPoint()),         this,                    SLOT(m_slotOnGetModelPoint()));
}

void SBMEMainWindow::SetMode(int nMode)
{
	switch (nMode)
    {
		case MODE_PRE_INIT:
		{
			m_pResetSystemAction->setEnabled(true);
			m_pInitializeSystemAction->setEnabled(true);
			m_pActivateAllHandlesAction->setDisabled(true);
			m_pStartTrackingAction->setDisabled(true);
			m_pStopTrackingAction->setDisabled(true);
        
			m_bPreInitiation     = true;
			m_bSystemInitialized = false;
			m_bIsTracking        = false;
        
			m_szSystemMode       = "Ready";
		
			sbme_bStopTracking   = true;
			//m_pSerialPortRecivTimer->stop();
			//m_pNDIAcquisitionTimer->stop();
        
			break;
		}
		case MODE_INIT:
		{
			m_pResetSystemAction->setEnabled(true);
			m_pInitializeSystemAction->setEnabled(true);
			m_pActivateAllHandlesAction->setEnabled(true);
			m_pStartTrackingAction->setDisabled(true);
			m_pStopTrackingAction->setDisabled(true);
        
			m_bPreInitiation     = false;
			m_bSystemInitialized = true;
			m_bIsTracking        = false;
        
			m_szSystemMode       = "System Initialized";
        
			sbme_bStopTracking   = true;
			//m_pSerialPortRecivTimer->stop();
			//m_pNDIAcquisitionTimer->stop();
        
			break;
		}
		case MODE_ACTIVATED:
		{
			m_pResetSystemAction->setEnabled(true);
			m_pInitializeSystemAction->setEnabled(true);
			m_pActivateAllHandlesAction->setEnabled(true);
			m_pStartTrackingAction->setEnabled(true);
			m_pStopTrackingAction->setDisabled(true);

			m_bIsTracking  = false;
			m_szSystemMode = "Handles Activated";

			sbme_bStopTracking = true;
			//m_pSerialPortRecivTimer->stop();
			//m_pNDIAcquisitionTimer->stop();

			break;
		}
		case MODE_TRACKING:
		{
			m_pResetSystemAction->setEnabled(true);
			m_pInitializeSystemAction->setEnabled(true);
			m_pActivateAllHandlesAction->setEnabled(true);
			m_pStartTrackingAction->setDisabled(true);
			m_pStopTrackingAction->setEnabled(true);

			m_bIsTracking  = TRUE;
			m_szSystemMode = "Tracking";

			sbme_bStopTracking = false;
			emit m_signalNDIAcquisitionstart();
			//m_pSerialPortRecivTimer->start();
			//m_pNDIAcquisitionTimer->start();

			break;
		}
    }
    if (m_bPreInitiation || m_bIsTracking)
        m_pFiringRateMenu->setDisabled(true);

    m_pSROMImageFileSettingsAction->setDisabled(m_bPreInitiation || m_bIsTracking);
    m_pSystemFeaturesAction->setDisabled(m_bPreInitiation || m_bIsTracking);

    for (int i = 0; i < m_nHandlesEnabled; i++)
    {
        m_HandlesCardDlgList[i]->EnableorDisableButton(!(m_bPreInitiation || m_bIsTracking));
    }
    emit m_signalSystemModeChanged(m_szSystemMode);
}

void SBMEMainWindow::m_slotViewInOrOutModel(bool isViewIn)
{
	m_pQGL3DEAModeling->ViewInOrOutModel(isViewIn);
    //m_pQGL3DEAModelingLeft->ViewInOrOutModel(isViewIn);
    //m_pQGL3DEAModelingRight->ViewInOrOutModel(isViewIn);
}

void SBMEMainWindow::m_slotViewSampledPointsOnly(bool isViewSampledPointsOnly)
{
	m_pQGL3DEAModeling->SetViewSampledPointsOnly(isViewSampledPointsOnly);
    m_pQGL3DEAModelingAdd->SetViewSampledPointsOnly(isViewSampledPointsOnly);
    //m_pQGL3DEAModelingLeft->SetViewSampledPointsOnly(isViewSampledPointsOnly);
    //m_pQGL3DEAModelingRight->SetViewSampledPointsOnly(isViewSampledPointsOnly);
}

void SBMEMainWindow::m_slotPerspectiveOrOrtho(bool isPespective)
{
	m_pQGL3DEAModeling->PerspectiveOrOrtho(isPespective);
    //m_pQGL3DEAModelingLeft->PerspectiveOrOrtho(isPespective);
    //m_pQGL3DEAModelingRight->PerspectiveOrOrtho(isPespective);
}

void SBMEMainWindow::m_slotAutoConnect(bool isAutoConnect)
{
	m_pNDIController->SetAutoConnect(isAutoConnect);
}

void SBMEMainWindow::m_slotSetCommPort()
{
    //m_pNDIController->SetCommPort();

    m_pSerialPortSettingsDlg->exec();
}

void SBMEMainWindow::m_slotSetProgramOptions()
{
    //m_pNDIController->SetProgramOptions();
	SBMENDIProgramOptionDlg *m_pNDIProgramOptionDlg = new SBMENDIProgramOptionDlg;
    if (m_pNDIProgramOptionDlg)
    {
        if (m_pNDIProgramOptionDlg->exec())
            delete m_pNDIProgramOptionDlg;
    }
}

void SBMEMainWindow::m_slotSROMFileSettings()
{
	m_pRomFileDlg->SetSysteminfo(m_pDtSystemInformation->nTypeofSystem, m_pDtSystemInformation->nNoActivePorts,
                                 m_pDtSystemInformation->nNoPassivePorts, m_pDtSystemInformation->nNoMagneticPorts);
    m_pRomFileDlg->show();
}

void SBMEMainWindow::m_slotViewSystemFeatures()
{
    //m_pNDIController->ViewSystemFeatures();
	SBMENDISystemFeaturesDlg *m_pSystemFeaturesDlg = new SBMENDISystemFeaturesDlg;
	if (m_pSystemFeaturesDlg == NULL)
		return;
	if (m_pDtSystemInformation->nTypeofSystem != AURORA_SYSTEM)
    {
        m_pSystemFeaturesDlg->SetVariables(m_pDtSystemInformation->szVersionInfo,
                                           m_pDtSystemInformation->nNoActivePorts,
                                           m_pDtSystemInformation->nNoPassivePorts,
                                           m_pDtSystemInformation->nNoActWirelessPorts,
                                           m_pDtSystemInformation->nNoActTIPPorts);
    }
    else
    {

        m_pSystemFeaturesDlg->SetVariables(m_pDtSystemInformation->szVersionInfo,
                                           m_pDtSystemInformation->nNoMagneticPorts,
                                           m_pDtSystemInformation->nNoFGs,
                                           m_pDtSystemInformation->nNoFGCards);
    }
    if(m_pSystemFeaturesDlg->exec())
		delete m_pSystemFeaturesDlg;
}

//修改于2015/04/28
void SBMEMainWindow::m_slotResetSystem()
{
    //测试代码
	//QMessageBox::information(this, "Reset", "System successfully Reset", QMessageBox::Ok);
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	bool resetsystem = m_pNDIController->ResetSystem();
	
	QApplication::restoreOverrideCursor();

	if (resetsystem)
		QMessageBox::information(this, "Reset", "System resets successfully!", QMessageBox::NoButton);
	else
		QMessageBox::information(this, "Reset", "System fails to reset!\n"
			                                    "Please try again!", QMessageBox::NoButton);
	/*
	if (m_pNDIController->ResetSystem())
    {
        SetMode(MODE_PRE_INIT);
		QApplication::restoreOverrideCursor();
        QMessageBox::information(this, "Reset", "System resets successfully!", QMessageBox::NoButton);
    }
	else
	{
		QApplication::restoreOverrideCursor();
        QMessageBox::information(this, "Reset", "System fails to reset!"
			                                    "Please try again!", QMessageBox::NoButton);
	}
	*/
}

//修改于2015/04/28
void SBMEMainWindow::m_slotInitializeSystem()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	bool initializesystem = m_pNDIController->InitializeSystem();
	
	QApplication::restoreOverrideCursor();

	if (initializesystem)
	{
		SetMode(MODE_INIT);
		QMessageBox::information(this, "Initialization", "System intializes successfully!", QMessageBox::NoButton);
	}
	else
		QMessageBox::information(this, "Initialization", "System fails to intialize!\n"
			                                             "Please try again!", QMessageBox::NoButton);
	/*
	if (m_pNDIController->InitializeSystem())
    {
        SetMode(MODE_INIT);
		QApplication::restoreOverrideCursor();
        QMessageBox::information(this, "Initialization", "System intializes successfully!", QMessageBox::NoButton);
    }
	else
	{
		QApplication::restoreOverrideCursor();
        QMessageBox::information(this, "Initialization", "System fails to intialize!"
			                                             "Please try again!", QMessageBox::NoButton);
	}
	*/
}

bool SBMEMainWindow::m_slotActivateAllHandles()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	if (!m_pNDIController->bActivateAllHandles())
        return false;
	QApplication::restoreOverrideCursor();
    QString str = QString("%1 Handles are Activated").arg(m_nHandlesEnabled);
    QMessageBox::information(this, "Activation Success", str, QMessageBox::Ok);

    m_pHandlesPanel->clear();
    delete m_HandlesCardDlgList[0];
    for (int i = 0; i < m_nHandlesEnabled; i++)
    {
        m_HandlesCardDlgList[i] = new SBMENDIHandleCardDlg(m_pHandlesPanel);
        connect(m_HandlesCardDlgList[i], SIGNAL(m_signalToEnableorDisableHandle(int, int, bool)), this, SLOT(m_slotEnableDisableHandle(int, int, bool)));
        connect(m_HandlesCardDlgList[i], SIGNAL(m_signalToSetHandleModel(int, int)),              this, SLOT(m_slotSetHandleModel(int, int)));
        connect(m_HandlesCardDlgList[i], SIGNAL(m_signalToSetHandleColor(int, QColor)),           this, SLOT(m_slotSetHandleColor(int, QColor)));
		connect(m_HandlesCardDlgList[i], SIGNAL(m_signalToSetReferenceHandle(int, int)),          this, SLOT(m_slotSetReferenceHandle(int, int)));
        connect(m_HandlesCardDlgList[i], SIGNAL(m_signalToSetActiveHandle(int)),                  this, SLOT(m_slotSetActiveHandle(int)));
        QString str(m_pDtHandleInformation[m_pEnabledHandleIndex[i]].szPartNumber);
        QString index = QString::number(m_pEnabledHandleIndex[i], 16).toUpper();
        m_pHandlesPanel->insertTab(i, m_HandlesCardDlgList[i], QIcon(":/Images/Images/tracking"), index);
        m_HandlesCardDlgList[i]->SetCardIndex(i);
        m_HandlesCardDlgList[i]->SetPortIndex(m_pEnabledHandleIndex[i]);
        m_HandlesCardDlgList[i]->SetPartNum(str);
        m_HandlesCardDlgList[i]->SetHandleEnabled(true);
    }
    m_pHandlesPanel->show();
    m_pQGL3DEAModeling->SetCurrentActiveHandle(0);
    SetMode(MODE_ACTIVATED);
    return 1;
}

void SBMEMainWindow::m_slotEnableDisableHandle(int cardIndex, int portIndex, bool bEnable)
{
	if (bEnable)
    {
        if (m_pNDIController->bEnableHandle(portIndex))
        {
            m_HandlesCardDlgList[cardIndex]->SetHandleEnabled(true);
            m_pHandlesPanel->setTabIcon(cardIndex, QIcon(":/Images/Images/tracking"));
        }
    }
    else
    {
        if (m_pNDIController->bDisableHandle(portIndex))
        {
            m_HandlesCardDlgList[cardIndex]->SetHandleEnabled(false);
            m_pHandlesPanel->setTabIcon(cardIndex, QIcon(":/Images/Images/tracking3"));
        }
    }
}

void SBMEMainWindow::m_slotSetHandleModel(int portIndex, int model)
{
	m_pQGL3DEAModeling->SetHandleModel(portIndex, model);
    m_pQGL3DEAModelingAdd->SetHandleModel(portIndex, model);
    //m_pQGL3DEAModelingLeft->SetHandleModel(portIndex, model);
    //m_pQGL3DEAModelingRight->SetHandleModel(portIndex, model);
}

void SBMEMainWindow::m_slotSetHandleColor(int portIndex, QColor color)
{
	m_pQGL3DEAModeling->SetHandleColor(portIndex, color);
    m_pQGL3DEAModelingAdd->SetHandleColor(portIndex, color);
    //m_pQGL3DEAModelingLeft->SetHandleColor(portIndex, color);
    //m_pQGL3DEAModelingRight->SetHandleColor(portIndex, color);
}

//添加于2015/04/28
void SBMEMainWindow::m_slotSetReferenceHandle(int cardIndex, int portIndex)
{
	if (m_ReferenceHandle[cardIndex])
	{
		for (int i = 0; i < m_nHandlesEnabled; i++)
		{
			m_ReferenceHandle[i] = false;
			if (i != cardIndex)
			    m_HandlesCardDlgList[i]->SetReferenceHandleEnabled(m_ReferenceHandle[i]);
		}
		m_pHandlesPanel->setTabText(cardIndex, QString(m_pHandlesPanel->tabText(cardIndex) + " (Reference Handle)"));
		m_nRefHandle = portIndex;
	    m_pNDIController->SetReferenceHandle(m_nRefHandle);
	}
	else
	{
		for (int i = 0; i < m_nHandlesEnabled; i++)
		{
			m_ReferenceHandle[i] = true;
			if (i != cardIndex)
			    m_HandlesCardDlgList[i]->SetReferenceHandleEnabled(m_ReferenceHandle[i]);
		}
		m_pHandlesPanel->setTabText(cardIndex, QString(m_pHandlesPanel->tabText(cardIndex).remove(QString(" (Reference Handle)"))));
		m_nRefHandle = -1;
	    m_pNDIController->SetReferenceHandle(m_nRefHandle);
	}
}

void SBMEMainWindow::m_slotSetActiveHandle(int idx)
{
	m_pQGL3DEAModeling->SetCurrentActiveHandle(idx);
    m_pQGL3DEAModelingAdd->SetCurrentActiveHandle(idx);
    //m_pQGL3DEAModelingLeft->SetCurrentActiveHandle(idx);
    //m_pQGL3DEAModelingRight->SetCurrentActiveHandle(idx);
}

bool SBMEMainWindow::m_slotStartTracking()
{
	if(!m_bIsTracking)
    {
        if (m_pNDIController->bStartTracking())
        {
            SetMode(MODE_TRACKING);
            return 1;
        }
        else
			return 0;
    }
}

//修改于2015/05/19
bool SBMEMainWindow::m_slotStopTracking()
{
	if(m_bIsTracking)
    {
        if (m_pNDIController->bStopTracking())
        {
            SetMode(MODE_ACTIVATED);
            m_szSystemMode = "Tracking Suspended";
            emit m_signalSystemModeChanged(m_szSystemMode);
            return 1;
        }   
        else
		    return 0;
    }
}

void SBMEMainWindow::m_slotFiringRate20Hz()
{
	m_pNDIController->FiringRate20Hz();
}

void SBMEMainWindow::m_slotFiringRate30Hz()
{
	m_pNDIController->FiringRate30Hz();
}

void SBMEMainWindow::m_slotFiringRate60Hz()
{
	m_pNDIController->FiringRate60Hz();
}

void SBMEMainWindow::m_slotEulerAngles(bool IsUseEulerAngles)
{
	m_bUseEulerAngles = IsUseEulerAngles;
	if (m_nHandlesEnabled == 0)
	{
	    if (!m_bUseEulerAngles)
        {
            m_HandlesCardDlgList[0]->SetQ0Text(QString("Q0:"));
            m_HandlesCardDlgList[0]->SetQxText(QString("Qx:"));
            m_HandlesCardDlgList[0]->SetQyText(QString("Qy:"));
            m_HandlesCardDlgList[0]->SetQzText(QString("Qz:"));
        }
        else
        {
            m_HandlesCardDlgList[0]->SetQ0Text(QString(""));
            m_HandlesCardDlgList[0]->SetQxText(QString("Rx"));
            m_HandlesCardDlgList[0]->SetQyText(QString("Ry:"));
            m_HandlesCardDlgList[0]->SetQzText(QString("Rz:"));
        }
	}

    for (int i = 0; i < m_nHandlesEnabled; i ++)
    {
        if (!m_bUseEulerAngles)
        {
            m_HandlesCardDlgList[i]->SetQ0Text(QString("Q0:"));
            m_HandlesCardDlgList[i]->SetQxText(QString("Qx:"));
            m_HandlesCardDlgList[i]->SetQyText(QString("Qy:"));
            m_HandlesCardDlgList[i]->SetQzText(QString("Qz:"));
        }
        else
        {
            m_HandlesCardDlgList[i]->SetQ0Text(QString(""));
            m_HandlesCardDlgList[i]->SetQxText(QString("Rx"));
            m_HandlesCardDlgList[i]->SetQyText(QString("Ry:"));
            m_HandlesCardDlgList[i]->SetQzText(QString("Rz:"));
        }
    }
}

void SBMEMainWindow::m_slotLargerSymbol(bool isLargerSymbol)
{
	m_pQGL3DEAModeling->SetHandleView(isLargerSymbol);
	m_pQGL3DEAModelingAdd->SetHandleView(isLargerSymbol);
    //m_pQGL3DEAModelingLeft->SetHandleView(isLargerSymbol);
    //m_pQGL3DEAModelingRight->SetHandleView(isLargerSymbol);
}

void SBMEMainWindow::m_slotExtendedVolume(bool isExtendedVolume)
{
	m_pQGL3DEAModelingAdd->SetVolumeView(isExtendedVolume);
}

void SBMEMainWindow::m_slotTXMode()
{
	m_nTrackingMode = 0;
	m_pTXModeAction->setChecked(true);
	m_pBXModeAction->setChecked(false);

	emit m_signalTrackingMode(m_nTrackingMode);
}

void SBMEMainWindow::m_slotBXMode()
{
	m_nTrackingMode = 1;
	m_pTXModeAction->setChecked(false);
	m_pBXModeAction->setChecked(true);
	emit m_signalTrackingMode(m_nTrackingMode);
}

/*void SBMEMainWindow::m_slotSelectECGChannel()
{
	m_pECGControlPanelDlg->exec();
}*/

void SBMEMainWindow::m_slotNew3DEAModel()
{
	static int i = 0;
    if ((m_pModelFile != NULL))
    {
        if (m_pModelFile->isOpen())
            m_pModelFile->close();
    }
    QString filename = QString("Data/Model/CurrentModel%1.csv").arg(i);
    
	if (QFile::exists(filename))
        QFile::resize(filename,0);
    
	m_pModelFile = new QFile(filename);
    m_pDeformationModel->LoadFile(filename.toLatin1().data());
    
	m_pModelFile->open(QIODevice::ReadWrite);
    m_pQGL3DEAModeling->SetModelFile(m_pModelFile);
    
	i++;
    
	m_pQGL3DEAModeling->SetTranslation(0, 0, 0);
    //m_pQGL3DEAModelingLeft->SetTranslation(0, 0, 0);
    //m_pQGL3DEAModelingRight->SetTranslation(0, 0, 0);
    m_pQGL3DEAModeling->SetColored(false);
    m_pQGL3DEAModelingAdd->SetColored(false);
    //m_pQGL3dEAModelingLeft->SetColored(false);
    //m_pQGL3dEAModelingRight->SetColored(false);
}

void SBMEMainWindow::m_slotLoad3DEAModel()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Load 3D EAModel"), "", tr("csv Files (*.csv *.CSV)"));
    
	if ((m_pModelFile != NULL))
    {
        if (m_pModelFile->isOpen())
            m_pModelFile->close();
    }
    
	m_pDeformationModel->LoadFile(filename.toLatin1().data());
    
	if (m_pDeformationModel->GetPoints3DNum() > 4)
        m_pDeformationModel->StartApproximation();
    
	m_pModelFile = new QFile(filename);
    m_pModelFile->open(QIODevice::ReadWrite);
    m_pQGL3DEAModeling->SetModelFile(m_pModelFile);
    
	double centerPoint[3];
    
	m_pDeformationModel->GetCenter(centerPoint);
    m_pQGL3DEAModeling->SetTranslation(centerPoint[0], centerPoint[1], centerPoint[2]);
    //m_pQGL3DEAModelingLeft->SetTranslation(centerPoint[0], centerPoint[1], centerPoint[2]);
    //m_pQGL3DEAModelingRight->SetTranslation(centerPoint[0], centerPoint[1], centerPoint[2]);
    m_pQGL3DEAModeling->SetColored(false);
    m_pQGL3DEAModelingAdd->SetColored(false);
    //m_pQGL3DEAModelingLeft->SetColored(false);
    //m_pQGL3DEAModelingRight->SetColored(false);

	m_pInsertPointAction->setEnabled(true);
	m_pDeletePointAction->setEnabled(true);
}

void SBMEMainWindow::m_slotLoad3DCTMRModel()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Load3D CT/MR Model"), "", tr("DICM Files (*.dicm *.DICM)"));
}

void SBMEMainWindow::m_slotInsertPoint()
{
}

void SBMEMainWindow::m_slotDeletePoint()
{
}

void SBMEMainWindow::m_slotAbout()
{
	QMessageBox::about(this, tr("About Three-dimensional Electrophysiological Mapping System"),
                       tr("<h2>3DEMS 1.0</h2>"
                          "<p>Copyright &copy; Tsinghua University."
                          "<p>3DEMS is an application based on Qt and OpenGL that "
                          "help doctors better to operate heart surgery."));
}

void SBMEMainWindow::m_slotAboutQt()
{
	qApp->aboutQt();
}

void SBMEMainWindow::m_slotAboutOpenGL()
{
	QMessageBox aboutOpenGL;
    //aboutOpenGL.setWindowIcon(QIcon(":/Images/Images/OpenGL.png"));
    QMessageBox::about(this, tr("About OpenGL"),
                       tr("<h2>OpenGL</h2>"
                          "<p>Copyright  &copy; 1997-2014 Khronos GroupCopyright"
                          "<p>OpenGL (Open Graphics Library)is a cross-language, multi-platform application programming interface (API)"
                          "for rendering 2D and 3D vector graphics. "
                          "The API is typically used to interact with a graphics processing unit (GPU),"
                          "to achieve hardware-accelerated rendering. "
                          "learn More please go to:http://www.opengl.org/"
                          ));
}

void SBMEMainWindow::m_slotAboutNDI()
{
	QMessageBox aboutNDI;
    //aboutNDI.setWindowIcon(QIcon(":/Images/Images/NDI_Logo.png"));
    aboutNDI.about(this, tr("About NDI"),
                   tr("<h2>NDI</h2>"
                      "<p>Copyright  &copy; 2014 Northern Digital Inc."
                      "<p>NDI is a global leading innovator and manufacturer of advanced 3D measurement technology systems,"
                      "with over 45,000 installations worldwide. For over 30 years, the company's optical measurement and electromagnetic tracking solutions "
                      "have been trusted by the world's foremost organizations and institutes in medicine, industry and academia. "
                      "From image-guided surgery to aeronautics; from quality assurance to biomechanics research, "
                      "NDI solutions are used whenever best-in-class measurement accuracy and reliability are required. "
                      "learn More please go to:http://www.ndigital.com/"
                      ));
}

bool SBMEMainWindow::m_slotDisplaySystemTransformData(int bPortOccupied, bool isnewportsactivefailed)
{
	//sbme_ThreadNDIMutex.lock();
	//QTime testtime;
	//testtime.start();

	//int a = testtime.elapsed();
	//int b = a;
	//int c = b;

	char pszTemp[256];
    QString str;
    Rotation dtEulerRot;

	if (!m_bIsTracking)
        return 0;

	//int a = testtime.elapsed();
	//int b = a;
	//int c = b;

	//sbme_ThreadNDIMutex.lock();

    //if (!m_pNDIController->bGetTXTransforms())
        //return 0;

	/*if (m_nTrackingMode == 0)
	{
		if (!m_pNDIController->bGetTXTransforms())
			return 0;
	}
	else if (m_nTrackingMode == 1)
	{
		if (!m_pNDIController->bGetBXTransforms())
			return 0;
	}*/

	/* 
	if a new port has become occupied we do the following:
	(1) Stop tracking
	(2) Activate Ports
	(3) Start Tracking
	*/
    /*if (m_pDtSystemInformation->bPortOccupied)
    {
        if (m_pNDIController->bStopTracking() && m_pNDIController->bActivateAllHandles() && m_pNDIController->bStartTracking())
            return 1;
        
		//We don't want the tracking thread to track if activating the ports failed!
		m_bIsTracking = FALSE;
        SetMode(MODE_ACTIVATED);
        return 0;
    }*/
	if (bPortOccupied)
	{
		if(isnewportsactivefailed)
	    {
		    m_bIsTracking = FALSE;
		    SetMode(MODE_ACTIVATED);
		    return 0;
	    }
		else
			return 1;
	}
    
	//sbme_ThreadNDIMutex.lock();
	//int a = testtime.elapsed();
	//int b = a;
	//int c = b;

    for (int i = 0; i < m_nHandlesEnabled; i++)
    {
        int index = m_pEnabledHandleIndex[i];
        if (m_pDtHandleInformation[index].HandleInfo.bInitialized > 0 &&
            m_pDtHandleInformation[index].szToolType[1] != '8')
        {
            if (m_pDtHandleInformation[index].Xfrms.ulFlags == TRANSFORM_VALID ||
                m_pDtHandleInformation[index].Xfrms.ulFlags == TRANSFORM_MISSING)
            {
                m_nFrameNumber = m_pDtHandleInformation[index].Xfrms.ulFrameNumber;
                m_pFrameNumber->display(m_nFrameNumber);
            }
            if (m_pDtHandleInformation[index].Xfrms.ulFlags == TRANSFORM_VALID)
            {
                m_pQGL3DEAModeling->SetHandleXfms(i, m_pDtHandleInformation[index].Xfrms.translation, m_pDtHandleInformation[index].Xfrms.rotation);
                m_pQGL3DEAModelingAdd->SetHandleXfms(i, m_pDtHandleInformation[index].Xfrms.translation, m_pDtHandleInformation[index].Xfrms.rotation);
                //m_pQGL3DEAModelingLeft->SetHandleXfms(i, m_pDtHandleInformation[index].Xfrms.translation, m_pDtHandleInformation[index].Xfrms.rotation);
                //m_pQGL3DEAModelingRight->SetHandleXfms(i, m_pDtHandleInformation[index].Xfrms.translation, m_pDtHandleInformation[index].Xfrms.rotation);
                m_pQGL3DEAModeling->SetHandlesEnabledFlag(i, true);
                m_pQGL3DEAModelingAdd->SetHandlesEnabledFlag(i, true);
                //m_pQGL3DEAModelingLeft->SetHandlesEnabledFlag(i, true);
                //m_pQGL3DEAModelingRight->SetHandlesEnabledFlag(i, true);
                m_HandlesCardDlgList[i]->SetStatus("Valid");
                sprintf(pszTemp, "%.2f", m_pDtHandleInformation[index].Xfrms.translation.x);
                m_HandlesCardDlgList[i]->SetTx(QString(pszTemp));
                sprintf(pszTemp, "%.2f", m_pDtHandleInformation[index].Xfrms.translation.y);
                m_HandlesCardDlgList[i]->SetTy(QString(pszTemp));
                sprintf(pszTemp, "%.2f", m_pDtHandleInformation[index].Xfrms.translation.z);
                m_HandlesCardDlgList[i]->SetTz(QString(pszTemp));
                if (!m_bUseEulerAngles)
                {
                    sprintf(pszTemp, "%.4f", m_pDtHandleInformation[index].Xfrms.rotation.q0);
                    m_HandlesCardDlgList[i]->SetQ0(QString(pszTemp));
                    sprintf(pszTemp, "%.4f", m_pDtHandleInformation[index].Xfrms.rotation.qx);
                    m_HandlesCardDlgList[i]->SetQx(QString(pszTemp));
                    sprintf(pszTemp, "%.4f", m_pDtHandleInformation[index].Xfrms.rotation.qy);
                    m_HandlesCardDlgList[i]->SetQy(QString(pszTemp));
                    sprintf(pszTemp, "%.4f", m_pDtHandleInformation[index].Xfrms.rotation.qz);
                    m_HandlesCardDlgList[i]->SetQz(QString(pszTemp));
                }
                else
                {
                    CvtQuatToEulerRotation(&m_pDtHandleInformation[index].Xfrms.rotation, &dtEulerRot);
                    sprintf(pszTemp, "%.4f", dtEulerRot.fYaw);
                    m_HandlesCardDlgList[i]->SetQx(QString(pszTemp));
                    sprintf(pszTemp, "%.4f", dtEulerRot.fPitch);
                    m_HandlesCardDlgList[i]->SetQy(QString(pszTemp));
                    sprintf(pszTemp, "%.4f", dtEulerRot.fRoll);
                    m_HandlesCardDlgList[i]->SetQz(QString(pszTemp));
                    sprintf(pszTemp, "");
                    m_HandlesCardDlgList[i]->SetQ0("--");
                }
                sprintf(pszTemp, "%.4f", m_pDtHandleInformation[index].Xfrms.fError);
                m_HandlesCardDlgList[i]->SetError(QString(pszTemp));
            }
            else
            {
                if (m_pDtHandleInformation[index].Xfrms.ulFlags == TRANSFORM_MISSING)
                {
                    str = QString("MISSING" );
                    m_HandlesCardDlgList[i]->SetStatus(str);
                }
                else
                {
                    str = QString("DISABLED");
                    m_HandlesCardDlgList[i]->SetStatus(str);
                    //m_pQGL3DEAModeling->SetHandlesEnabledFlag(i, false);
                    //m_pQGL3DEAModelingAdd->SetHandlesEnabledFlag(i, false);
                    //m_pQGL3DEAModelingLeft->SetHandlesEnabledFlag(i, false);
                    //m_pQGL3DEAModelingRight->SetHandlesEnabledFlag(i, false);
                }
                str = QString("--");
                m_HandlesCardDlgList[i]->SetTx(str);
                m_HandlesCardDlgList[i]->SetTy(str);
                m_HandlesCardDlgList[i]->SetTz(str);
                m_HandlesCardDlgList[i]->SetQ0(str);
                m_HandlesCardDlgList[i]->SetQx(str);
                m_HandlesCardDlgList[i]->SetQy(str);
                m_HandlesCardDlgList[i]->SetQz(str);
                m_HandlesCardDlgList[i]->SetError(str);
                m_HandlesCardDlgList[i]->SetOutOfVolume(str);
            }
            if (m_pDtHandleInformation[index].HandleInfo.bPartiallyOutOfVolume)
                str = QString("POOV");
            else if (m_pDtHandleInformation[index].HandleInfo.bOutOfVolume)
                str = QString("OOV");
            else
                str = QString("OK");
            m_HandlesCardDlgList[i]->SetOutOfVolume(str);
        }
    }
	
	//sbme_ThreadNDIMutex.unlock();

	//int a = testtime.elapsed();
	//int b = a;
	//int c = b;

	return true;
}

void SBMEMainWindow::m_slotSetSystemType(int nSystemType)
{
	m_pQGL3DEAModeling->SetSystemType(nSystemType);
	m_pQGL3DEAModelingAdd->SetSystemType(nSystemType);
    //m_pQGL3DEAModelingLeft->SetSystemType(nSystemType);
    //m_pQGL3DEAModelingRight->SetSystemType(nSystemType);  

    if (m_pDtSystemInformation->nTypeofSystem == AURORA_SYSTEM)
    {
        m_pFiringRateMenu->setDisabled(true);
    }
    else if ((m_pDtSystemInformation->nTypeofSystem == ACCEDO_SYSTEM) || (m_pDtSystemInformation->nTypeofSystem == VICRA_SYSTEM))
    {
        m_pFiringRate30Action->setDisabled(true);
        m_pFiringRate60Action->setDisabled(true);
    }
}

void SBMEMainWindow::m_slotNDIAutoInitialized()
{
	SetMode(MODE_INIT);
    QMessageBox::information(this, "Initialization", "System successfully intialized", QMessageBox::NoButton);
}

void SBMEMainWindow::m_slotSetHandlesEnabled(int HandlesEnabled)
{
	m_nHandlesEnabled = HandlesEnabled;
    m_pQGL3DEAModeling->SetHandlesEnabled(m_nHandlesEnabled);
	m_pQGL3DEAModelingAdd->SetHandlesEnabled(m_nHandlesEnabled);
    //m_pQGL3DEAModelingLeft->SetHandlesEnabled(m_nHandlesEnabled);
    //m_pQGL3DEAModelingRight->SetHandlesEnabled(m_nHandlesEnabled);
}

void SBMEMainWindow::m_slotRomFileChanged()
{
	SetMode(MODE_PRE_INIT);
}

void SBMEMainWindow::m_slotUpdateStatusBar(QString SysTemstatus)
{
    m_pConnectedStatus->setPixmap(m_bSystemInitialized ? QPixmap(":/Images/Images/Knob Green") : QPixmap(":/Images/Images/Knob Cancel"));
    m_pTrackingStatus->setPixmap(m_bIsTracking ? QPixmap(":/Images/Images/Knob Green") : QPixmap(":/Images/Images/Knob Orange"));
	m_pSystemStatus->setText(SysTemstatus);
}

void SBMEMainWindow::m_slotInitErrorDetermineSystemType()
{
	QMessageBox::warning(this, "INIT ERROR","Could not determine type of system\n"
                                     "(Polaris, Polaris Accedo, Polaris Vicra or Aurora)",
                                     QMessageBox::Ok );
}

void SBMEMainWindow::m_slotInitErrorInitializeSystem()
{
	QMessageBox::critical(this, "INIT ERROR","System could not be initialized.\n "
                                  "Check your COM Port settings, make sure your\n"
                                  "system is turned on and the system components are compatible.",
                                  QMessageBox::Ok );
}

void SBMEMainWindow::m_slotOpenLogFileError()
{
	QMessageBox::warning(this, "Log File Error", "Failed to open log file.", QMessageBox::Ok);
}

void SBMEMainWindow::m_slotComportOpened()
{
	QMessageBox::warning(this, "warning", "The comport has been opened.", QMessageBox::Ok);
}

void SBMEMainWindow::m_slotComPortOpenFailure()
{
	QMessageBox::critical(this, "Error", "Open ComPort Failure", QMessageBox::Ok);
}

void SBMEMainWindow::m_slotPINITError(char *szerrormessage)
{
	QMessageBox::critical(this, "PINIT ERROR", szerrormessage, QMessageBox::Ok);
}

void SBMEMainWindow::m_slotSROMError(char *cmessage)
{
	QMessageBox::critical(this, "SROM Error", cmessage, QMessageBox::Ok);
}

void SBMEMainWindow::m_slotSROMImageError(char *cmessage)
{
	QMessageBox::critical(this, "SROM Image Error", cmessage, QMessageBox::Ok);
}

void SBMEMainWindow::m_slotErrorMessage(char *pcherrornumber, char *pcherrormessage)
{
	QMessageBox::critical(this, pcherrornumber, pcherrormessage, QMessageBox::Ok);
}

void SBMEMainWindow::m_slotWarningMessage(char *pchwarningnumber, char *pchwarningmessage)
{
	QMessageBox::warning(this, pchwarningnumber, pchwarningmessage, QMessageBox::Ok);
}

void SBMEMainWindow::m_slotWriteTimeoutError()
{
	QMessageBox::critical(this, tr("Timeout Error!"), tr("Comport Write Time out!"));
}

void SBMEMainWindow::m_slotProcessTimeoutError()
{
	QMessageBox::critical(this, tr("Timeout Error!"), tr("Comport Time out!"));
}

void SBMEMainWindow::m_slotReadTimeoutError()
{
	int nTimeOutChoose = QMessageBox::critical(NULL, tr("Timeout Error!"), tr("Comport Time out!\n""what do you want to do?"), QMessageBox::Retry | QMessageBox::Abort| QMessageBox::Ignore);
	emit m_signalTimeOutChoose(nTimeOutChoose);
}

void SBMEMainWindow::m_slotCRCError()
{
	QMessageBox::critical(this, "CRC Error", "Bad CRC received with reply.", QMessageBox::Ok);
}

void SBMEMainWindow::m_slotInvalidResponseError()
{
	QMessageBox::critical(this, "Invalid Response", "Invalid response received from the system", QMessageBox::Ok);
}

void SBMEMainWindow::m_slotLogFileError(char *szmessage)
{
	QMessageBox::warning(this, "Log File Error", szmessage, QMessageBox::Ok);
}
