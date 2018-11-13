#include "SBMEStereoProjectorControlPanelDlg.h"
#include "ui_SBMEStereoProjectorControlPanelDlg.h"

SBMEStereoProjectorControlPanelDlg::SBMEStereoProjectorControlPanelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMEStereoProjectorControlPanelDlg)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider_FocalDistance, SIGNAL(valueChanged(int)), this, SLOT(m_slotPopChangedFocusDistance(int)));
    connect(ui->horizontalSlider_PupilDistance, SIGNAL(valueChanged(int)), this, SLOT(m_slotPopChangedPupilDistance(int)));
    connect(ui->horizontalSlider_Fovy,          SIGNAL(valueChanged(int)), this, SLOT(m_slotPopChangedFovy(int)));
    
	ui->horizontalSlider_FocalDistance->setMaximum(3000);
    ui->horizontalSlider_FocalDistance->setValue(100);
    ui->horizontalSlider_PupilDistance->setValue(66);
    ui->horizontalSlider_Fovy->setValue(60);
}

SBMEStereoProjectorControlPanelDlg::~SBMEStereoProjectorControlPanelDlg()
{
    delete ui;
}

void SBMEStereoProjectorControlPanelDlg::m_slotPopChangedFocusDistance(int FD)
{
    ui->label_FD->setNum(FD);
    emit m_signalFocusDistanceChanged(FD);
}

void SBMEStereoProjectorControlPanelDlg::m_slotPopChangedPupilDistance(int PD)
{
    ui->label_PD->setNum(PD);
    emit m_signalPupilDistanceChanged(PD);
}

void SBMEStereoProjectorControlPanelDlg::m_slotPopChangedFovy(int Fovy)
{
    ui->label_Fovy->setNum(Fovy);
    emit m_signalFovyChanged(Fovy);
}
