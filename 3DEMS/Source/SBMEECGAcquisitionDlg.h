#ifndef SBMEECGACQUISITIONDLG_H
#define SBMEECGACQUISITIONDLG_H

#include <QtGlobal>
#include <QPainter>

#include <QPointF>
#include <QDialog>
#include <QThread>

#include <QColor>
#include <QtMath>
#include <QTimer>

#include <QList>
#include <QFile>

#include <QTextStream>
#include <QMouseEvent>

#include "SBMEECGAcquisitionObj.h"
#include "SBMEECGProcessObj.h"
#include "SBMEECGPlayBackDlg.h"

namespace Ui
{
    class SBMEECGAcquisitionDlg;
}

class SBMEECGAcquisitionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMEECGAcquisitionDlg(QWidget *parent = 0);
    ~SBMEECGAcquisitionDlg();

protected:
	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	Ui::SBMEECGAcquisitionDlg *ui;

	SBMEECGAcquisitionObj *m_pSBMEECGAcquisition;
    SBMEECGProcessObj     *m_pSBMEECGProcess;
    SBMEECGPlayBackDlg    *m_pSBMEECGPlayBackDlg;

	QThread *m_pThreadAcquisition;
	QThread *m_pThreadProcess;
    QTimer  *m_pARTTimer;
    QTimer  *m_pPlayBackTimer;

    QPointF m_ECGDataPoint[SBME_MAX_CHANNEL_COUNT][SBME_MAX_PAINT_POINT];
	//优化代码
	//QPointF m_ECGDataPoint[SBME_MAX_DISPLAY_ECG_NUM][SBME_MAX_PAINT_POINT];
	//优化代码
    float   m_ECGDataFloat[SBME_MAX_CHANNEL_COUNT][SBME_MAX_PAINT_POINT];
	
    int   m_nSelectedECGNum;
    int   m_nDrawWidth;

    int   *m_pDialogChannel;
    int   *m_pPlayBackTime;

    bool  m_bStarting;
    bool  m_bRealTime;
    
    QList<QPoint> m_MouseClickPoint;
    QColor m_DrawColor[8];
	
	void DrawBackGround();
	void DrawECGText();
	void DrawECGData();
	void DrawMouseClickPoint();
	void DrawPlayBack();

	void AcquisitionStopped();

signals:
	void m_signalStartAcquisition();
    void m_signalStartProcess();

	void m_signalECGControlPanelDlgEnabled(bool);

	//void m_signalStopAcquisition();

private slots:
	void m_slotStartDataAcquisition();
    void m_slotStopDataAcquisition();
    void m_slotSetInputRange(int);
    void m_slotPlayBack();
    void m_slotPlayBackTime(int *);

    void m_slotDialogCreateDeviceErr();
    void m_slotDialogInitializeDeviceErr();
    void m_slotDialogReadDeviceErr();
    void m_slotDialogOpenFileErr();
	void m_slotDialogDataFlowErr();

	void m_slotDialogDrawECGData();
    void m_slotDialogSelectedECG(int ,int *);
    void m_slotARTTimeout();
    void m_slotPlayBackTimeout();
};

#endif // SBMEECGACQUISITIONDLG_H
