#include "SBMEColorDlg.h"
#include "ui_SBMEColorDlg.h"

SBMEColorDlg::SBMEColorDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::SBMEColorDlg)
{
    ui->setupUi(this);

    connect(ui->pushButton_EnableColoring,         SIGNAL(clicked()),         this, SLOT(m_slotPopChangedColoringFlag()));
    connect(ui->horizontalSlider_ColoringRadius,   SIGNAL(valueChanged(int)), this, SLOT(m_slotPopChangedColoringRadius(int)));
    connect(ui->horizontalSlider_ColoringDistance, SIGNAL(valueChanged(int)), this, SLOT(m_slotPopChangedColoringDistance(int)));
    
	ui->horizontalSlider_ColoringRadius->setValue(25);
    ui->horizontalSlider_ColoringDistance->setValue(40);

    m_pColorBar = new SBMEColorMappingBar(this);    //颜色条添加代码
    m_pColorBar->setGeometry(QRect(15, 35, 30, 30));    //颜色条添加代码
    
	connect(m_pColorBar, SIGNAL(ValueChanged()), this, SLOT(m_slotPopChangedColorMapping()));
}

SBMEColorDlg::~SBMEColorDlg()
{
    delete ui;
}

SBMEColorMappingBar* SBMEColorDlg::GetColorMappingBar()
{
    //return ui->m_pColorbar;
    return this->m_pColorBar;    //颜色条修改代码
}

void SBMEColorDlg::m_slotPopChangedColoringFlag()
{
    if (ui->pushButton_EnableColoring->text() == "Disable Coloring")
    {
        ui->pushButton_EnableColoring->setText("Enable Coloring");
        emit m_signalEnableDisableColoring(false);
    }
    else
    {
        ui->pushButton_EnableColoring->setText("Disable Coloring");
        emit m_signalEnableDisableColoring(true);
    }
}

void SBMEColorDlg::m_slotPopChangedColoringRadius(int ColoringRadius)
{
    ui->label_ColoringRadius->setNum((float)ColoringRadius / 5);
    emit m_signalColoringRadiusChanged((float)ColoringRadius / 5);
}

void SBMEColorDlg::m_slotPopChangedColoringDistance(int ColoringDistance)
{
    ui->label_ColoringDistance->setNum(ColoringDistance);
    emit m_signalColoringDistanceChanged(ColoringDistance);
}

void SBMEColorDlg::m_slotPopChangedColorMapping()
{
    emit m_signalColorMappingChanged();
}
