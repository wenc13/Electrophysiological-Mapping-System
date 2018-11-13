//#include <QtGui>
#include "SBMENDISystemFeaturesDlg.h"
#include "ui_SBMENDISystemFeaturesDlg.h"

SBMENDISystemFeaturesDlg::SBMENDISystemFeaturesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMENDISystemFeaturesDlg)
{
    ui->setupUi(this);
	setFixedSize(this->width (), this->height ());
    connect(ui->OkButton, SIGNAL(clicked()), this, SLOT(m_slotAccept()));
}

SBMENDISystemFeaturesDlg::~SBMENDISystemFeaturesDlg()
{
    delete ui;
}

void SBMENDISystemFeaturesDlg::m_slotAccept()
{
    QDialog::accept();
}

void SBMENDISystemFeaturesDlg::SetVariables(char *pszVersionInfo, int nNoActivePorts, int nNoPassivePorts, int nNoActiveWireless, int nNoTIPDetection)
{
    QString str = QString(pszVersionInfo);
    str.replace("\n", "\r\n");
    ui->VersionInfoBrowser->setText(str);
    ui->label_1->setText("Number of active port:");
    ui->label_2->setText("Number of wireless:");
    ui->label_3->setText("Number of active wireless ports:");
    ui->label_4->setText("Number of ports supporting tool-in-port detection:");
    ui->lcdNumber_1->display(nNoActivePorts);
    ui->lcdNumber_2->display(nNoActiveWireless);
    ui->lcdNumber_3->display(nNoPassivePorts);
    ui->lcdNumber_4->display(nNoTIPDetection);
}

void SBMENDISystemFeaturesDlg::SetVariables(char *pszVersionInfo, int nNoMagneticPorts, int nNoFieldGenerators, int nNoFieldGeneratorCards)
{
    QString str = QString(pszVersionInfo);
    str.replace("\n", "\r\n");
    ui->VersionInfoBrowser->setText(str);
    ui->label_1->setText("Number of Magnetic Ports:");
    ui->label_2->setText("Number of Field Generators:");
    ui->label_3->setText("Number of Field Generator Cards:");
    ui->label_4->setVisible(false);
    ui->lcdNumber_1->display(nNoMagneticPorts);
    ui->lcdNumber_2->display(nNoFieldGenerators);
    ui->lcdNumber_3->display(nNoFieldGeneratorCards);
    ui->lcdNumber_4->setVisible(false);
}
