#include "SBMEECGAcquisitionObj.h"

SBMEECGAcquisitionObj::SBMEECGAcquisitionObj() : QObject()
{
    m_nDeviceLgcID   = 0;
    m_nReturn        = 0;
    m_nReadSizeWords = 0;
    m_lRetWords      = 0;
	m_nReadIndex     = 0;

    m_hDevice        = NULL;
    m_bAcqStopped    = true;

	/*AcqObjFile.setFileName("ARTData.txt");
	if(!AcqObjFile.open(QIODevice::WriteOnly))
	{
		emit AcqObjOpenFileErr();
		return;
	}
	AcqObjIn.setDevice(&AcqObjFile);*/
}

void SBMEECGAcquisitionObj::m_slotECGAcquisitionStart()
{
    m_ADPara.CheckStsMode   = USB2805_CHKSTSMODE_HALF;        //查询FIFO的半满标志
    m_ADPara.ADMode         = USB2805_ADMODE_SEQUENCE;        //选择连续采集模式
    m_ADPara.FirstChannel	= 0;                              //首通道0
    m_ADPara.LastChannel	= SBME_MAX_CHANNEL_COUNT-1;       //末通道0
    m_ADPara.Frequency		= 4000*SBME_MAX_CHANNEL_COUNT;    //采样频率
    m_ADPara.GroupInterval	= 100;                            //组间间隔设为100微秒
    m_ADPara.LoopsOfGroup	= 1;                              //组内循环次数设为1次
    m_ADPara.Gains			= USB2805_GAINS_1MULT;            //使用1倍增益
    m_ADPara.TriggerMode	= USB2805_TRIGMODE_SOFT;          //触发模式选择软件内触发
	m_ADPara.TriggerSource  = USB2805_TRIGSOURCE_ATR;         //触发源选择模拟触发ATR
    m_ADPara.TriggerType	= USB2805_TRIGTYPE_EDGE;          //触发类型选择边沿触发
    m_ADPara.TriggerDir		= USB2805_TRIGDIR_NEGATIVE;       //触发方向选择
    m_ADPara.TrigLevelVolt	= 0;                              //触发电平0V
    m_ADPara.TrigWindow		= 10;                             //触发灵敏度
    m_ADPara.ClockSource	= USB2805_CLOCKSRC_IN;
    m_ADPara.bClockOutput	= FALSE;

    //m_nDeviceLgcID = 0;
    m_hDevice = USB2805_CreateDevice(m_nDeviceLgcID);
    if (m_hDevice == INVALID_HANDLE_VALUE)
    {
        emit m_signalAcqObjCreateDeviceErr();
        return;
    }

    m_nReturn = USB2805_InitDeviceAD(m_hDevice, &m_ADPara);
    if (!m_nReturn)
    {
        emit m_signalAcqObjInitializeDeviceErr();
        USB2805_ReleaseDevice(m_hDevice);
		return;
    }

    m_nReadIndex        = 0;
	sbme_nSegmentCounts = 0;
	m_nReadSizeWords    = SBME_MAX_SEGMENT_SIZE - SBME_MAX_SEGMENT_SIZE % (256 * SBME_MAX_CHANNEL_COUNT);
    m_bAcqStopped       = false;
    
	/*while (!m_bECGStopped)
	{
        //if (sbme_bThreadECGFlagAcq == true)
			//continue;
        //sbme_ThreadARTDataMutex.lock();
        if (!USB2805_ReadDeviceAD(m_hDevice, sbme_ADBuffer[sbme_nReadIndex], m_nReadSizeWords, &m_lRetWords))
		{
            emit m_signalAcqObjReadDeviceErr();
            USB2805_ReleaseDeviceAD(m_hDevice);
            USB2805_ReleaseDevice(m_hDevice);
			return;
		}

		sbme_nReadIndex++;
		if (sbme_nReadIndex > SBME_MAX_SEGMENT_COUNT-1)
			sbme_nReadIndex = 0;

        //sbme_bThreadECGFlagAcq = true;
        //sbme_ThreadARTDataMutex.unlock();
		//for(int i=0;i<MAX_SEGMENT_SIZE;i++)
            //AcqObjIn << sbme_ADBuffer[i];
	}*/
	
	while (!m_bAcqStopped)
	{
        //if (sbme_bThreadECGFlagAcq == true)
			//continue;
        //sbme_ThreadARTDataMutex.lock();
		sbme_ThreadECGMutex.lock();
		//while (sbme_nSegmentCounts ==32)
			//sbme_ThreadECGProWaitCondition.wait(&sbme_ThreadECGMutex);

        if (!USB2805_ReadDeviceAD(m_hDevice, sbme_ADBuffer[m_nReadIndex], m_nReadSizeWords, &m_lRetWords))
		{
            emit m_signalAcqObjReadDeviceErr();
            USB2805_ReleaseDeviceAD(m_hDevice);
            USB2805_ReleaseDevice(m_hDevice);
			return;
		}

		m_nReadIndex++;
		if (m_nReadIndex > SBME_MAX_SEGMENT_COUNT-1)
			m_nReadIndex = 0;
		
		sbme_nSegmentCounts++;
		if (sbme_nSegmentCounts > SBME_MAX_SEGMENT_COUNT)
		    break;

		sbme_ThreadECGWaitCondition.wakeAll();
		sbme_ThreadECGMutex.unlock();


        //sbme_bThreadECGFlagAcq = true;
        //sbme_ThreadARTDataMutex.unlock();
		//for(int i=0;i<MAX_SEGMENT_SIZE;i++)
            //AcqObjIn << sbme_ADBuffer[i];
	}

	if (sbme_nSegmentCounts > SBME_MAX_SEGMENT_COUNT)
	{
		ECGAcquisitionStop();
		emit m_signalAcqObjDataFlowErr();
	}
}

/*void SBMEECGAcquisitionObj::m_slotECGAcquisitionStop()
{
	m_bECGStopped = true;
    if (m_hDevice != NULL)
	{
        USB2805_ReleaseDeviceAD(m_hDevice);
        USB2805_ReleaseDevice(m_hDevice);
	}
}*/

void SBMEECGAcquisitionObj::ECGAcquisitionStop()
{
    m_bAcqStopped = true;
    if (m_hDevice != NULL)
	{
        USB2805_ReleaseDeviceAD(m_hDevice);
        USB2805_ReleaseDevice(m_hDevice);
	}
}
