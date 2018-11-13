//#include <QtGui>
#include "SBMENDISerialPortSettingsDlg.h"
#include "ui_SBMENDISerialPortSettingsDlg.h"

#include <QSerialPortInfo>

SBMENDISerialPortSettingsDlg::SBMENDISerialPortSettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMENDISerialPortSettingsDlg)
{
    ui->setupUi(this);

	setFixedSize(this->width (), this->height ());

	//NDIComIndex = -1;
	//portNumber  = -1;
	//portName    = "";

	m_pSettings = new QSettings("NDISettings.ini", QSettings::IniFormat);
    
    connect(ui->serialPortInfoListBox,  SIGNAL(currentIndexChanged(int)), this, SLOT(m_slotShowPortInfo(int)));
	connect(ui->buttonBox,              SIGNAL(accepted()),               this, SLOT(m_slotAccept()));
    //connect(ui->checkBox_Hardware,     SIGNAL(clicked(bool)),            this, SLOT(m_slotSetHandshaking(bool)));    //修改于2015/04/06
    //ui->flowControlBox->setDisabled(true);    //修改于2015/04/06
    
	FillPortsInfo();
    FillPortsParameters();
    //UpdateSettings();
	/*currentSettings.portNumber  = ui->serialPortInfoListBox->currentIndex();
	currentSettings.portName    = ui->serialPortInfoListBox->currentText();
    currentSettings.baudRate    = ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt();
	currentSettings.dataBits    = ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt();
	currentSettings.parity      = ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt();
	currentSettings.stopBits    = ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt();
	currentSettings.flowControl = ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt();*/
}

SBMENDISerialPortSettingsDlg::~SBMENDISerialPortSettingsDlg()
{
    delete ui;
}

void SBMENDISerialPortSettingsDlg::FillPortsInfo()
{
    //QSettings settings("NDISettings.ini", QSettings::IniFormat);
	ui->serialPortInfoListBox->clear();

	int NDIComIndex = -1;
    int index = 0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QStringList list;
        list << info.portName()
             << info.description()
             << info.manufacturer()
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());

        ui->serialPortInfoListBox->addItem(list.first(), list);
        if (info.manufacturer() == "NDI")
        {
            NDIComIndex = index;
        }
        index++;
    }
    if (NDIComIndex != -1)
        ui->serialPortInfoListBox->setCurrentIndex(NDIComIndex);
	else 
		if (ui->serialPortInfoListBox->count() > m_pSettings->value("/Communication/COM Port", 0).toInt())
			ui->serialPortInfoListBox->setCurrentIndex(m_pSettings->value("/Communication/COM Port", 0).toInt());
		else
			ui->serialPortInfoListBox->setCurrentIndex(0);
	
	m_pSettings->setValue("/Communication/COM Port Index", ui->serialPortInfoListBox->currentIndex());
	m_pSettings->setValue("/Communication/COM Port Name", ui->serialPortInfoListBox->currentText());
	//portNumber = ui->serialPortInfoListBox->currentIndex();
	//portName   = ui->serialPortInfoListBox->currentText();
}

void SBMENDISerialPortSettingsDlg::FillPortsParameters()
{
    //QSettings settings("NDISettings.ini",QSettings::IniFormat);

    ui->baudRateBox->addItem(QLatin1String("9600"),   9600);
    ui->baudRateBox->addItem(QLatin1String("14400"),  14400);
    ui->baudRateBox->addItem(QLatin1String("19200"),  19200);
    ui->baudRateBox->addItem(QLatin1String("38400"),  38400);
    ui->baudRateBox->addItem(QLatin1String("57600"),  57600);
    ui->baudRateBox->addItem(QLatin1String("115200"), 115200);
    ui->baudRateBox->setCurrentIndex(m_pSettings->value("/Communication/Baud Rate", 0).toInt());

    ui->dataBitsBox->addItem(QLatin1String("8"), 8);
    ui->dataBitsBox->addItem(QLatin1String("7"), 7);
    ui->dataBitsBox->setCurrentIndex(m_pSettings->value("/Communication/Data Bits", 0).toInt());

    ui->parityBox->addItem(QLatin1String("None"), 0);
    ui->parityBox->addItem(QLatin1String("Odd"), 3);
    ui->parityBox->addItem(QLatin1String("Even"), 2);
    ui->parityBox->setCurrentIndex(m_pSettings->value("/Communication/Parity", 0).toInt());

    ui->stopBitsBox->addItem(QLatin1String("1"), 1);
    ui->stopBitsBox->addItem(QLatin1String("2"), 2);
    ui->stopBitsBox->setCurrentIndex(m_pSettings->value("/Communication/Stop Bits", 0).toInt());

    ui->flowControlBox->addItem(QLatin1String("None"), 0);
    ui->flowControlBox->addItem(QLatin1String("RTS/CTS"), 1);
	//ui->flowControlBox->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);
    ui->flowControlBox->setCurrentIndex(m_pSettings->value("/Communication/Flow Control", 0).toInt());

	//ui->checkBox_Hardware->setChecked(settings.value("/Communication/Hardware", 0).toBool());
	ui->checkBox_Reset->setChecked(m_pSettings->value("/Communication/Reset Hardware", 0).toBool());
	ui->checkBox_Wireless->setChecked(m_pSettings->value("/Communication/Wireless", 0).toBool());
}

void SBMENDISerialPortSettingsDlg::UpdateSettings()
{
    //QSettings settings("NDISettings.ini", QSettings::IniFormat);

    /*currentSettings.portNumber  = ui->serialPortInfoListBox->currentIndex();
	currentSettings.portName    = ui->serialPortInfoListBox->currentText();
    currentSettings.baudRate    = ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt();
	currentSettings.dataBits    = ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt();
	currentSettings.parity      = ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt();
	currentSettings.stopBits    = ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt();
	currentSettings.flowControl = ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt();*/
	int  baudRate        = m_pSettings->value("/Communication/Baud Rate", 0).toInt();
	int  dataBits        = m_pSettings->value("/Communication/Data Bits", 0).toInt();
	int  parity          = m_pSettings->value("/Communication/Parity", 0).toInt();
	int  stopBits        = m_pSettings->value("/Communication/Stop Bits", 0).toInt();
	int  flowControl     = m_pSettings->value("/Communication/Flow Control", 0).toInt();
	bool resetChecked    = m_pSettings->value("/Communication/Reset Hardware", 0).toBool();
	bool wirelessChecked = m_pSettings->value("/Communication/Wireless", 0).toBool();

	//m_pSettings->setValue("/Communication/COM Port",       ui->serialPortInfoListBox->currentIndex());
	m_pSettings->setValue("/Communication/COM Port Index", ui->serialPortInfoListBox->currentIndex());
	m_pSettings->setValue("/Communication/COM Port Name",  ui->serialPortInfoListBox->currentText());
    m_pSettings->setValue("/Communication/Baud Rate",      ui->baudRateBox->currentIndex());
    m_pSettings->setValue("/Communication/Data Bits",      ui->dataBitsBox->currentIndex());
    m_pSettings->setValue("/Communication/Parity",         ui->parityBox->currentIndex());
    m_pSettings->setValue("/Communication/Stop Bits",      ui->stopBitsBox->currentIndex());
	m_pSettings->setValue("/Communication/Flow Control",   ui->flowControlBox->currentIndex());    //修改于2015/04/04
    m_pSettings->setValue("/Communication/Wireless",       ui->checkBox_Wireless->isChecked());
	m_pSettings->setValue("/Communication/Reset Hardware", ui->checkBox_Reset->isChecked());

	//portNumber = ui->serialPortInfoListBox->currentIndex();
	//portName   = ui->serialPortInfoListBox->currentText();

	if (baudRate        != m_pSettings->value("/Communication/Baud Rate", 0).toInt() ||
		dataBits        != m_pSettings->value("/Communication/Data Bits", 0).toInt() ||
		parity          != m_pSettings->value("/Communication/Parity", 0).toInt() ||
	    stopBits        != m_pSettings->value("/Communication/Stop Bits", 0).toInt() ||
	    flowControl     != m_pSettings->value("/Communication/Flow Control", 0).toInt() ||
	    resetChecked    != m_pSettings->value("/Communication/Reset Hardware", 0).toBool() ||
        wirelessChecked != m_pSettings->value("/Communication/Wireless", 0).toBool()
	    )
		emit m_signalCOMPortParametersChange();
}

/*SBMENDISerialPortSettingsDlg::SerialPortSettings SBMENDISerialPortSettingsDlg::Settings() const
{
    return currentSettings;
}*/

void SBMENDISerialPortSettingsDlg::m_slotShowPortInfo(int idx)
{
    if (idx != -1)
    {
        QStringList list = ui->serialPortInfoListBox->itemData(idx).toStringList();
        ui->descriptionLabel->setText(tr("Description: %1").arg(list.at(1)));
        ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.at(2)));
        ui->locationLabel->setText(tr("Location: %1").arg(list.at(3)));
        ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.at(4)));
        ui->pidLabel->setText(tr("Product Identifier: %1").arg(list.at(5)));
    }
}

void SBMENDISerialPortSettingsDlg::m_slotAccept()
{
    UpdateSettings();
    QDialog::accept();
}

/*void SBMENDISerialPortSettingsDlg::m_slotSetHandshaking(bool ishandshaking)
{
    ui->flowControlBox->setDisabled(ishandshaking);    //修改于2015/04/04
	//ui->flowControlBox->setCurrentIndex(ishandshaking ? 1 : 0);
}*/    //修改于2015/04/06
