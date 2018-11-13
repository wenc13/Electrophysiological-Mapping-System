#include "SBMEECGAcquisitionDlg.h"
#include "ui_SBMEECGAcquisitionDlg.h"

#include <QPainter>
#include <QMessageBox>

SBMEECGAcquisitionDlg::SBMEECGAcquisitionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMEECGAcquisitionDlg)
{
    ui->setupUi(this);

	ui->pushButton_StopDAQ->setEnabled(false);

	ui->comboBox_InputRange->addItem("-10V~10V", 0);
    ui->comboBox_InputRange->addItem("-5V~5V", 1);
    ui->comboBox_InputRange->addItem("-2.5V~2.5V", 2);
    ui->comboBox_InputRange->addItem("0~10V", 3);
    ui->comboBox_InputRange->addItem("0~5V", 4);
    ui->comboBox_InputRange->setCurrentIndex(0);

	m_pSBMEECGAcquisition = new SBMEECGAcquisitionObj;
    m_pSBMEECGProcess     = new SBMEECGProcessObj;
    m_pThreadAcquisition  = new QThread;
    m_pThreadProcess      = new QThread;
    
	m_pSBMEECGAcquisition->moveToThread(m_pThreadAcquisition);
    m_pSBMEECGProcess->moveToThread(m_pThreadProcess);

    connect(ui->pushButton_StartDAQ, SIGNAL(clicked()),                this, SLOT(m_slotStartDataAcquisition()));
    connect(ui->pushButton_StopDAQ,  SIGNAL(clicked()),                this, SLOT(m_slotStopDataAcquisition()));
    connect(ui->comboBox_InputRange, SIGNAL(currentIndexChanged(int)), this, SLOT(m_slotSetInputRange(int)));
    connect(ui->pushButton_PlayBack, SIGNAL(clicked()),                this, SLOT(m_slotPlayBack()));

    connect(this, SIGNAL(m_signalStartAcquisition()), m_pSBMEECGAcquisition, SLOT(m_slotECGAcquisitionStart()));
    connect(this, SIGNAL(m_signalStartProcess()),     m_pSBMEECGProcess,     SLOT(m_slotECGProcessStart()));

	//connect(this, SIGNAL(m_signalStopAcquisition()), m_pSBMEECGAcquisition, SLOT(m_slotECGAcquisitionStop()));
	
    connect(m_pSBMEECGAcquisition, SIGNAL(m_signalAcqObjCreateDeviceErr()),     this, SLOT(m_slotDialogCreateDeviceErr()));
    connect(m_pSBMEECGAcquisition, SIGNAL(m_signalAcqObjInitializeDeviceErr()), this, SLOT(m_slotDialogInitializeDeviceErr()));
    connect(m_pSBMEECGAcquisition, SIGNAL(m_signalAcqObjReadDeviceErr()),       this, SLOT(m_slotDialogReadDeviceErr()));
	connect(m_pSBMEECGAcquisition, SIGNAL(m_signalAcqObjDataFlowErr()),         this, SLOT(m_slotDialogDataFlowErr()));
	
    connect(m_pSBMEECGProcess, SIGNAL(m_signalAcqObjOpenFileErr()),  this, SLOT(m_slotDialogOpenFileErr()));
    connect(m_pSBMEECGProcess, SIGNAL(m_signalProObjDataProcessd()), this, SLOT(m_slotDialogDrawECGData()));

	/*setWindowTitle(QString("ART Data Acquisition"));
    Qt::WindowFlags flags = Qt::Window;
    setWindowFlags(flags);

	setAutoFillBackground(true);
	setBackgroundRole(QPalette::Dark);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);*/

    //ui->pushButton_StartDAQ->setEnabled(false);
	//ui->pushButton_PlayBack->setEnabled(false);

    //sbme_bThreadECGFlagAcq = false;
    //sbme_bThreadECGFlagPro = false;

    //memset(sbme_ADBuffer, 0x00, sizeof(sbme_ADBuffer));
	for (int i = 0; i < SBME_MAX_SEGMENT_COUNT; i++)
		for (int j = 0; j < 32768; j++)
            sbme_ADBuffer[i][j] = 0;

    for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
        for (int j = 0; j < 16; j++)
            sbme_ThreadECGfloat[i][j] = 0;

    for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
        for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
		{
            m_ECGDataPoint[i][j].setX(j);
            m_ECGDataPoint[i][j].setY(0);
            m_ECGDataFloat[i][j] = 0;
		}

    m_nSelectedECGNum = 0;

    m_bStarting       = false;
    m_bRealTime       = false;

    m_nDrawWidth = qMax(ui->pushButton_StartDAQ->width(), ui->comboBox_InputRange->width());
    m_nDrawWidth += 15;
    m_DrawColor[0] = QColor(142, 21, 195);
    m_DrawColor[1] = QColor(2, 164, 2);
    m_DrawColor[2] = QColor(188, 29, 73);
    m_DrawColor[3] = QColor(211, 73, 39);
    m_DrawColor[4] = QColor(28, 160, 225);
    m_DrawColor[5] = QColor(0, 216, 203);
    m_DrawColor[6] = QColor(230, 214, 4);
    m_DrawColor[7] = QColor(41, 0, 104);

    /*m_pARTTimer = new QTimer();
    connect(m_pARTTimer, SIGNAL(timeout), this, SLOT(m_slotARTTimeout()));
    m_pPlayBackTimer = new QTimer();
    connect(m_pPlayBackTimer, SIGNAL(timeout), this, SLOT(m_slotPlayBackTimeout()));*/
	
	m_pThreadAcquisition->start();
	m_pThreadProcess->start();
}

SBMEECGAcquisitionDlg::~SBMEECGAcquisitionDlg()
{
    delete ui;
}

void SBMEECGAcquisitionDlg::paintEvent(QPaintEvent *event)
{
	DrawBackGround();
	DrawECGText();
	DrawECGData();
	DrawMouseClickPoint();
}

void SBMEECGAcquisitionDlg::closeEvent(QCloseEvent *event)
{
    m_slotStopDataAcquisition();
}

void SBMEECGAcquisitionDlg::mousePressEvent(QMouseEvent *event)
{
    if (m_nSelectedECGNum == 0)
		return;
    if (event->button() == Qt::LeftButton)
	{
        if ((event->pos().x() >= 30) &&
           (event->pos().x() <= this->width() - m_nDrawWidth) &&
           (event->pos().y() >= 0) &&
           (event->pos().y() <= this->height()))
		{
			QCursor cursor;
			cursor.setShape(Qt::CrossCursor);
			QApplication::setOverrideCursor(cursor);
		}
	}
}

void SBMEECGAcquisitionDlg::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_nSelectedECGNum == 0)
		return;
    if (event->button() == Qt::LeftButton)
	{	
		int channelsegment;
		int minindex;
        float minpointdistance = this->height() / m_nSelectedECGNum;
        for (int i = 0; i < m_nSelectedECGNum; i++)
            if (event->pos().y() >= (i * this->height() / m_nSelectedECGNum) &&
                event->pos().y() < ((i+1) * this->height() / m_nSelectedECGNum))
			{
                channelsegment = m_nSelectedECGNum - 1 - i;
				break;
			}

		float tempdistance;
        if ((this->width() - m_nDrawWidth - 30) > SBME_MAX_PAINT_POINT)
		{
            for (int i = qFloor((event->pos().x() - 30) * SBME_MAX_PAINT_POINT / (this->width() - m_nDrawWidth - 30)) - 10;
                 i <= qFloor((event->pos().x() - 30) * SBME_MAX_PAINT_POINT / (this->width() - m_nDrawWidth - 30)) + 10;
                 i++)
			{
                tempdistance = qSqrt(qPow(event->pos().x() - m_ECGDataPoint[m_pDialogChannel[channelsegment]][i].x(), 2)
                             + qPow((this->height() - event->pos().y()) - m_ECGDataPoint[m_pDialogChannel[channelsegment]][i].y(), 2));
                if (minpointdistance > tempdistance)
				{
					minpointdistance = tempdistance;
					minindex = i;
				}
			}
		}
		else
            for (int i = qFloor(event->pos().x() - 30) - 10; i <= qFloor(event->pos().x() - 30) + 10; i++)
			{
                tempdistance = qSqrt(qPow(event->pos().x() - m_ECGDataPoint[m_pDialogChannel[channelsegment]][i].x(), 2)
                             + qPow((this->height() - event->pos().y()) - m_ECGDataPoint[m_pDialogChannel[channelsegment]][i].y(), 2));
                if (minpointdistance > tempdistance)
				{
					minpointdistance = tempdistance;
					minindex = i;
				}
			}
        if (minpointdistance <= 8)
		{
            if (m_MouseClickPoint.contains(QPoint(minindex, channelsegment)))
                m_MouseClickPoint.removeOne(QPoint(minindex, channelsegment));
			else
                m_MouseClickPoint.append(QPoint(minindex, channelsegment));
			update();
		}
		QApplication::restoreOverrideCursor();
	}
}

void SBMEECGAcquisitionDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
	{

	}
}

void SBMEECGAcquisitionDlg::DrawBackGround()
{
	QPainter BackGroundPainter(this);
    BackGroundPainter.translate(0, this->height());
    BackGroundPainter.scale(1, -1);
	QPen BackGroundPen(Qt::black);
	BackGroundPen.setStyle(Qt::DotLine);
	BackGroundPainter.setPen(BackGroundPen);
    for (int i = 0; i < this->height();)
	{
        BackGroundPainter.drawLine(30, i, this->width()-m_nDrawWidth, i);
        i += 10;
	}
    for (int i = 30; i < this->width() - m_nDrawWidth;)
	{
        BackGroundPainter.drawLine(i, 0, i, this->height());
        i += 10;
	}
}

void SBMEECGAcquisitionDlg::DrawECGText()
{
	QPainter TextPainter(this);
    switch (m_nSelectedECGNum)
	{
	case 8:
        TextPainter.setPen(QPen(m_DrawColor[7], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 8 + 1)), QString("CH%1").arg(m_pDialogChannel[7]+1));
	case 7:
        TextPainter.setPen(QPen(m_DrawColor[6], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 7 + 1)), QString("CH%1").arg(m_pDialogChannel[6]+1));
	case 6:
        TextPainter.setPen(QPen(m_DrawColor[5], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 6 + 1)), QString("CH%1").arg(m_pDialogChannel[5]+1));
	case 5:
        TextPainter.setPen(QPen(m_DrawColor[4], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 5 + 1)), QString("CH%1").arg(m_pDialogChannel[4]+1));
	case 4:
        TextPainter.setPen(QPen(m_DrawColor[3], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 4 + 1)), QString("CH%1").arg(m_pDialogChannel[3]+1));
	case 3:
        TextPainter.setPen(QPen(m_DrawColor[2], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 3 + 1)), QString("CH%1").arg(m_pDialogChannel[2]+1));
	case 2:
        TextPainter.setPen(QPen(m_DrawColor[1], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 2 + 1)), QString("CH%1").arg(m_pDialogChannel[1]+1));
	case 1:
        TextPainter.setPen(QPen(m_DrawColor[0], 1.5));
        TextPainter.drawText(QPointF(6, this->height() / (2 * m_nSelectedECGNum) * (2 * m_nSelectedECGNum - 2 * 1 + 1)), QString("CH%1").arg(m_pDialogChannel[0]+1));
		break;
	case 0:
		break;
	}
}

void SBMEECGAcquisitionDlg::DrawECGData()
{
	QPainter DataPainter(this);
    DataPainter.translate(0, this->height());
    DataPainter.scale(1, -1);

    if (m_nSelectedECGNum != 0)
        for (int i = 0; i < m_nSelectedECGNum; i++)
            for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
                m_ECGDataPoint[m_pDialogChannel[i]][j].setY(m_ECGDataFloat[m_pDialogChannel[i]][j] * (this->height() / (2 * m_nSelectedECGNum)) / 10000 +
                this->height() / (2 * m_nSelectedECGNum) * (2 * i + 1));
	else
		return;

    if ((this->width() - m_nDrawWidth - 30) > SBME_MAX_PAINT_POINT)
	{
        for (int i = 0; i < m_nSelectedECGNum; i++)
            for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
                m_ECGDataPoint[m_pDialogChannel[i]][j].setX(j * (this->width() - m_nDrawWidth - 30) / SBME_MAX_PAINT_POINT + 30);
        switch (m_nSelectedECGNum)
		{
		case 8:
            DataPainter.setPen(QPen(m_DrawColor[7], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[7]], SBME_MAX_PAINT_POINT);
		case 7:
            DataPainter.setPen(QPen(m_DrawColor[6], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[6]], SBME_MAX_PAINT_POINT);
		case 6:
            DataPainter.setPen(QPen(m_DrawColor[5], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[5]], SBME_MAX_PAINT_POINT);
		case 5:
            DataPainter.setPen(QPen(m_DrawColor[4], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[4]], SBME_MAX_PAINT_POINT);
		case 4:
            DataPainter.setPen(QPen(m_DrawColor[3], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[3]], SBME_MAX_PAINT_POINT);
		case 3:
            DataPainter.setPen(QPen(m_DrawColor[2],1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[2]],SBME_MAX_PAINT_POINT);
		case 2:
            DataPainter.setPen(QPen(m_DrawColor[1], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[1]], SBME_MAX_PAINT_POINT);
		case 1:
            DataPainter.setPen(QPen(m_DrawColor[0], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[0]], SBME_MAX_PAINT_POINT);
			break;
		}
	}
	else
	{
        for (int i = 0; i < m_nSelectedECGNum; i++)
            for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
                m_ECGDataPoint[m_pDialogChannel[i]][j].setX(j + 30);
        switch (m_nSelectedECGNum)
		{
		case 8:
            DataPainter.setPen(QPen(m_DrawColor[7], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[7]], this->width() - m_nDrawWidth - 30);
		case 7:
            DataPainter.setPen(QPen(m_DrawColor[6], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[6]], this->width() - m_nDrawWidth - 30);
		case 6:
            DataPainter.setPen(QPen(m_DrawColor[5], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[5]], this->width() - m_nDrawWidth - 30);
		case 5:
            DataPainter.setPen(QPen(m_DrawColor[4], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[4]], this->width() - m_nDrawWidth - 30);
		case 4:
            DataPainter.setPen(QPen(m_DrawColor[3], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[3]], this->width() - m_nDrawWidth - 30);
		case 3:
            DataPainter.setPen(QPen(m_DrawColor[2], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[2]], this->width() - m_nDrawWidth - 30);
		case 2:
            DataPainter.setPen(QPen(m_DrawColor[1], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[1]], this->width() - m_nDrawWidth - 30);
		case 1:
            DataPainter.setPen(QPen(m_DrawColor[0], 1.5));
            DataPainter.drawPolyline(m_ECGDataPoint[m_pDialogChannel[0]], this->width() - m_nDrawWidth - 30);
			break;
		}
	}
}

void SBMEECGAcquisitionDlg::DrawMouseClickPoint()
{
	QPainter PointPainter(this);
    PointPainter.translate(0, this->height());
    PointPainter.scale(1, -1);
    QPen PointPen(Qt::red, 4);
	PointPainter.setPen(PointPen);
    foreach (QPoint pointf, m_MouseClickPoint)
        if ((this->width() - m_nDrawWidth - 30) > SBME_MAX_PAINT_POINT)
            PointPainter.drawPoint(QPointF(pointf.x() * (this->width() - m_nDrawWidth - 30) / SBME_MAX_PAINT_POINT + 30,
                                   m_ECGDataFloat[m_pDialogChannel[pointf.y()]][pointf.x()] * (this->height() / (2 * m_nSelectedECGNum)) / 10000 +
                                   this->height() / (2 * m_nSelectedECGNum) * (2 * pointf.y() + 1)));
		else
            if (pointf.x() <= this->width() - m_nDrawWidth - 30)
                PointPainter.drawPoint(QPointF(pointf.x() + 30,
                                       m_ECGDataFloat[m_pDialogChannel[pointf.y()]][pointf.x()] * (this->height() / (2 * m_nSelectedECGNum)) / 10000 +
                                       this->height() / (2 * m_nSelectedECGNum) * (2 * pointf.y() + 1)));
}

void SBMEECGAcquisitionDlg::DrawPlayBack()
{
}

void SBMEECGAcquisitionDlg::AcquisitionStopped()
{
	ui->pushButton_StartDAQ->setEnabled(true);
    ui->pushButton_StopDAQ->setEnabled(false);
	ui->comboBox_InputRange->setEnabled(true);
	ui->pushButton_PlayBack->setEnabled(true);

	emit m_signalECGControlPanelDlgEnabled(true);

	m_bStarting = false;
}

void SBMEECGAcquisitionDlg::m_slotStartDataAcquisition()
{    
    for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
        for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
		{
            m_ECGDataPoint[i][j].setX(j);
            m_ECGDataPoint[i][j].setY(0);
            m_ECGDataFloat[i][j] = 0;
		}
    
	m_bStarting = true;
    m_bRealTime = true;
	
	ui->pushButton_StartDAQ->setEnabled(false);
    ui->pushButton_StopDAQ->setEnabled(true);
	ui->comboBox_InputRange->setEnabled(false);
	ui->pushButton_PlayBack->setEnabled(false);

	emit m_signalECGControlPanelDlgEnabled(false);
    emit m_signalStartAcquisition();
    emit m_signalStartProcess();
	
	//ARTTimer->start(10);
}

void SBMEECGAcquisitionDlg::m_slotStopDataAcquisition()
{
    m_pSBMEECGAcquisition->ECGAcquisitionStop();
    m_pSBMEECGProcess->ECGProcessStop();

	//≤‚ ‘¥˙¬Î
	//emit m_signalStopAcquisition();
	//≤‚ ‘¥˙¬Î
	
	AcquisitionStopped();

    //m_bStarting = false;
}

void SBMEECGAcquisitionDlg::m_slotSetInputRange(int inputrange)
{
    m_pSBMEECGProcess->ProObjSetInputRange(inputrange);
}

void SBMEECGAcquisitionDlg::m_slotPlayBack()
{
    if (ui->pushButton_PlayBack->text() == "Play Back")
	{
        m_pSBMEECGPlayBackDlg = new SBMEECGPlayBackDlg(this);
        connect(m_pSBMEECGPlayBackDlg, SIGNAL(m_signalPlayBackTime(int *)), this,  SLOT(m_slotPlayBackTime(int *)));
        m_pSBMEECGPlayBackDlg->setModal(true);
        m_pSBMEECGPlayBackDlg->show();
	}
	else
	{
		ui->pushButton_PlayBack->setText("Play Back");
		ui->pushButton_StartDAQ->setEnabled(true);
	}
}

void SBMEECGAcquisitionDlg::m_slotPlayBackTime(int *palybacktime)
{
    /*for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
        for (int j = 0; j < SBME_MAX_PAINT_POINT; j++)
		{
            m_ARTDataPoint[i][j].setX(j);
            m_ARTDataPoint[i][j].setY(0);
            m_ARTDataFloat[i][j] = 0;
		}
    m_bRealTime = false;
	ui->pushButton_StartDAQ->setEnabled(false);
	ui->pushButton_PlayBack->setText("Stop Reply");
    m_pPlayBackTime = palybacktime;
	
	QFile ARTDialogFile("ARTData.txt");
    if (!ARTDialogFile.open(QIODevice::ReadOnly|QIODevice::Text))
	{
        QMessageBox::critical(this, "Play Back Error", "Cannot open file for replaying!", QMessageBox::Ok);
		return;
	}
	QTextStream ARTDialogIn(&ARTDialogFile);
	
	QString playbacklinein = ARTDialogIn.readLine();
	QStringList playbackstringlist = playbacklinein.split(" ");
    for (int i = 0; i < 32; i++)
		QString str = playbackstringlist[i];*/
	
	/*if(!QFile::exists("ARTData.txt"))
	{
		QMessageBox::critical(this,"Locate File Error","The data file does not exist!",QMessageBox::Ok);
		return;
	}
	QFile ARTDialogFile("ARTData.txt");
	if(!ARTDialogFile.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QMessageBox::critical(this,"Play Back Error","Cannot open file for replaying!",QMessageBox::Ok);
		return;
	}
	QTextStream ARTDialogIn(&ARTDialogFile);
	qint64 begintime = (pPlayBackTime[0]*3600+pPlayBackTime[1]*60+pPlayBackTime[2])*4000;
	qint64 endtime = (pPlayBackTime[0]*3600+pPlayBackTime[1]*60+pPlayBackTime[2])*4000 > ARTDialogFile.size()?(pPlayBackTime[0]*3600+pPlayBackTime[1]*60+pPlayBackTime[2])*4000:ARTDialogFile.size();
	QList<float> playbacklist;
	for(int i=0;i<32;i++)
		playbacklist.append(0);
	for(qint64 i = ARTDialogIn.seek(begintime);i<ARTDialogIn.seek(endtime);)
	{
		QString playbacklinein = ARTDialogIn.readLine();
		QStringList playbackstringlist = playbacklinein.split(" ");
		for(int i=0;i<32;i++)
		{
			playbacklist.removeLast();
			playbacklist.prepend(Volt);
		}
		i+=128;
	}*/
}

void SBMEECGAcquisitionDlg::m_slotDialogCreateDeviceErr()
{
    QMessageBox::critical(this, "Create Device Error", "Create Device Error!", QMessageBox::Ok);

	AcquisitionStopped();
}

void SBMEECGAcquisitionDlg::m_slotDialogInitializeDeviceErr()
{
    QMessageBox::critical(this, "Initialize Device Error", "USB2805_InitDeviceAD Error!", QMessageBox::Ok);

	AcquisitionStopped();
}

void SBMEECGAcquisitionDlg::m_slotDialogReadDeviceErr()
{
    QMessageBox::critical(this, "Read Device Error", "Read Device Error!", QMessageBox::Ok);

	AcquisitionStopped();
}

void SBMEECGAcquisitionDlg::m_slotDialogOpenFileErr()
{
    QMessageBox::critical(this, "Open File Error", "Cannot open file for writing!", QMessageBox::Ok);

	AcquisitionStopped();
}

void SBMEECGAcquisitionDlg::m_slotDialogDataFlowErr()
{
	QMessageBox::critical(this, "Data Flow Error", "Data Flow, ECG Acquisition has stopped!", QMessageBox::Ok);
	
	AcquisitionStopped();
    //m_bStarting = false;

	//≤‚ ‘¥˙¬Î
	//m_pSBMEECGAcquisition->ECGAcquisitionStop();
	//≤‚ ‘¥˙¬Î
}

void SBMEECGAcquisitionDlg::m_slotDialogDrawECGData()
{
    if (m_bStarting)
	{
        for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
            for (int j = 511; j > 15; j--)
                m_ECGDataFloat[i][j] = m_ECGDataFloat[i][j-16];
        for (int i = 0; i < SBME_MAX_CHANNEL_COUNT; i++)
            for (int j = 0; j < 16; j++)
                m_ECGDataFloat[i][j] = sbme_ThreadECGfloat[i][j];
        //sbme_bThreadECGFlagPro = false;
		update();
	}
	else
		return;
}

void SBMEECGAcquisitionDlg::m_slotDialogSelectedECG(int selectedARTnum, int *selectedARTindex)
{
    m_nSelectedECGNum = selectedARTnum;
    m_pDialogChannel = selectedARTindex;
    
	if (!ui->pushButton_StartDAQ->isEnabled())
		ui->pushButton_StartDAQ->setEnabled(true);
    
	if (!ui->pushButton_PlayBack->isEnabled())
		ui->pushButton_PlayBack->setEnabled(true);
	
	update();
}

void SBMEECGAcquisitionDlg::m_slotARTTimeout()
{
}

void SBMEECGAcquisitionDlg::m_slotPlayBackTimeout()
{
}
