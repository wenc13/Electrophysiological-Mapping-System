//#include <QtGui>
#include "SBMENDIProgramOptionDlg.h"
#include "ui_SBMENDIProgramOptionDlg.h"

#include <QFileDialog>

SBMENDIProgramOptionDlg::SBMENDIProgramOptionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMENDIProgramOptionDlg)
{
    ui->setupUi(this);
	
	setFixedSize(this->width (), this->height ());
	connect(ui->checkBox_LogToFile,     SIGNAL(clicked()),  this, SLOT(m_slotOnLogToFile()));
    connect(ui->checkBox_BeepOnError,   SIGNAL(clicked()),  this, SLOT(m_slotOnBeepOnError()));
	connect(ui->pushButton_Browser,     SIGNAL(clicked()),  this, SLOT(m_slotOnBrowse()));
    connect(ui->checkBox_BeepOnWarning, SIGNAL(clicked()),  this, SLOT(m_slotOnBeepOnWarning()));
	connect(ui->buttonBox,              SIGNAL(accepted()), this, SLOT(m_slotAccept()));

    m_pSettings = new QSettings("NDISettings.ini", QSettings::IniFormat);
    InitiallizeDlg();
    m_slotOnLogToFile();
    m_slotOnBeepOnError();
    m_slotOnBeepOnWarning();
}

SBMENDIProgramOptionDlg::~SBMENDIProgramOptionDlg()
{
    delete ui;
}

void SBMENDIProgramOptionDlg::InitiallizeDlg()
{
    ui->checkBox_LogToFile->setChecked(m_pSettings->value("/Logging Options/Log To File", 0).toBool());
	ui->lineEdit_FileName->setText(m_pSettings->value("/Logging Options/Log File Name", "").toString());
    ui->checkBox_DateStamp->setChecked(m_pSettings->value("/Logging Options/Date Time Stamp", 0).toBool());
	ui->checkBox_ClearlogFile->setChecked(m_pSettings->value("/Logging Options/Clear File", 0).toBool());
    
	ui->checkBox_BeepOnError->setChecked(m_pSettings->value("/Beeping Options/Beep On Error", 0).toBool());
    ui->spinBox_BeepOnErrorNum->setValue(m_pSettings->value("/Beeping Options/No Error Beeps", 1).toInt());
    ui->checkBox_BeepOnWarning->setChecked(m_pSettings->value("/Beeping Options/Beep On Warning", 0).toBool());
    ui->spinBox_BeepOnWarningNum->setValue(m_pSettings->value("/Beeping Options/No Warning Beeps", 1).toInt());
    
	ui->checkBox_ReportWhileTracking->setChecked(m_pSettings->value("/Reporting Options/Report While Tracking", 1).toBool());
}

void SBMENDIProgramOptionDlg::m_slotOnLogToFile()
{
    bool IsLogToFile = ui->checkBox_LogToFile->isChecked();
    ui->lineEdit_FileName->setEnabled(IsLogToFile);
    ui->pushButton_Browser->setEnabled(IsLogToFile);
    ui->checkBox_DateStamp->setEnabled(IsLogToFile);
    ui->checkBox_ClearlogFile->setEnabled(IsLogToFile);
}

void SBMENDIProgramOptionDlg::m_slotOnBeepOnError()
{
    bool IsBeepOnError = ui->checkBox_BeepOnError->isChecked();
    ui->spinBox_BeepOnErrorNum->setEnabled(IsBeepOnError);
}

void SBMENDIProgramOptionDlg::m_slotOnBeepOnWarning()
{
    bool IsBeepOnWarning = ui->checkBox_BeepOnWarning->isChecked();
    ui->spinBox_BeepOnWarningNum->setEnabled(IsBeepOnWarning);
}

void SBMENDIProgramOptionDlg::m_slotOnBrowse()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), " ", tr("Text files (*.txt)"));
    ui->lineEdit_FileName->setText(fileName);
}

void SBMENDIProgramOptionDlg::m_slotAccept()
{
    m_pSettings->setValue("/Logging Options/Log To File", ui->checkBox_LogToFile->isChecked());
	m_pSettings->setValue("/Logging Options/Log File Name", ui->lineEdit_FileName->text());
    m_pSettings->setValue("/Logging Options/Date Time Stamp", ui->checkBox_DateStamp->isChecked());
	m_pSettings->setValue("/Logging Options/Clear File", ui->checkBox_ClearlogFile->isChecked());
    
    m_pSettings->setValue("/Beeping Options/Beep On Error", ui->checkBox_BeepOnError->isChecked());
    m_pSettings->setValue("/Beeping Options/No Error Beeps", ui->spinBox_BeepOnErrorNum->value());
    m_pSettings->setValue("/Beeping Options/Beep On Warning", ui->checkBox_BeepOnWarning->isChecked());
    m_pSettings->setValue("/Beeping Options/No Warning Beeps", ui->spinBox_BeepOnWarningNum->value());
    
	m_pSettings->setValue("/Reporting Options/Report While Tracking", ui->checkBox_ReportWhileTracking->isChecked());
    
	QDialog::accept();
}
