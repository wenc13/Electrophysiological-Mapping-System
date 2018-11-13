#ifndef SBMESTEREOPROJECTORCONTROLPANELDLG_H
#define SBMESTEREOPROJECTORCONTROLPANELDLG_H

#include <QDialog>

namespace Ui
{
    class SBMEStereoProjectorControlPanelDlg;
}

class SBMEStereoProjectorControlPanelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMEStereoProjectorControlPanelDlg(QWidget *parent = 0);
    ~SBMEStereoProjectorControlPanelDlg();

private:
    Ui::SBMEStereoProjectorControlPanelDlg *ui;

signals:
    void m_signalFocusDistanceChanged(int FD);
    void m_signalPupilDistanceChanged(int PD);
    void m_signalFovyChanged(int Fovy);

private slots:
    void m_slotPopChangedFocusDistance(int FD);
    void m_slotPopChangedPupilDistance(int PD);
    void m_slotPopChangedFovy(int Fovy);
};

#endif // SBMESTEREOPROJECTORCONTROLPANELDLG_H
