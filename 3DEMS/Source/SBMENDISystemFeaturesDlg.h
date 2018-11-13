#ifndef SBMENDISYSTEMFEATURESDLG_H
#define SBMENDISYSTEMFEATURESDLG_H

#include <QDialog>

namespace Ui
{
    class SBMENDISystemFeaturesDlg;
}

class SBMENDISystemFeaturesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMENDISystemFeaturesDlg(QWidget *parent = 0);
    ~SBMENDISystemFeaturesDlg();

    void SetVariables( char *pszVersionInfo,
                       int nNoActivePorts,
                       int nNoPassivePorts,
                       int nNoActiveWireless,
                       int nNoTIPDetection );
    void SetVariables( char *pszVersionInfo,
                       int nNoMagneticPorts,
                       int nNoFieldGenerators,
                       int nNoFieldGeneratorCards );

private:
    Ui::SBMENDISystemFeaturesDlg *ui;

private slots:
    void m_slotAccept();

};

#endif // SBMENDISYSTEMFEATURESDLG_H
