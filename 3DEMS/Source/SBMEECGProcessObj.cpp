#include "SBMEECGProcessObj.h"

SBMEECGProcessObj::SBMEECGProcessObj() : QObject()
{
    m_nInputRange   = 0;
	m_fVolt         = 0;
	m_bProStopped   = true;
	m_nProcessIndex = 0;

    m_AcqObjFile.setFileName("ARTData.txt");
    if (!m_AcqObjFile.open(QIODevice::WriteOnly))
	{
        emit m_signalAcqObjOpenFileErr();
		return;
	}
    m_AcqObjIn.setDevice(&m_AcqObjFile);
}

void SBMEECGProcessObj::m_slotECGProcessStart()
{
    m_nProcessIndex = 0;
	m_bProStopped   = false;

    int nChannel = 0;
    int nChannelIndex = 15;

    while (!m_bProStopped)
	{
		sbme_ThreadECGMutex.lock();
		if (sbme_nSegmentCounts == 0)
			sbme_ThreadECGWaitCondition.wait(&sbme_ThreadECGMutex);

		for (int i = 0; i < SBME_MAX_SEGMENT_SIZE;)
		{
            switch (m_nInputRange)
			{
			case USB2805_INPUT_N10000_P10000mV:
                m_fVolt = (float)((20000.00 / 65536) * sbme_ADBuffer[m_nProcessIndex][i] - 10000.00);
				break;
			case USB2805_INPUT_N5000_P5000mV:
                m_fVolt = (float)((10000.00 / 65536) * sbme_ADBuffer[m_nProcessIndex][i] - 5000.00);
				break;
			case USB2805_INPUT_N2500_P2500mV:
                m_fVolt = (float)((5000.00 / 65536) * sbme_ADBuffer[m_nProcessIndex][i] - 2500.00);
				break;
			case USB2805_INPUT_0_P10000mV:
                m_fVolt = (float)((10000.00 / 65536) * sbme_ADBuffer[m_nProcessIndex][i]);
				break;
			case USB2805_INPUT_0_P5000mV:
                m_fVolt = (float)((5000.00 / 65536) * sbme_ADBuffer[m_nProcessIndex][i]);
				break;
			}
                
			sbme_ThreadECGfloat[nChannel][nChannelIndex] = m_fVolt;
			
			nChannel++;    
			if (nChannel > SBME_MAX_CHANNEL_COUNT-1)
			{
				nChannel = 0;
				nChannelIndex -= 1;
                if (nChannelIndex < 0)
					nChannelIndex = 15;
			}

			i++;
			if (i % 32 == 31)
				i += 4 * 32;
		}

		m_nProcessIndex++;
		if (m_nProcessIndex > SBME_MAX_SEGMENT_COUNT-1)
			m_nProcessIndex = 0;

		sbme_nSegmentCounts--;
		//sbme_ThreadECGProWaitCondition.wakeAll();
		sbme_ThreadECGMutex.unlock();

        //sbme_bThreadECGFlagAcq = false;
        //sbme_bThreadECGFlagPro = true;
        //sbme_ThreadARTDataMutex.unlock();
        emit m_signalProObjDataProcessd();
	}
}

void SBMEECGProcessObj::ECGProcessStop()
{
    m_bProStopped = true;
}

void SBMEECGProcessObj::ProObjSetInputRange(int inputrange)
{
    m_nInputRange = inputrange;
}
