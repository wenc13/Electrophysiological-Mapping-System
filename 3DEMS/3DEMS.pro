QT += \
    widgets \
    opengl \
    serialport

SOURCES += \
    SBMEmain.cpp \
    SBMEMainWindow.cpp \
    SBMEQGL3DEAModeling.cpp \
    SBMEECGAcquisitionDlg.cpp \
    SBMENDISerialPortSettingsDlg.cpp \
    SBMENDISystemFeaturesDlg.cpp \
    SBMENDIRomFileDlg.cpp \
    SBMENDIProgramOptionDlg.cpp \
    SBMENDIHandleCardDlg.cpp \
    SBMENDIAuxiliary.cpp \
    SBMENDIController.cpp \
    SBMEECGAcquisitionObj.cpp \
    SBMEECGProcessObj.cpp \
    SBMEUserDef.cpp \
    SBMEECGPlayBackDlg.cpp \
    SBMEColorDlg.cpp \
    SBMEColorMappingBar.cpp \
    SBMECoordinateRegistrationDlg.cpp \
    SBMEDeformModel.cpp \
    SBMEGridPoints.cpp \
    SBMEMatrixComputation.cpp \
    SBMEStereoProjectorControlPanelDlg.cpp \
    SBMEPoints3D.cpp \
    SBMEECGControlPanelDlg.cpp

HEADERS += \
    SBMEMainWindow.h \
    SBMEQGL3DEAModeling.h \
    SBMEECGAcquisitionDlg.h \
    SBMENDIDef.h \
    SBMENDISerialPortSettingsDlg.h \
    SBMENDISystemFeaturesDlg.h \
    SBMENDIRomFileDlg.h \
    SBMENDIProgramOptionDlg.h \
    SBMENDIHandleCardDlg.h \
    SBMENDIAuxiliary.h \
    SBMENDIController.h \
    SBMESerialPortBuffer.h \
    SBMEECGAcquisitionObj.h \
    SBMEECGProcessObj.h \
    SBMEMacroDefinition.h \
    SBMEUserDef.h \
    Usb2805.h \
    SBMEECGPlayBackDlg.h \
    SBMEColorDlg.h \
    SBMEColorMappingBar.h \
    SBMECoordinateRegistrationDlg.h \
    SBMEDeformModel.h \
    SBMEGridPoints.h \
    SBMEMatrixComputation.h \
    SBMEStereoProjectorControlPanelDlg.h \
    SBMEPoints3D.h \
    SBMEECGControlPanelDlg.h

FORMS += \
    SBMEECGAcquisitionDlg.ui \
    SBMENDISerialPortSettingsDlg.ui \
    SBMENDISystemFeaturesDlg.ui \
    SBMENDIRomFileDlg.ui \
    SBMENDIProgramOptionDlg.ui \
    SBMENDIHandleCardDlg.ui \
    SBMEECGPlayBackDlg.ui \
    SBMEColorDlg.ui \
    SBMECoordinateRegistrationDlg.ui \
    SBMEStereoProjectorControlPanelDlg.ui \
    SBMEECGControlPanelDlg.ui

RESOURCES += \
    3DEMS.qrc
