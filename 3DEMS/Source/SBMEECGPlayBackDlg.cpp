#include "SBMEECGPlayBackDlg.h"
#include "ui_SBMEECGPlayBackDlg.h"
#include <QMessageBox>

SBMEECGPlayBackDlg::SBMEECGPlayBackDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMEECGPlayBackDlg)
{
	ui->setupUi(this);

    setWindowTitle(QString("Time Range Input"));
    Qt::WindowFlags flags = Qt::Window;
    setWindowFlags(flags);

    connect(ui->lineEdit_PlayBackBegin,    SIGNAL(textChanged(const QString &)), this, SLOT(m_slotPlayBackTimeBegin(const QString &)));
    connect(ui->lineEdit_PlayBackEnd,      SIGNAL(textChanged(const QString &)), this, SLOT(m_slotPlayBackTimeEnd(const QString &)));
    connect(ui->pushButton_PlayBackOK,     SIGNAL(clicked()),                    this, SLOT(m_slotPlayBackOK()));
    connect(ui->pushButton_PlayBackCancel, SIGNAL(clicked()),                    this, SLOT(m_slotPlayBackCancel()));

	ui->lineEdit_PlayBackBegin->setText("00:00:00");
	ui->lineEdit_PlayBackEnd->setText("00:00:00");
}

SBMEECGPlayBackDlg::~SBMEECGPlayBackDlg()
{
    delete ui;
}

void SBMEECGPlayBackDlg::m_slotPlayBackTimeBegin(const QString &begintime)
{
    m_BeginTimeList = begintime.split(":");
    m_PlayBackTime[0] = m_BeginTimeList[0].toInt();
    m_PlayBackTime[1] = m_BeginTimeList[1].toInt();
    m_PlayBackTime[2] = m_BeginTimeList[2].toInt();
}

void SBMEECGPlayBackDlg::m_slotPlayBackTimeEnd(const QString &endtime)
{
    m_EndTimeList = endtime.split(":");
    m_PlayBackTime[3] = m_EndTimeList[0].toInt();
    m_PlayBackTime[4] = m_EndTimeList[1].toInt();
    m_PlayBackTime[5] = m_EndTimeList[2].toInt();
}

void SBMEECGPlayBackDlg::m_slotPlayBackOK()
{
    if ((m_PlayBackTime[0] * 3600 + m_PlayBackTime[1] * 60 + m_PlayBackTime[2]) > (m_PlayBackTime[3] * 3600 + m_PlayBackTime[4] * 60 + m_PlayBackTime[5]))
	{
        QMessageBox::critical(this, "Time Error", "The begin time is greater than the end time!", QMessageBox::Ok);
		return;
	}
    emit m_signalPlayBackTime(m_PlayBackTime);
	return accept();
}

void SBMEECGPlayBackDlg::m_slotPlayBackCancel()
{
	return accept();
}
