#include "SBMEECGControlPanelDlg.h"
#include "ui_SBMEECGControlPanelDlg.h"

SBMEECGControlPanelDlg::SBMEECGControlPanelDlg(QWidget *parent) : QDialog(parent),
    ui(new Ui::SBMEECGControlPanelDlg)
{
    ui->setupUi(this);

	setFixedSize(this->width(), this->height());
	connect(ui->pushButton_OK, SIGNAL(clicked()), this, SLOT(m_slotSelectedECGChanged()));
	
	m_CheckBoxArray[0]   = ui->checkBox_1;   m_CheckBoxArray[1]   = ui->checkBox_2;   m_CheckBoxArray[2]   = ui->checkBox_3;   m_CheckBoxArray[3]   = ui->checkBox_4;
    m_CheckBoxArray[4]   = ui->checkBox_5;   m_CheckBoxArray[5]   = ui->checkBox_6;   m_CheckBoxArray[6]   = ui->checkBox_7;   m_CheckBoxArray[7]   = ui->checkBox_8;
    m_CheckBoxArray[8]   = ui->checkBox_9;   m_CheckBoxArray[9]   = ui->checkBox_10;  m_CheckBoxArray[10]  = ui->checkBox_11;  m_CheckBoxArray[11]  = ui->checkBox_12;
    m_CheckBoxArray[12]  = ui->checkBox_13;  m_CheckBoxArray[13]  = ui->checkBox_14;  m_CheckBoxArray[14]  = ui->checkBox_15;  m_CheckBoxArray[15]  = ui->checkBox_16;
    m_CheckBoxArray[16]  = ui->checkBox_17;  m_CheckBoxArray[17]  = ui->checkBox_18;  m_CheckBoxArray[18]  = ui->checkBox_19;  m_CheckBoxArray[19]  = ui->checkBox_20;
    m_CheckBoxArray[20]  = ui->checkBox_21;  m_CheckBoxArray[21]  = ui->checkBox_22;  m_CheckBoxArray[22]  = ui->checkBox_23;  m_CheckBoxArray[23]  = ui->checkBox_24;
    m_CheckBoxArray[24]  = ui->checkBox_25;  m_CheckBoxArray[25]  = ui->checkBox_26;  m_CheckBoxArray[26]  = ui->checkBox_27;  m_CheckBoxArray[27]  = ui->checkBox_28;
    m_CheckBoxArray[28]  = ui->checkBox_29;  m_CheckBoxArray[29]  = ui->checkBox_30;  m_CheckBoxArray[30]  = ui->checkBox_31;  m_CheckBoxArray[31]  = ui->checkBox_32;
    m_CheckBoxArray[32]  = ui->checkBox_33;  m_CheckBoxArray[33]  = ui->checkBox_34;  m_CheckBoxArray[34]  = ui->checkBox_35;  m_CheckBoxArray[35]  = ui->checkBox_36;
    m_CheckBoxArray[36]  = ui->checkBox_37;  m_CheckBoxArray[37]  = ui->checkBox_38;  m_CheckBoxArray[38]  = ui->checkBox_39;  m_CheckBoxArray[39]  = ui->checkBox_40;
    m_CheckBoxArray[40]  = ui->checkBox_41;  m_CheckBoxArray[41]  = ui->checkBox_42;  m_CheckBoxArray[42]  = ui->checkBox_43;  m_CheckBoxArray[43]  = ui->checkBox_44;
    m_CheckBoxArray[44]  = ui->checkBox_45;  m_CheckBoxArray[45]  = ui->checkBox_46;  m_CheckBoxArray[46]  = ui->checkBox_47;  m_CheckBoxArray[47]  = ui->checkBox_48;
    m_CheckBoxArray[48]  = ui->checkBox_49;  m_CheckBoxArray[49]  = ui->checkBox_50;  m_CheckBoxArray[50]  = ui->checkBox_51;  m_CheckBoxArray[51]  = ui->checkBox_52;
    m_CheckBoxArray[52]  = ui->checkBox_53;  m_CheckBoxArray[53]  = ui->checkBox_54;  m_CheckBoxArray[54]  = ui->checkBox_55;  m_CheckBoxArray[55]  = ui->checkBox_56;
    m_CheckBoxArray[56]  = ui->checkBox_57;  m_CheckBoxArray[57]  = ui->checkBox_58;  m_CheckBoxArray[58]  = ui->checkBox_59;  m_CheckBoxArray[59]  = ui->checkBox_60;
    m_CheckBoxArray[60]  = ui->checkBox_61;  m_CheckBoxArray[61]  = ui->checkBox_62;  m_CheckBoxArray[62]  = ui->checkBox_63;  m_CheckBoxArray[63]  = ui->checkBox_64;

    for (int i = 0; i < SBME_ELECTRODE_NUM; i++)
    {
        m_ECGFlag[i] = false;
        connect(m_CheckBoxArray[i], SIGNAL(stateChanged(int)), this, SLOT(m_slotCheckBoxesStateChanged(int)));
    }
    
	m_nSelectedECGNum = 0;
    //m_slotSelectedECGChanged();
}

SBMEECGControlPanelDlg::~SBMEECGControlPanelDlg()
{
    delete ui;
}

void SBMEECGControlPanelDlg::m_slotCheckBoxesStateChanged(int state)
{
    if (state == 0)
        m_nSelectedECGNum--;
    else if (state == 2)
        m_nSelectedECGNum++;
    if (m_nSelectedECGNum == SBME_MAX_DISPLAY_ECG_NUM)
    {
        for (int i = 0; i < SBME_ELECTRODE_NUM; i++)
        {
            if (m_CheckBoxArray[i]->isChecked() == false)
                m_CheckBoxArray[i]->setDisabled(true);
        }
    }
    else
    {
        for (int i = 0; i < SBME_ELECTRODE_NUM; i++)
        {
            m_CheckBoxArray[i]->setEnabled(true);
        }
    }
}

void SBMEECGControlPanelDlg::m_slotSelectedECGChanged()
{
    int i = 0, j = 0;
    for (i = 0; i < SBME_ELECTRODE_NUM; i++)
    {
        if (m_CheckBoxArray[i]->isChecked() == true)
        {
            m_SelectedECGIndex[j] = i;
            j++;
        }
    }
    emit m_signalSelectedECGtoDispaly(m_nSelectedECGNum, m_SelectedECGIndex);
}

void SBMEECGControlPanelDlg::m_slotOKButtonEnabled(bool isabled)
{
	ui->pushButton_OK->setEnabled(isabled);
}