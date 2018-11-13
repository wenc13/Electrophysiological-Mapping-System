#ifndef SBMEECGPROCESSOBJ_H
#define SBMEECGPROCESSOBJ_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include "SBMEMacroDefinition.h"
#include "SBMEUserDef.h"
#include "Usb2805.h"

class SBMEECGProcessObj : public QObject
{ 
    Q_OBJECT 

public: 
    SBMEECGProcessObj();

	void ECGProcessStop();
	void ProObjSetInputRange(int);

private:
    int   m_nInputRange;
    float m_fVolt;
    volatile bool m_bProStopped;

	int m_nProcessIndex;

    QFile m_AcqObjFile;
    QDataStream m_AcqObjIn;

signals:
    void m_signalAcqObjOpenFileErr();
    void m_signalProObjDataProcessd();

private slots:
    void m_slotECGProcessStart();
};

#endif // SBMEECGPROCESSOBJ_H
