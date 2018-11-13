#ifndef SBMECOLORDLG_H
#define SBMECOLORDLG_H

#include <QDialog>
#include "SBMEColorMappingBar.h"

namespace Ui
{
    class SBMEColorDlg;
}

class SBMEColorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMEColorDlg(QWidget *parent = 0);
    ~SBMEColorDlg();
    
	SBMEColorMappingBar *GetColorMappingBar();

private:
    Ui::SBMEColorDlg *ui;
    SBMEColorMappingBar *m_pColorBar;

signals:
    void m_signalEnableDisableColoring(bool);
    void m_signalColoringRadiusChanged(float);
    void m_signalColoringDistanceChanged(int);
	void m_signalColorMappingChanged();

private slots:
    void m_slotPopChangedColoringFlag();
    void m_slotPopChangedColoringRadius(int);
    void m_slotPopChangedColoringDistance(int);
	void m_slotPopChangedColorMapping();
};

#endif // SBMECOLORDLG_H
