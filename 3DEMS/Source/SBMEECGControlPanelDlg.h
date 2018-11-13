#ifndef SBMEECGCONTROLPANELDLG_H
#define SBMEECGCONTROLPANELDLG_H

#include <QDialog>
#include <QCheckBox>
#include "SBMEMacroDefinition.h"

namespace Ui
{
    class SBMEECGControlPanelDlg;
}

class SBMEECGControlPanelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMEECGControlPanelDlg(QWidget *parent = 0);
    ~SBMEECGControlPanelDlg();

private:
    Ui::SBMEECGControlPanelDlg *ui;

    int  m_nSelectedECGNum;
    int  m_SelectedECGIndex[SBME_MAX_DISPLAY_ECG_NUM];
    
	bool m_ECGFlag[SBME_ELECTRODE_NUM];
    
	QCheckBox *m_CheckBoxArray[SBME_ELECTRODE_NUM];

signals:
    void m_signalSelectedECGtoDispaly(int ECGnum, int *ECGIndex);

private slots:
    void m_slotCheckBoxesStateChanged(int state);
    void m_slotSelectedECGChanged();
	void m_slotOKButtonEnabled(bool);
};

#endif // SBMEECGCONTROLPANELDLG_H
