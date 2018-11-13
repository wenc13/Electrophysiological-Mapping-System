#include "SBMENDIRomFileDlg.h"
#include "ui_SBMENDIRomFileDlg.h"

#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>

SBMENDIRomFileDlg::SBMENDIRomFileDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMENDIRomFileDlg)
{
    ui->setupUi(this);
	setFixedSize(this->width (), this->height ());
    connect(ui->pushButton_Close,    SIGNAL(clicked()),             this, SLOT(m_slotOnClose()));
    connect(ui->pushButton_Browse,   SIGNAL(clicked()),             this, SLOT(m_slotOnBrowse()));
    connect(ui->pushButton_Save,     SIGNAL(clicked()),             this, SLOT(m_slotOnSave()));
    connect(ui->tableWidget_RomFile, SIGNAL(cellClicked(int, int)), this, SLOT(m_slotOnClickTable(int, int)));

    m_pSettings = new QSettings("NDISettings.ini", QSettings::IniFormat);
    m_bChangesSaved = false;
    m_sPortID = "";
    m_sROMFile = "";

    ui->tableWidget_RomFile->setColumnCount(2);
    ui->tableWidget_RomFile->setRowCount(0);
    QStringList HeaderLbles;
    HeaderLbles<<"Port ID"<<"SROM Image File";
    ui->tableWidget_RomFile->setHorizontalHeaderLabels(HeaderLbles);
    m_nCurrentRow = 0;
    m_bFillTablebFinished = false;

    ui->pushButton_Browse->setDisabled(true);
    ui->pushButton_Save->setDisabled(true);
    ui->lineEdit_RomFileName->setReadOnly(false);
}

SBMENDIRomFileDlg::~SBMENDIRomFileDlg()
{
    delete ui;
}

void SBMENDIRomFileDlg::m_slotOnClose()
{
    if (m_bChangesSaved)
    {
        QMessageBox::information(this, "Attention!", "You must re-initialize your system before SROM Image File\n"
                                 "changes will be applied.", QMessageBox::Ok);
        emit m_signalRomFileChanged();
        m_bChangesSaved = false;
    }
    close();
}

void SBMENDIRomFileDlg::FillRomFileTable()
{
    QString	RomFileName;
    char pszPortID[20];
    int	i = 0;
    for (i = 1; i <= m_nNoPassivePorts; i++)
    {
        sprintf(pszPortID, "Wireless Tool %02d", i);
        QString key = "/POLARIS SROM Image Files/";
        key += pszPortID;
        RomFileName = m_pSettings->value(key).toString();
        AddItemToList(QString(pszPortID), RomFileName);
    }
    if (m_nNoActivePorts == 4)
        m_nNoActivePorts = 12;
    for (i = 1 ; i <= m_nNoActivePorts; i++)
    {
        if (i == 4)
        {
            sprintf(pszPortID, "Port %d", i);
            AddItemToList(QString(pszPortID), "TDS Expansion Port");
            continue;
        }
        QString key = "/POLARIS SROM Image Files/";
        sprintf(pszPortID, "Port %d", i);
        key += pszPortID;
        RomFileName = m_pSettings->value(key).toString();
        AddItemToList(QString(pszPortID), RomFileName);
    }
    for (i = 1 ; i <= m_nNoMagneticPorts; i++)
    {
        QString key="/AURORA SROM Image Files/";
        sprintf(pszPortID, "Port %d", i);
        key += pszPortID;
        RomFileName = m_pSettings->value(key).toString();
        AddItemToList(QString(pszPortID), RomFileName);
    }
}

void SBMENDIRomFileDlg::AddItemToList(QString PortID, QString RomFileName)
{
    QTableWidgetItem *newitem = new QTableWidgetItem(PortID);
    QTableWidgetItem *newitem2 = new QTableWidgetItem(RomFileName);
    ui->tableWidget_RomFile->insertRow(m_nCurrentRow);
    ui->tableWidget_RomFile->setItem(m_nCurrentRow, 0, newitem);
    ui->tableWidget_RomFile->setItem(m_nCurrentRow, 1, newitem2);
    m_nCurrentRow++;
}

void SBMENDIRomFileDlg::m_slotOnBrowse()
{
    m_sROMFile = QFileDialog::getOpenFileName(this, tr("Open RomFile"), "", tr("Rom Files (*.rom *.Rom)"));
    ui->lineEdit_RomFileName->setText(m_sROMFile);
}

void SBMENDIRomFileDlg::m_slotOnSave()
{
    ui->tableWidget_RomFile->item(m_nCurrentRow, 1)->setText(m_sROMFile);
    if (m_nNoMagneticPorts > 0)
        m_pSettings->setValue("/AURORA SROM Image Files/" + m_sPortID,m_sROMFile);
    else
        m_pSettings->setValue("/POLARIS SROM Image Files/" + m_sPortID,m_sROMFile);
    m_bChangesSaved = true;
}

void SBMENDIRomFileDlg::m_slotOnClickTable(int row, int column)
{
    m_nCurrentRow = row;
    m_sPortID = ui->tableWidget_RomFile->item(row, 0)->text();
    m_sROMFile = ui->tableWidget_RomFile->item(row, 1)->text();
    ui->lineEdit_PortID->setText(m_sPortID);
    ui->lineEdit_RomFileName->setText(m_sROMFile);
    if ((m_nTypeofSystem != AURORA_SYSTEM) && (m_sPortID.contains("Port 4")))
    {
        ui->lineEdit_PortID->setDisabled(true);
        ui->lineEdit_RomFileName->setDisabled(true);
        ui->pushButton_Browse->setDisabled(true);
        ui->pushButton_Save->setDisabled(true);
    }
    else
    {
        ui->lineEdit_PortID->setEnabled(true);
        ui->lineEdit_RomFileName->setEnabled(true);
        ui->pushButton_Browse->setEnabled(true);
        ui->pushButton_Save->setEnabled(true);
    }
}

void SBMENDIRomFileDlg::SetSysteminfo(int nTypeofSystem, int nNoActivePorts, int nNoPassivePorts, int nNoMagneticPorts)
{
    if (!m_bFillTablebFinished)
    {
        m_nTypeofSystem = nTypeofSystem;
        m_nNoActivePorts = nNoActivePorts;
        m_nNoPassivePorts = nNoPassivePorts;
        m_nNoMagneticPorts = nNoMagneticPorts;
        FillRomFileTable();
        m_bFillTablebFinished = true;
    }
}
