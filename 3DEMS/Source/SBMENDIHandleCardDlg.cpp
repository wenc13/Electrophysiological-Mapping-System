#include "SBMENDIHandleCardDlg.h"
#include "ui_SBMENDIHandleCardDlg.h"

#include <QColorDialog>

SBMENDIHandleCardDlg::SBMENDIHandleCardDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMENDIHandleCardDlg)
{
    ui->setupUi(this);

	//setFixedSize(this->width(), this->height());

    ui->comboBox_HandleModel->addItem("Default", 0);
    ui->comboBox_HandleModel->addItem("Line", 1);
    ui->comboBox_HandleModel->addItem("Spiral", 2);
    ui->comboBox_HandleModel->addItem("Sphere", 3);
    ui->comboBox_HandleModel->setCurrentIndex(0);
    connect(ui->pushButton_Enable,               SIGNAL(clicked()),                this, SLOT(m_slotOnEnableorDisableHandle()));
    connect(ui->comboBox_HandleModel,            SIGNAL(currentIndexChanged(int)), this, SLOT(m_slotOnSetHandleModel(int)));
    connect(ui->pushButton_Color,                SIGNAL(clicked()),                this, SLOT(m_slotOnSetHandleColor()));
	connect(ui->pushButton_SetAsReferenceHandle, SIGNAL(clicked()),                this, SLOT(m_slotOnSetReferenceHandle()));
    connect(ui->pushButton_SetAsActiveHandle,    SIGNAL(clicked()),                this, SLOT(m_slotOnSetActiveHandle()));

	m_nCardIndex = -1;
    m_nPortIndex = -1;
    m_bIsEnbaled = false;
}

SBMENDIHandleCardDlg::~SBMENDIHandleCardDlg()
{
    delete ui;
}

void SBMENDIHandleCardDlg::SetCardIndex(int idx)
{
    m_nCardIndex = idx;
}

void SBMENDIHandleCardDlg::SetPortIndex(int index)
{
    m_nPortIndex = index;
    QString str = QString::number(m_nPortIndex, 16).toUpper();
    ui->lineEdit_PortIndex->setText(str);
}

void SBMENDIHandleCardDlg::SetPartNum(QString str)
{
    ui->lineEdit_PartNum->setText(str);
}

void SBMENDIHandleCardDlg::SetHandleEnabled(bool bEnabled)
{
    m_bIsEnbaled = bEnabled;
    if (m_bIsEnbaled)
        ui->pushButton_Enable->setText("Disable");
    else
        ui->pushButton_Enable->setText("Enable");
}

void SBMENDIHandleCardDlg::EnableorDisableButton(bool bEnable)
{
    ui->pushButton_Enable->setEnabled(bEnable);
}

void SBMENDIHandleCardDlg::SetReferenceHandleEnabled(bool bEnable)
{
	ui->pushButton_SetAsReferenceHandle->setEnabled(bEnable);
}

void SBMENDIHandleCardDlg::SetStatus(QString str)
{
    ui->lineEdit_Status->setText(str);
}

void SBMENDIHandleCardDlg::SetOutOfVolume(QString str)
{
    ui->lineEdit_OV->setText(str);
}

void SBMENDIHandleCardDlg::SetError(QString str)
{
    ui->lineEdit_Error->setText(str);
}

void SBMENDIHandleCardDlg::SetTx(QString str)
{
    ui->lineEdit_Tx->setText(str);
}

void SBMENDIHandleCardDlg::SetTy(QString str)
{
    ui->lineEdit_Ty->setText(str);
}

void SBMENDIHandleCardDlg::SetTz(QString str)
{
    ui->lineEdit_Tz->setText(str);
}

void SBMENDIHandleCardDlg::SetQ0(QString str)
{
    ui->lineEdit_Q0->setText(str);
}

void SBMENDIHandleCardDlg::SetQx(QString str)
{
    ui->lineEdit_Qx->setText(str);
}

void SBMENDIHandleCardDlg::SetQy(QString str)
{
    ui->lineEdit_Qy->setText(str);
}

void SBMENDIHandleCardDlg::SetQz(QString str)
{
    ui->lineEdit_Qz->setText(str);
}

void SBMENDIHandleCardDlg::SetQ0Text(QString str)
{
    ui->label_Q0->setText(str);
}

void SBMENDIHandleCardDlg::SetQxText(QString str)
{
    ui->label_Qx->setText(str);
}

void SBMENDIHandleCardDlg::SetQyText(QString str)
{
    ui->label_Qy->setText(str);
}

void SBMENDIHandleCardDlg::SetQzText(QString str)
{
    ui->label_Qz->setText(str);
}

void SBMENDIHandleCardDlg::m_slotOnEnableorDisableHandle()
{
    if (m_bIsEnbaled)
        emit(m_signalToEnableorDisableHandle(m_nCardIndex, m_nPortIndex, false));

    else
        emit(m_signalToEnableorDisableHandle(m_nCardIndex, m_nPortIndex, true));

}

void SBMENDIHandleCardDlg::m_slotOnSetHandleModel(int model)
{
    emit m_signalToSetHandleModel(m_nCardIndex, model);
}

void SBMENDIHandleCardDlg::m_slotOnSetHandleColor()
{
    QColor color = QColorDialog::getColor(Qt::blue, this, "Set Handle Color");
    emit m_signalToSetHandleColor(m_nCardIndex, color);
}

void SBMENDIHandleCardDlg::m_slotOnSetReferenceHandle()
{
    if (ui->pushButton_SetAsReferenceHandle->text() == "Set As Reference Handle")
		ui->pushButton_SetAsReferenceHandle->setText(QString("Cancel Reference Handle"));
	else
		ui->pushButton_SetAsReferenceHandle->setText(QString("Set As Reference Handle"));
	
	emit m_signalToSetReferenceHandle(m_nCardIndex, m_nPortIndex);
}

void SBMENDIHandleCardDlg::m_slotOnSetActiveHandle()
{
    emit m_signalToSetActiveHandle(m_nCardIndex);
}
