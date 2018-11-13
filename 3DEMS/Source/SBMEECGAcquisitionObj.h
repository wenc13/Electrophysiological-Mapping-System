#ifndef SBMEECGACQUISITIONOBJ_H
#define SBMEECGACQUISITIONOBJ_H

#include <QObject>
#include "SBMEMacroDefinition.h"
#include "SBMEUserDef.h"
#include "Usb2805.h"
//#include <QFile>
//#include <QDataStream>

class SBMEECGAcquisitionObj : public QObject
{ 
    Q_OBJECT

public: 
    SBMEECGAcquisitionObj();

    void ECGAcquisitionStop();

private:
    int  m_nDeviceLgcID;      //设备逻辑号
    int  m_nReturn;           //函数返回值
    int  m_nReadSizeWords;    // 每次读取AD数据个数
    long m_lRetWords;         // 实际读取的数据个数

	int m_nReadIndex;

    HANDLE          m_hDevice;     //设备对象句柄
    volatile bool   m_bAcqStopped;
    USB2805_PARA_AD m_ADPara;      // 初始化AD的参数结构
	
	//QFile AcqObjFile;
	//QDataStream AcqObjIn;

signals: 
    void m_signalAcqObjCreateDeviceErr();
    void m_signalAcqObjInitializeDeviceErr();
    void m_signalAcqObjReadDeviceErr();
	void m_signalAcqObjDataFlowErr();                                                                                                                                                                                                    
	//void AcqObjOpenFileErr();

private slots:
    void m_slotECGAcquisitionStart();
	//void m_slotECGAcquisitionStop();
};

#endif // SBMEECGACQUISITIONOBJ_H
